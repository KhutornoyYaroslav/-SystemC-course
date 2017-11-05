#include "L1.h"

void L1::signal_compiler()
{
	isempty = empty[const int(in_adrress.read().range(width-1,0))].read();
	isvalid = (in_adrress.read() >> width) == tag[const int(in_adrress.read().range(width-1,0))].read();
	adrress_l1 = in_adrress.read().range(width-1,0);
	adrress_ram = in_adrress.read();
	tag_value = in_adrress.read() >> width;
}

void L1::state_switcher()
{  
	for (int u=0; u<size; u++)
	{
		empty[u] = true;
		tag[u] = 60; //Разобраться
	}

	state = 5;
	wait();

	//state 8 - задержка для начальной инициализации тэгов
	//state 0 - когда ничего не надо делать
	//state 1 - write и верный регион
	//state 2 - read и верный регион
	//state 6 - неверный регион, загружаем новую строку кэша
	//state 8 - неверный регион, выгружаем текущую строку кэша

	while(true)
	{
		switch(state.read())
		{
			case 5:
				state = 0;
				wait();
				break;

			case 0: 

				i = 0;
				hold_write_enable = in_write_enable.read();
				hold_read_enable = in_read_enable.read();

				if(in_write_enable.read() == true && in_read_enable.read() == false && isvalid.read() == true && isempty == false)  
					state = 1;
				else if(in_write_enable.read() == false && in_read_enable.read() == true && isvalid.read() == true && isempty == false)   
					state = 2;
				else if(in_write_enable.read() == true && in_read_enable.read() == false && isvalid.read() == false && isempty == false)   
					state = 8;
				else if(in_write_enable.read() == false && in_read_enable.read() == true && isvalid.read() == false && isempty == false)   
					state = 8;
				else if(in_write_enable.read() == true && in_read_enable.read() == false && isvalid.read() == true && isempty == true)  
					state = 6;
				else if(in_write_enable.read() == false && in_read_enable.read() == true && isvalid.read() == true && isempty == true)   
					state = 6;
				else if(in_write_enable.read() == true && in_read_enable.read() == false && isvalid.read() == false && isempty == true)   
					state = 6;
				else if(in_write_enable.read() == false && in_read_enable.read() == true && isvalid.read() == false && isempty == true)   
					state = 6;
				else
					state = 0;
				break;


			case 1:		
				tag[const int(adrress_l1.read())].write(tag_value.read());
				empty[const int(adrress_l1.read())] = false;
				memory[const int(adrress_l1.read())].write(in_data.read());
				state = 0;
				break;

			case 2: 
				state = 0;
				break;

			case 6:	
			if(i < l1_length)
			{
				if(in_ram_ack.read() == true)
				{
					tag[const int(adrress_l1.read() + i.read())].write((in_adrress.read() + i.read()) >> width);
					empty[const int(adrress_l1.read() + i.read())] = false;
					memory[const int(adrress_l1.read() + i.read())].write(in_ram_data.read());
					state = 7;
				}
				else
					state = 6;
			}
			else
			{
				if(in_ram_ack.read() == true)
				{
					if(hold_write_enable.read() == true && hold_read_enable.read() == false)
					{
						state = 1; 
					}
					else
					{
						state = 2; 
					}
					i = 0;//
					tag[const int(adrress_l1.read() + i.read())].write((in_adrress.read() + i.read()) >> width);
					empty[const int(adrress_l1.read() + i.read())] = false;    
					memory[const int(adrress_l1.read() + i.read())].write(in_ram_data.read());											
				}
				else
					state = 6;
			}
			break;
			
			case 7:
				i = i.read() + 1;
				state = 6;
				break;


			case 8:
			if(i < l1_length)
			{
				if(in_ram_ack.read() == true) 
				{
					empty[const int(adrress_l1.read() + i.read())] = true;
					state = 9;
					wait();
				}
				else
					state = 8;
			}
			else
			{
				if(in_ram_ack.read() == true) 
				{
					i = 0;
					empty[const int(adrress_l1.read() + i.read())] = true;
					state = 6;
					wait();
				}
				else
					state = 8;			
	
			}
			break;


			case 9:
				i = i.read() + 1;
				state = 8;
				break;


			default:
				state = 0;
				break;
		}

	wait();
	}
}


void L1::post_state()  
{
 

    switch(state.read())
		{
			case 0:
				out_ack.write(false);
				out_ram_write_enable.write(false);
				out_ram_read_enable.write(false);
				out_ram_adrress.write(in_adrress.read());
				out_data.write(memory[const int(adrress_l1.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read())]);
				break;

			case 1:
				out_ack.write(true);
				out_ram_write_enable.write(false);
				out_ram_read_enable.write(false);
				out_ram_adrress.write(in_adrress.read());
				out_data.write(memory[const int(adrress_l1.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read())]);
				break;

			case 2:
				out_ack.write(true);
				out_ram_write_enable.write(false);
				out_ram_read_enable.write(false);
				out_ram_adrress.write(in_adrress.read());
				out_data.write(memory[const int(adrress_l1.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read())]);
				break;

			case 6:
				out_ack.write(false);
				out_ram_write_enable.write(false); 
				out_ram_read_enable.write(true);
				out_ram_adrress.write(adrress_ram.read() + i.read());
				out_data.write(memory[const int(adrress_l1.read() + i.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read() + i.read())]);
				break;
				
			case 8:
				out_ack.write(false);
				out_ram_write_enable.write(true);
				out_ram_read_enable.write(false);
				out_ram_adrress.write(adrress_l1.read() + i.read() + size*tag[const int(adrress_l1.read() + i.read())].read());
				out_data.write(memory[const int(adrress_l1.read() + i.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read() + i.read())]);
				break;


			case 9:
			case 7:
			case 5:
			default:
				out_ack.write(false);
				out_ram_write_enable.write(false);
				out_ram_read_enable.write(false);
				out_ram_adrress.write(in_adrress.read());
				out_data.write(memory[const int(adrress_l1.read())]);
				out_ram_data.write(memory[const int(adrress_l1.read())]);
				break;
		}
}