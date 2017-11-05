#include "systemc.h"

SC_MODULE(state_machine) 
{
    sc_in_clk clock;
    sc_in<bool> areset;
    sc_in<sc_uint<2> > in;
    sc_out<sc_uint<2> > y;

    //------------Local Variables Here---------------------
    sc_signal<sc_uint<2> > state;

    //------------Code Starts Here-------------------------
    void pre_state();   
    void post_state();

	//------------Constructor Here-------------------------

    SC_CTOR(state_machine) :

		clock("clock"),
		areset("areset"),
		in("in"),
		y("y")

	{
        cout << "State machine executing new" << endl;

        SC_CTHREAD(pre_state, clock.pos());
        async_reset_signal_is(areset, true);

        SC_METHOD(post_state);
        sensitive << state;
    } 
}; 

