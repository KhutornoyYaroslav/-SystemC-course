
#include "systemc.h"

#ifndef DESIGN_H
#define	DESIGN_H

SC_MODULE(eightbit_counter) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;
    sc_in<bool> areset;   
    sc_in<bool> reset;
    sc_in<bool> up_down;
    sc_out<sc_uint<8> > counter_data; 

    //------------Local Variables Here---------------------
    sc_uint<8> mycounter;

    //------------Code Starts Here-------------------------
    void counter_action();
    
    //------------Constructor Here-------------------------   
    SC_CTOR(eightbit_counter) : 

		clock("clock"), 
		reset("reset"), 
		areset("areset"), 
		up_down("up_down")

    {
        cout << "Executing new" << endl;
        SC_CTHREAD(counter_action, clock.pos());
        async_reset_signal_is(areset, true);         
        reset_signal_is(reset, true);      
    }
};

#endif