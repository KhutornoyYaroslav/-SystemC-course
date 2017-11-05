#include "systemc.h"

#ifndef DESIGN_H
#define	DESIGN_H

SC_MODULE(fifo) 
{
    sc_in_clk clock; 
    sc_in<bool> sreset_n; 
    sc_in<char> data_in;
	sc_in<bool> push;
	sc_in<bool> pop;

	sc_out<char> data_out;
	sc_out<bool> empty;
	sc_out<bool> full;

    //------------Local Variables Here---------------------
	int size;
	char *data;

    //--------------Local Signals Here---------------------
	sc_signal<int> push_pointer, pop_pointer;
	sc_signal<bool> push_over, pop_over;

    //------------Code Starts Here-------------------------
    void fifo_push();   
    void fifo_pop();
	void fifo_method();

	SC_HAS_PROCESS(fifo);  
    fifo(sc_module_name name, int SizeOfData) :
            
		clock("clock"),
        sreset_n("sreset_n"),
        data_in("data_in"),
        push("push"),
        pop("pop"),
		data_out("data_out"),
		empty("empty"),
		full("full")

	{
		size = SizeOfData;
		data = new char[SizeOfData];

        cout << "FIFO executing new" << endl;

        SC_CTHREAD(fifo_push, clock.pos());
        reset_signal_is(sreset_n, false);

		SC_CTHREAD(fifo_pop, clock.pos());
        reset_signal_is(sreset_n, false);

		SC_METHOD(fifo_method);
		sensitive << push_pointer << pop_pointer << push_over << pop_over;
    }

}; 

#endif

