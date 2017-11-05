
#include "systemc.h"

#ifndef DESIGN_H
#define	DESIGN_H

SC_MODULE(eightbit_register) 
{
	//-----------------Ports Here--------------------------
    sc_in_clk clock;
    sc_in<bool> reset;
    sc_in<bool> areset;   
    sc_in<bool> load;
    sc_in<bool> register_in;   
    sc_out<bool> register_out;       
    sc_out<sc_uint<8> > register_data;
    sc_in<sc_uint<8> > load_data;

    //------------Local Variables Here---------------------
    sc_uint<8> myregister;

    //------------Code Starts Here-------------------------

    void register_store();
    
    //------------Constructor Here-------------------------
    
    SC_CTOR(eightbit_register) : 

		clock("clock"), 
		reset("reset"), 
		areset("areset"),
		load("load"), 
		load_data("load_data"), 
		register_data("register_data"),
		register_in("register_in"), 
		register_out("register_out")

    {
        cout << "Executing new" << endl;
        SC_CTHREAD(register_store, clock.pos());
        async_reset_signal_is(areset, true);         
        reset_signal_is(reset, true);      
    } 
};

#endif