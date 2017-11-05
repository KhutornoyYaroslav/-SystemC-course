#include "SM.h"

void state_machine::pre_state() 
{  
    state = 0;
    wait();

    while (true) 
	{
		switch(state.read())
		{
			case 0:

				if(in.read() == 0) state = 3;
				else if(in.read() == 3) state = 1;
				else if(in.read() == 1) state = 2;
				else state = 0;
				break;

			case 1:

				if(in.read() == 2) state = 0;
				else if(in.read() == 3) state = 3;
				else state = 1;
				break;

			case 2:

				if(in.read() == 2) state = 3;
				else if(in.read() == 0) state = 0;
				else state = 2;
				break;

			case 3:

				if(in.read() == 0)	state = 0;
				else if(in.read() == 2) state = 1;
				else state = 3;
				break;		
		}
		wait();
    }
}


void state_machine::post_state()  
{
    switch(state.read())
		{
			case 0:
				y = 2;
				break;

			case 1:
				y = 3;
				break;

			case 2:
				y = 1;
				break;

			case 3:
				y = 0;
				break;
		}
}
