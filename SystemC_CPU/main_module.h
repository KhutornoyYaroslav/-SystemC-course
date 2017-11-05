#include "arbiter.h"
#include "systemc.h"
#include "ron.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "mem.h"
#include "wb.h"
#include "l1.h"
#include "mpu.h"
#include "ram.h"
#include "gpio.h"

SC_MODULE(main_module) 
{
	ARBITER arbiter_comp;
	RON ron_comp;
	GPIO gpio_comp;
	L1 l1_instr_comp;
	L1 l1_data_comp;
	MPU mpu_comp;
	RAM ram_comp;
	FETCH fetch_comp;
	DECODE decode_comp;
	EXECUTE execute_comp;
	MEM mem_comp;
	WB wb_comp;

    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
    sc_in<bool> reset;
    sc_out<bool> out_mpu_error;

    //------------Local Variables Here---------------------
	sc_signal<bool> fetch_ready;
	sc_signal<bool> mem_ready;
	sc_signal<sc_uint<32> > adrress_from_fetch_to_l1_instr;
	sc_signal<sc_int<32> > instruction_from_l1_instr_to_fetch;
	sc_signal<bool> ack_from_l1_instr_to_fetch;
	sc_signal<sc_int<32> > instruction_from_fetch_to_decode;
	sc_signal<sc_uint<25> > branch_adrress_from_exec_to_fetch;
	sc_signal<bool> branch_adrress_load_from_exec_to_fetch;
	sc_signal<bool> read_enable_from_fetch_to_mpu;
	sc_signal<bool> write_enable_from_fetch_to_mpu;
	sc_signal<bool> read_enable_from_mpu_to_l1_instr;
	sc_signal<bool> write_enable_from_mpu_to_l1_instr;
	sc_signal<sc_uint<4> > type_of_instr_from_decode_to_exec;
	sc_signal<sc_uint<3> > type_of_operation_from_decode_to_exec;
	sc_signal<sc_uint<5> > adrress_ron_result_from_decode_to_exec;
	sc_signal<sc_uint<5> > adrress_ron_1_from_decode_to_ron;
	sc_signal<sc_uint<5> > adrress_ron_2_from_decode_to_ron;
	sc_signal<sc_uint<20> > direct_data_from_decode_to_exec;
	sc_signal<sc_uint<25> > branch_adrress_from_decode_to_exec;
	sc_signal<sc_int<32> > operand_1_from_ron_to_execute;
	sc_signal<sc_int<32> > operand_2_from_ron_to_execute;
	sc_signal<sc_int<32> > result_main_from_exec_to_mem;
	sc_signal<sc_uint<4> > type_of_instr_from_exec_to_mem;
	sc_signal<sc_uint<5> > adrress_ron_result_from_exec_to_mem;
	sc_signal<sc_uint<32> > adrress_mem_from_exec_to_mem;
	sc_signal<sc_int<32> > data_from_mem_to_wb; 
	sc_signal<sc_uint<4> > type_of_instr_from_mem_to_wb; 
	sc_signal<sc_uint<5> > adrress_ron_result_from_mem_to_wb; 
	sc_signal<sc_int<32> > data_from_mem_to_l1_data; 
	sc_signal<sc_int<32> > data_from_l1_data_to_mem; 
	sc_signal<sc_uint<32> > adrress_mem_from_mem_to_l1_data; 
	sc_signal<bool> read_enable_from_mem_to_mpu;
	sc_signal<bool> write_enable_from_mem_to_mpu;
	sc_signal<bool> read_enable_from_mpu_to_l1_data;
	sc_signal<bool> write_enable_from_mpu_to_l1_data;
	sc_signal<bool> ack_from_l1_data_to_mem; 
	sc_signal<bool> gpio_in_from_mem_to_gpio;
	sc_signal<bool> gpio_out_from_mem_to_gpio;
	sc_signal<bool> gpio_ack_from_gpio_to_mem;
	sc_signal<sc_int<32> > data_from_gpio_to_mem;
	sc_signal<sc_int<32> > data_from_mem_to_gpio;
	sc_signal<sc_uint<5> > adrress_ron_result_from_wb_to_ron; 
	sc_signal<sc_int<32> > data_ron_result_from_wb_to_ron; 
	sc_signal<bool> write_ena_from_wb_to_ron; 
	sc_signal<bool> fetch_enable;
	sc_signal<bool> exec_enable;
	sc_signal<bool> decode_enable;
	sc_signal<bool> mem_enable;
	sc_signal<bool> branch_reset;
	sc_signal<bool> stop;
	sc_signal<sc_uint<32> > ram_adrress_from_l1_instr_to_ram; 
	sc_signal<sc_int<32> > ram_data_from_ram_to_l1_instr; 
	sc_signal<sc_int<32> > ram_data_from_l1_instr_to_ram; 
	sc_signal<bool> ram_write_enable_from_l1_instr_to_ram;
	sc_signal<bool> ram_read_enable_from_l1_instr_to_ram;
	sc_signal<bool> ram_ack_from_ram_to_l1_instr; 
	sc_signal<sc_uint<32> > ram_adrress_from_l1_data_to_ram; 
	sc_signal<sc_int<32> > ram_data_from_ram_to_l1_data; 
	sc_signal<sc_int<32> > ram_data_from_l1_data_to_ram; 
	sc_signal<bool> ram_write_enable_from_l1_data_to_ram;
	sc_signal<bool> ram_read_enable_from_l1_data_to_ram;
	sc_signal<bool> ram_ack_from_ram_to_l1_data; 
	sc_signal<sc_int<32> > data_to_l1_instr;

    //------------Constructor Here-------------------------   
    SC_CTOR(main_module) : 

		arbiter_comp("arbiter_comp"),
		ron_comp("ron_comp"),
		gpio_comp("gpio_comp"),
		l1_instr_comp("l1_comp"),
		l1_data_comp("l1_data_comp"),
		mpu_comp("mpu_comp"),
		ram_comp("ram_comp"),
		fetch_comp("fetch_comp"),
		decode_comp("decode_comp"),
		execute_comp("execute_comp"),
		mem_comp("mem_comp"),
		wb_comp("wb_comp")

    {

		fetch_comp.clock(clock);
		fetch_comp.reset(reset);
		fetch_comp.enable(fetch_enable);
		fetch_comp.ready(fetch_ready);
		fetch_comp.out_adrress_to_mem(adrress_from_fetch_to_l1_instr);
		fetch_comp.in_instruction_from_mem(instruction_from_l1_instr_to_fetch);
		fetch_comp.in_ack_from_mem(ack_from_l1_instr_to_fetch);
		fetch_comp.out_instruction_to_decode(instruction_from_fetch_to_decode);
		fetch_comp.in_branch_adrress_from_exec(branch_adrress_from_exec_to_fetch);
		fetch_comp.in_branch_adrress_load_from_exec(branch_adrress_load_from_exec_to_fetch);
		fetch_comp.fetch_read_enable(read_enable_from_fetch_to_mpu);
		fetch_comp.fetch_write_enable(write_enable_from_fetch_to_mpu);


		decode_comp.clock(clock);
		decode_comp.reset(branch_reset);
		decode_comp.enable(decode_enable);
		decode_comp.in_decode_instr(instruction_from_fetch_to_decode);
		decode_comp.out_type_of_instr(type_of_instr_from_decode_to_exec);
		decode_comp.out_type_of_operation(type_of_operation_from_decode_to_exec);
		decode_comp.out_adrress_ron_result(adrress_ron_result_from_decode_to_exec);
		decode_comp.out_adrress_ron_1(adrress_ron_1_from_decode_to_ron);
		decode_comp.out_adrress_ron_2(adrress_ron_2_from_decode_to_ron);
		decode_comp.out_direct_data(direct_data_from_decode_to_exec);
		decode_comp.out_branch_adrress(branch_adrress_from_decode_to_exec);


		execute_comp.clock(clock);
		execute_comp.reset(branch_reset);
		execute_comp.enable(exec_enable);
		execute_comp.in_operand_1(operand_1_from_ron_to_execute);
		execute_comp.in_operand_2(operand_2_from_ron_to_execute);
		execute_comp.in_type_of_instr(type_of_instr_from_decode_to_exec);
		execute_comp.in_type_of_operation(type_of_operation_from_decode_to_exec);
		execute_comp.in_adrress_ron_result(adrress_ron_result_from_decode_to_exec);
		execute_comp.in_direct_data(direct_data_from_decode_to_exec);
		execute_comp.in_branch_adrress(branch_adrress_from_decode_to_exec);
		execute_comp.out_branch_adrress_to_fetch(branch_adrress_from_exec_to_fetch);
		execute_comp.out_branch_adrress_load_to_fecth(branch_adrress_load_from_exec_to_fetch);
		execute_comp.out_result_main(result_main_from_exec_to_mem);
		execute_comp.out_type_of_instr(type_of_instr_from_exec_to_mem);
		execute_comp.out_adrress_ron_result(adrress_ron_result_from_exec_to_mem);
		execute_comp.out_adrress_mem(adrress_mem_from_exec_to_mem);
		execute_comp.out_stop(stop);


		mem_comp.clock(clock);
		mem_comp.reset(reset);
		mem_comp.enable(mem_enable);
		mem_comp.ready(mem_ready);
		mem_comp.data_from_exec(result_main_from_exec_to_mem);
		mem_comp.in_type_of_instr(type_of_instr_from_exec_to_mem);
		mem_comp.in_adrress_ron_result(adrress_ron_result_from_exec_to_mem);
		mem_comp.in_adrress_mem(adrress_mem_from_exec_to_mem);
		mem_comp.out_data(data_from_mem_to_wb);
		mem_comp.out_type_of_instr(type_of_instr_from_mem_to_wb);
		mem_comp.out_adrress_ron_result(adrress_ron_result_from_mem_to_wb);
		mem_comp.data_from_mem(data_from_l1_data_to_mem);
		mem_comp.data_to_mem(data_from_mem_to_l1_data);
		mem_comp.mem_adress(adrress_mem_from_mem_to_l1_data);
		mem_comp.mem_read_enable(read_enable_from_mem_to_mpu);
		mem_comp.mem_write_enable(write_enable_from_mem_to_mpu);
		mem_comp.mem_ack(ack_from_l1_data_to_mem);
		mem_comp.to_gpio_in(gpio_in_from_mem_to_gpio);
		mem_comp.to_gpio_out(gpio_out_from_mem_to_gpio);
		mem_comp.from_gpio_ack(gpio_ack_from_gpio_to_mem);
		mem_comp.data_from_gpio(data_from_gpio_to_mem);
		mem_comp.data_to_gpio(data_from_mem_to_gpio);


		wb_comp.clock(clock);
		wb_comp.reset(reset);
		wb_comp.enable(decode_enable);
		wb_comp.in_type_of_instr(type_of_instr_from_mem_to_wb);
		wb_comp.in_adrress_ron_result(adrress_ron_result_from_mem_to_wb);
		wb_comp.in_data(data_from_mem_to_wb);
		wb_comp.out_adrress_ron_result(adrress_ron_result_from_wb_to_ron);
		wb_comp.out_data_ron_result(data_ron_result_from_wb_to_ron);
		wb_comp.out_write_ena(write_ena_from_wb_to_ron);


		arbiter_comp.reset(reset);
		arbiter_comp.in_fetch_ready(fetch_ready);
		arbiter_comp.in_mem_ready(mem_ready);
		arbiter_comp.in_branch_adrress_load_to_fecth(branch_adrress_load_from_exec_to_fetch);
		arbiter_comp.out_fetch_enable(fetch_enable);
		arbiter_comp.out_exec_enable(exec_enable);
		arbiter_comp.out_decode_enable(decode_enable);
		arbiter_comp.out_mem_enable(mem_enable);
		arbiter_comp.out_reset(branch_reset);
		arbiter_comp.in_stop(stop);


		ron_comp.clock(clock);
		ron_comp.reset(branch_reset);
		ron_comp.enable(decode_enable);
		ron_comp.in_adrress_ron_1(adrress_ron_1_from_decode_to_ron);
		ron_comp.in_adrress_ron_2(adrress_ron_2_from_decode_to_ron);
		ron_comp.in_adrress_ron_result(adrress_ron_result_from_wb_to_ron);
		ron_comp.in_write_enable_result(write_ena_from_wb_to_ron);
		ron_comp.out_data_ron_1(operand_1_from_ron_to_execute);
		ron_comp.out_data_ron_2(operand_2_from_ron_to_execute);
		ron_comp.in_data_ron_result(data_ron_result_from_wb_to_ron);


		l1_instr_comp.clock(clock);
		l1_instr_comp.reset(reset);
		l1_instr_comp.in_adrress(adrress_from_fetch_to_l1_instr);
		l1_instr_comp.in_data(data_to_l1_instr);//
		l1_instr_comp.out_data(instruction_from_l1_instr_to_fetch);
		l1_instr_comp.in_read_enable(read_enable_from_mpu_to_l1_instr);
		l1_instr_comp.in_write_enable(write_enable_from_mpu_to_l1_instr);
		l1_instr_comp.out_ack(ack_from_l1_instr_to_fetch);
		l1_instr_comp.out_ram_adrress(ram_adrress_from_l1_instr_to_ram);
		l1_instr_comp.in_ram_data(ram_data_from_ram_to_l1_instr);
		l1_instr_comp.out_ram_data(ram_data_from_l1_instr_to_ram);
		l1_instr_comp.out_ram_write_enable(ram_write_enable_from_l1_instr_to_ram);
		l1_instr_comp.out_ram_read_enable(ram_read_enable_from_l1_instr_to_ram);
		l1_instr_comp.in_ram_ack(ram_ack_from_ram_to_l1_instr);
		

		l1_data_comp.clock(clock);
		l1_data_comp.reset(reset);
		l1_data_comp.in_adrress(adrress_mem_from_mem_to_l1_data);
		l1_data_comp.in_data(data_from_mem_to_l1_data);
		l1_data_comp.out_data(data_from_l1_data_to_mem);
		l1_data_comp.in_read_enable(read_enable_from_mpu_to_l1_data);
		l1_data_comp.in_write_enable(write_enable_from_mpu_to_l1_data);
		l1_data_comp.out_ack(ack_from_l1_data_to_mem);
		l1_data_comp.out_ram_adrress(ram_adrress_from_l1_data_to_ram);
		l1_data_comp.in_ram_data(ram_data_from_ram_to_l1_data);
		l1_data_comp.out_ram_data(ram_data_from_l1_data_to_ram);
		l1_data_comp.out_ram_write_enable(ram_write_enable_from_l1_data_to_ram);
		l1_data_comp.out_ram_read_enable(ram_read_enable_from_l1_data_to_ram);
		l1_data_comp.in_ram_ack(ram_ack_from_ram_to_l1_data);
		

		ram_comp.clock(clock);
		ram_comp.reset(reset);
		ram_comp.in_write_enable_1(ram_write_enable_from_l1_instr_to_ram);
		ram_comp.in_read_enable_1(ram_read_enable_from_l1_instr_to_ram);
		ram_comp.out_ack_1(ram_ack_from_ram_to_l1_instr);
		ram_comp.in_adrress_1(ram_adrress_from_l1_instr_to_ram);
		ram_comp.in_data_1(ram_data_from_l1_instr_to_ram);
		ram_comp.out_data_1(ram_data_from_ram_to_l1_instr);
		ram_comp.in_write_enable_2(ram_write_enable_from_l1_data_to_ram);
		ram_comp.in_read_enable_2(ram_read_enable_from_l1_data_to_ram);
		ram_comp.out_ack_2(ram_ack_from_ram_to_l1_data);
		ram_comp.in_adrress_2(ram_adrress_from_l1_data_to_ram);
		ram_comp.in_data_2(ram_data_from_l1_data_to_ram);
		ram_comp.out_data_2(ram_data_from_ram_to_l1_data);


		gpio_comp.clock(clock);
		gpio_comp.reset(reset);
		gpio_comp.in(gpio_in_from_mem_to_gpio);
		gpio_comp.out(gpio_out_from_mem_to_gpio);
		gpio_comp.ack(gpio_ack_from_gpio_to_mem);
		gpio_comp.data_from_cpu(data_from_mem_to_gpio);
		gpio_comp.data_to_cpu(data_from_gpio_to_mem);


		mpu_comp.clock(clock);
		mpu_comp.reset(reset);
		mpu_comp.in_adrress_1(adrress_from_fetch_to_l1_instr);
		mpu_comp.in_write_enable_1(write_enable_from_fetch_to_mpu);
		mpu_comp.in_read_enable_1(read_enable_from_fetch_to_mpu);
		mpu_comp.out_write_enable_1(write_enable_from_mpu_to_l1_instr);
		mpu_comp.out_read_enable_1(read_enable_from_mpu_to_l1_instr);
		mpu_comp.in_adrress_2(adrress_mem_from_mem_to_l1_data);
		mpu_comp.in_write_enable_2(write_enable_from_mem_to_mpu);
		mpu_comp.in_read_enable_2(read_enable_from_mem_to_mpu);
		mpu_comp.out_write_enable_2(write_enable_from_mpu_to_l1_data);
		mpu_comp.out_read_enable_2(read_enable_from_mpu_to_l1_data);
		mpu_comp.out_error(out_mpu_error);
    }
};
