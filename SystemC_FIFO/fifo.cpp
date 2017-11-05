
#include "fifo.h"

void fifo::fifo_push() 
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

void fifo::fifo_pop() 
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

void fifo::fifo_method()
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