#include "systemc.h"

template <typename T>
class fifoparam : public sc_module
{

public:
    sc_in_clk clock; 
	sc_in<T> data_in;
	sc_out<T> data_out;
    sc_in<bool> sreset_n; 
	sc_out<bool> empty;
	sc_out<bool> full;
	sc_in<bool> push;
	sc_in<bool> pop;

    //------------Local Variables Here---------------------
	int size;
	T *data;

    //--------------Local Signals Here---------------------
	sc_signal<int> push_pointer, pop_pointer;
	sc_signal<bool> push_over, pop_over;

    //------------Code Starts Here-------------------------
    void fifo_push();   
    void fifo_pop();
	void fifo_method();

	SC_HAS_PROCESS(fifoparam);  
    fifoparam(const char* name, int SizeOfData) :
         
		sc_module(name),
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
		data = new T [SizeOfData];

        cout << "FIFO executing" << endl;
		cout << "Size of FIFO = " << size << endl;

        SC_CTHREAD(fifo_push, clock.pos());
        reset_signal_is(sreset_n, false);

		SC_CTHREAD(fifo_pop, clock.pos());
        reset_signal_is(sreset_n, false);

		SC_METHOD(fifo_method);
		sensitive << push_pointer << pop_pointer << push_over << pop_over;
    }
}; 


template <typename T>
void fifoparam<T>::fifo_push() 
{   
	push_over = 0;
	push_pointer = 0;
    wait();

    while (true) 
	{	
		if(push && !full)
		{
		data[push_pointer.read()] = data_in.read();

			if(push_pointer.read() == size-1)
			{
				push_pointer = 0;
				push_over = !push_over;
			}
			else
			{
				push_pointer = push_pointer.read() + 1;
			}

		}
        wait();
    }
}

template <typename T>
void fifoparam<T>::fifo_pop() 
{   
	pop_over = 0;
	pop_pointer = 0;
    wait();

    while (true) 
	{		
		if(pop && !empty)
		{
		data_out = data[pop_pointer.read()];

			if(pop_pointer.read() == size-1)
			{
				pop_pointer = 0;
				pop_over = !pop_over;
			}
			else
			{
				pop_pointer = pop_pointer.read() + 1;			
			}

		}
        wait();
    }
}

template <typename T>
void fifoparam<T>::fifo_method()
{
		if(push_pointer.read() == pop_pointer.read())
		{
			if(push_over.read() != pop_over.read())
			{
				empty = 0;
				full = 1;
			}
			else
			{
				empty = 1;
				full = 0;		
			}	
		}
		else
		{
			empty = 0;
			full = 0;
		}
}