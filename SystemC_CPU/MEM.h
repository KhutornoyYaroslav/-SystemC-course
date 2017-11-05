#include "systemc.h"

SC_MODULE(MEM) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> enable;
    sc_in<bool> reset;	
	sc_out<bool> ready;
	sc_in<sc_int<32> > data_from_exec; 
	sc_in<sc_uint<4> > in_type_of_instr;
	sc_in<sc_uint<5> > in_adrress_ron_result; 
	sc_in<sc_uint<32> > in_adrress_mem; 
	sc_out<sc_int<32> > out_data; 
	sc_out<sc_uint<4> > out_type_of_instr;
	sc_out<sc_uint<5> > out_adrress_ron_result; 
	sc_in<sc_int<32> > data_from_mem;  
	sc_out<sc_int<32> > data_to_mem; 
	sc_out<sc_uint<32> > mem_adress; 
	sc_out<bool> mem_read_enable;
	sc_out<bool> mem_write_enable;
	sc_in<bool> mem_ack; 
	sc_out<bool> to_gpio_in;
	sc_out<bool> to_gpio_out;
	sc_in<bool> from_gpio_ack;
	sc_in<sc_int<32> > data_from_gpio;
	sc_out<sc_int<32> > data_to_gpio;

    //------------Local Variables Here---------------------


    //------------Code Starts Here-------------------------
	void mem_cthread();

    //------------Constructor Here-------------------------   
    SC_CTOR(MEM) : 

		clock("clock"), 
		enable("enable"),
		reset("reset"),
		ready("ready"),
		data_from_exec("data_from_exec"),
		in_type_of_instr("in_type_of_instr"),
		in_adrress_ron_result("in_adrress_ron_result"),
		in_adrress_mem("in_adrress_mem"),
		out_data("out_data"),
		out_type_of_instr("out_type_of_instr"),
		out_adrress_ron_result("out_adrress_ron_result"),
		data_from_mem("data_from_mem"),
		data_to_mem("data_to_mem"),
		mem_adress("mem_adress"),
		mem_read_enable("mem_read_enable"),
		mem_write_enable("mem_write_enable"),
		mem_ack("mem_ack"),
		to_gpio_in("to_gpio_in"),
		to_gpio_out("to_gpio_out"),
		from_gpio_ack("from_gpio_ack"),
		data_from_gpio("data_from_gpio"),
		data_to_gpio("data_to_gpio")

    {
        cout << "MEM is now created..." << endl;

		SC_CTHREAD(mem_cthread, clock.pos());        
        reset_signal_is(reset, true); 
    }
};