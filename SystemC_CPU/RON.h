
#include "systemc.h"

SC_MODULE(RON) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> enable;
    sc_in<bool> reset;	
	sc_in<sc_uint<5> > in_adrress_ron_1;
	sc_in<sc_uint<5> > in_adrress_ron_2;
	sc_in<sc_uint<5> > in_adrress_ron_result;
	sc_in<bool> in_write_enable_result;
	sc_out<sc_int<32> > out_data_ron_1;
	sc_out<sc_int<32> > out_data_ron_2;
	sc_in<sc_int<32> > in_data_ron_result;

    //------------Local Variables Here---------------------
	int data[32];

    //------------Code Starts Here-------------------------
    void ron_action();
    
    //------------Constructor Here-------------------------   
    SC_CTOR(RON) : 

		clock("clock"), 
		enable("enable"),
		reset("reset"),
		in_adrress_ron_1("in_adrress_ron_1"),
		in_adrress_ron_2("in_adrress_ron_2"),
		in_adrress_ron_result("in_adrress_ron_result"),
		out_data_ron_1("out_data_ron_1"),
		out_data_ron_2("out_data_ron_2"),
		in_data_ron_result("in_data_ron_result"),
		in_write_enable_result("in_write_enable_result")

    {
        cout << "RON is now created..." << endl;
		SC_CTHREAD(ron_action, clock.pos());
        reset_signal_is(reset, true);      
    }
};