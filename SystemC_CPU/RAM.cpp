#include "RAM.h"

void RAM::ram_action_1()
{  
	out_ack_1.write(false);
    wait();
    
    while (true) 
    {
		while(in_write_enable_1 == false && in_read_enable_1 == false)
		{
			wait();
		}

		if(in_write_enable_1 == true) 
		{
			memory[const int(in_adrress_1.read())] = in_data_1.read();
		}
		else
		{
			out_data_1.write(memory[const int(in_adrress_1.read())]);
		}

		out_ack_1.write(true);
		wait();
		out_ack_1.write(false);
    };
};

void RAM::ram_action_2()
{  
	out_ack_2.write(false);
    wait();
    
    while (true) 
    {
		while(in_write_enable_2 == false && in_read_enable_2 == false)
		{
			wait();
		}

		if(in_write_enable_2 == true) 
		{
			while(in_adrress_1.read() == in_adrress_2.read())
			{
				wait();
			}
			memory[const int(in_adrress_2.read())] = in_data_2.read();
		}
		else
		{
			out_data_2.write(memory[const int(in_adrress_2.read())]);
		}

		out_ack_2.write(true);
		wait();
		out_ack_2.write(false);
    };
};

