#include "systemc.h"

SC_MODULE(DECODE) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> enable;
    sc_in<bool> reset;
	sc_in<sc_int<32> > in_decode_instr;
	sc_out<sc_uint<4> > out_type_of_instr;
	sc_out<sc_uint<3> > out_type_of_operation;
	sc_out<sc_uint<5> > out_adrress_ron_result;
	sc_out<sc_uint<5> > out_adrress_ron_1;
	sc_out<sc_uint<5> > out_adrress_ron_2;
	sc_out<sc_uint<20> > out_direct_data;
	sc_out<sc_uint<25> > out_branch_adrress;

    //------------Local Variables Here---------------------


    //------------Code Starts Here-------------------------
	void decode_method();
    void decode_cthread();
    
    //------------Constructor Here-------------------------   
    SC_CTOR(DECODE) : 

		clock("clock"), 
		enable("enable"),
		reset("reset"),
		in_decode_instr("in_decode_instr"),
		out_type_of_instr("out_type_of_instr"),
		out_type_of_operation("out_type_of_operation"),
		out_adrress_ron_result("out_adrress_ron_result"),
		out_direct_data("out_direct_data"),
		out_branch_adrress("out_branch_adrress"),
		out_adrress_ron_1("out_adrress_ron_1"),
		out_adrress_ron_2("out_adrress_ron_2")

    {
        cout << "DECODE is now created..." << endl;

		SC_METHOD(decode_method);
        sensitive << in_decode_instr;

        SC_CTHREAD(decode_cthread, clock.pos());        
        reset_signal_is(reset, true); 
    }
};