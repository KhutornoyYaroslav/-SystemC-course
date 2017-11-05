#include "systemc.h"

SC_MODULE(GPIO) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> reset;
	sc_in<bool> in;
	sc_in<bool> out;
	sc_out<bool> ack;
	sc_in<sc_int<32> > data_from_cpu;
	sc_out<sc_int<32> > data_to_cpu;

    //------------Local Variables Here---------------------
	sc_signal<sc_int<32> > in_register;
	sc_signal<sc_int<32> > out_register;

    //------------Code Starts Here-------------------------
	void gpio_cthread();

    //------------Constructor Here-------------------------   
    SC_CTOR(GPIO) : 

		clock("clock"), 
		reset("reset"),
		in("in"),
		out("out"),
		ack("ack"),
		data_from_cpu("data_from_cpu"),
		data_to_cpu("data_to_cpu")

    {
        cout << "GPIO is now created..." << endl;

        SC_CTHREAD(gpio_cthread, clock.pos());
        reset_signal_is(reset, true);
    }
};