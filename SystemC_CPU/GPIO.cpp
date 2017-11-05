#include "GPIO.h"

void GPIO::gpio_cthread()
{
	ack.write(false);
	wait();

	while(true)
	{
		while(in.read() == false && out.read() == false)
		{
			wait();
		}

		if(in.read() == true && out.read() == false)
		{
			data_to_cpu.write(in_register.read());	
		}
		else
		{
			out_register.write(data_from_cpu.read());	
		}

		ack.write(true);	
		wait();
		ack.write(false);
	}
}