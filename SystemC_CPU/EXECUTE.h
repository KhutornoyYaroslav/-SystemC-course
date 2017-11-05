
#include "systemc.h"

SC_MODULE(EXECUTE) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;
	sc_in<bool> enable;
    sc_in<bool> reset;
	sc_in<sc_int<32> > in_operand_1;
	sc_in<sc_int<32> > in_operand_2;
	sc_in<sc_uint<4> > in_type_of_instr;
	sc_in<sc_uint<3> > in_type_of_operation;
	sc_in<sc_uint<5> > in_adrress_ron_result;
	sc_in<sc_uint<20> > in_direct_data;
	sc_in<sc_uint<25> > in_branch_adrress;
	sc_out<sc_uint<25> > out_branch_adrress_to_fetch;
	sc_out<bool> out_branch_adrress_load_to_fecth;
	sc_out<sc_int<32> > out_result_main;
	sc_out<sc_uint<4> > out_type_of_instr;
	sc_out<sc_uint<5> > out_adrress_ron_result;
	sc_out<sc_uint<32> > out_adrress_mem;
	sc_out<bool> out_stop;

    //------------Local Variables Here---------------------
	sc_int<64> tmp_result; // ?????? 33
	sc_signal<sc_int<32> > sig_operand_2;
	sc_signal<sc_int<32> > sig_result_alu;
	sc_signal<bool> sig_ready;
	sc_signal<bool> out_c_flag;
	sc_signal<bool> out_z_flag;

    //------------Code Starts Here-------------------------
    void execute_alu();
	void execute_pre_alu();   
	void execute_buffer();  

    //------------Constructor Here-------------------------   
    SC_CTOR(EXECUTE) : 

    clock("clock"),
	enable("enable"), 
    reset("reset"),
	in_operand_1("in_operand_1"),
	in_operand_2("in_operand_2"),
	in_type_of_instr("in_type_of_instr"),
	in_type_of_operation("in_type_of_operation"),
	in_adrress_ron_result("in_adrress_ron_result"),
	in_direct_data("in_direct_data"),
	in_branch_adrress("in_branch_adrress"),
	out_branch_adrress_to_fetch("out_branch_adrress_to_fetch"), 
	out_branch_adrress_load_to_fecth("out_branch_adrress_load_to_fecth"),
	out_result_main("out_result_main"),
	out_type_of_instr("out_type_of_instr"),
	out_adrress_ron_result("out_adrress_ron_result"),
	out_adrress_mem("out_adrress_mem"),
	out_stop("out_stop")

    {
        cout << "EXECUTE is now created..." << endl;

		SC_METHOD(execute_alu);        
        sensitive << in_operand_1 << sig_operand_2 << in_type_of_operation;

        SC_METHOD(execute_pre_alu);        
        sensitive << in_operand_2 << in_type_of_instr;

		SC_CTHREAD(execute_buffer, clock.pos());        
        reset_signal_is(reset, true); 
    }
};
