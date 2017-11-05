#include "systemc.h"
#include "fifo_param.h"

template <typename T>
class fifoparaminherit : public fifoparam<T>
{	
	public:
		sc_out<bool> almost_empty;
		sc_out<bool> almost_full;

		void almost_method();


    SC_HAS_PROCESS(fifoparaminherit);
    fifoparaminherit(const char* name, int SizeOfData) : fifoparam<T>(name, SizeOfData) 
	{
		SC_METHOD(almost_method);
		sensitive << push_pointer << pop_pointer << push_over << pop_over;
    }
};


template <typename T>
void fifoparaminherit<T>::almost_method()
{
		if((push_pointer.read() - pop_pointer.read()) == 1)
		{
			if(push_over.read() == pop_over.read())
			{
				almost_empty = 1;
				almost_full = 0;				
			}	
		}
		else if((pop_pointer.read() - push_pointer.read()) == 1)
		{
			if(push_over.read() != pop_over.read())
			{
				almost_empty = 0;
				almost_full = 1;				
			}	
		}
		else if((pop_pointer.read() - push_pointer.read()) == size-1)
		{
			if(push_over.read() != pop_over.read())
			{
				almost_empty = 1;
				almost_full = 0;				
			}	
		}
		else if((push_pointer.read() - pop_pointer.read()) == size-1)
		{
			if(push_over.read() == pop_over.read())
			{
				almost_empty = 0;
				almost_full = 1;				
			}	
		}
		else
		{
				almost_empty = 0;
				almost_full = 0;		
		}
}
