#include "MEM.h"

void MEM::mem_cthread()
{
	out_type_of_instr.write(15);
	mem_write_enable.write(false);
	mem_read_enable.write(false);
	ready.write(false);

	wait();

	while (true)
	{
		if(enable == true)
		{
			out_type_of_instr.write(in_type_of_instr.read());
			out_adrress_ron_result.write(in_adrress_ron_result.read());
			mem_adress.write(in_adrress_mem.read());
			data_to_mem.write(data_from_exec.read());
			data_to_gpio.write(data_from_exec.read());

			switch(in_type_of_instr.read())
			{
				case 2: //LOAD
				to_gpio_in.write(false);
				to_gpio_out.write(false);
				mem_write_enable.write(false);
				mem_read_enable.write(true);
				ready.write(false);
				wait();

				to_gpio_in.write(false);
				to_gpio_out.write(false);
				mem_write_enable.write(false);
				mem_read_enable.write(false);
				while(mem_ack.read() == false)
				{
					wait();
				}
				out_data.write(data_from_mem.read());
				ready.write(true);
				break;

				case 3: //STOR
				out_data.write(data_from_exec.read());
				to_gpio_in.write(false);
				to_gpio_out.write(false);
				mem_write_enable.write(true);
				mem_read_enable.write(false);
				ready.write(false);
				wait();

				to_gpio_in.write(false);
				to_gpio_out.write(false);
				mem_write_enable.write(false);
				mem_read_enable.write(false);
				while(mem_ack.read() == false)
				{
					wait();
				}
				ready.write(true);
				break;

				case 13: //IN
				mem_write_enable.write(false);
				mem_read_enable.write(false);
				to_gpio_in.write(true);
				to_gpio_out.write(false);
				ready.write(false);
				wait();

				mem_write_enable.write(false);
				mem_read_enable.write(false);
				to_gpio_in.write(false);
				to_gpio_out.write(false);
				while(from_gpio_ack.read() == false)
				{
					wait();
				}
				out_data.write(data_from_gpio.read());
				ready.write(true);
				break;

				case 14: //OUT
				out_data.write(data_from_exec.read());
				mem_write_enable.write(false);
				mem_read_enable.write(false);
				to_gpio_in.write(false);
				to_gpio_out.write(true);
				ready.write(false);
				wait();

				mem_write_enable.write(false);
				mem_read_enable.write(false);
				to_gpio_in.write(false);
				to_gpio_out.write(false);
				while(from_gpio_ack.read() == false)
				{
					wait();
				}
				ready.write(true);
				break;

				default: //OTHERS
				ready.write(true);
				mem_write_enable.write(false);
				mem_read_enable.write(false);
				to_gpio_in.write(false);
				to_gpio_out.write(false);
				out_data.write(data_from_exec.read());
				break;
			}
		}

	wait();
	}
}