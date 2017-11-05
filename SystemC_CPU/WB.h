#include "systemc.h"

SC_MODULE(WB) 
{
    //--------------------Ports Here-----------------------
	sc_in_clk clock;  
    sc_in<bool> reset;	
	sc_in<bool> enable;
	sc_in<sc_uint<4> > in_type_of_instr;
	sc_in<sc_uint<5> > in_adrress_ron_result;
	sc_in<sc_int<32> > in_data;
	sc_out<sc_uint<5> > out_adrress_ron_result; 
	sc_out<sc_int<32> > out_data_ron_result; 
	sc_out<bool> out_write_ena; 

    //------------Local Variables Here---------------------

    //------------Code Starts Here-------------------------
    void wb_method();    

    //------------Constructor Here-------------------------   
    SC_CTOR(WB) : 

		clock("clock"),
		reset("reset"),
		enable("enable"),
		in_type_of_instr("in_type_of_instr"),		
		in_adrress_ron_result("in_adrress_ron_result"),
		in_data("in_data"),
		out_adrress_ron_result("out_adrress_ron_result"),
		out_data_ron_result("out_data_ron_result")

    {
        cout << "WB is now created..." << endl;

		SC_METHOD(wb_method);
        sensitive << in_type_of_instr << in_data << in_adrress_ron_result << enable;
    }
};