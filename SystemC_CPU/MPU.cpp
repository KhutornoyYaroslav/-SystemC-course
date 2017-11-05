#include "MPU.h"

void MPU::signal_compiler()
{
	out_error = out_error_1.read() || out_error_2.read();
}

void MPU::mpu_cthread_1()
{
	table_start_adrress[0] = 0;
	table_end_adrress[0] = 255;
	table_start_adrress[1] = 256;
	table_end_adrress[1] = 511;
	table_start_adrress[2] = 512;
	table_end_adrress[2] = 767;
	table_start_adrress[3] = 768;
	table_end_adrress[3] = 1023;
	table_start_adrress[4] = 1024;
	table_end_adrress[4] = 1279;
	table_start_adrress[5] = 1280;
	table_end_adrress[5] = 1535;
	table_start_adrress[6] = 1536;
	table_end_adrress[6] = 1791;
	table_start_adrress[7] = 1792;
	table_end_adrress[7] = 2047;
	table_start_adrress[8] = 2048;
	table_end_adrress[8] = 2303;
	table_start_adrress[9] = 2304;
	table_end_adrress[9] = 2559;
	table_start_adrress[10] = 2560;
	table_end_adrress[10] = 2815;
	table_start_adrress[11] = 2816;
	table_end_adrress[11] = 3071;
	table_start_adrress[12] = 3072;
	table_end_adrress[12] = 3327;
	table_start_adrress[13] = 3328;
	table_end_adrress[13] = 3583;
	table_start_adrress[14] = 3584;
	table_end_adrress[14] = 3839;
	table_start_adrress[15] = 3840;
	table_end_adrress[15] = 4095;

	table_read_enable[0] = true;
	table_write_enable[0] = false;
	table_read_enable[1] = true;
	table_write_enable[1] = false;
	table_read_enable[2] = true;
	table_write_enable[2] = false;
	table_read_enable[3] = true;
	table_write_enable[3] = false;
	table_read_enable[4] = true;
	table_write_enable[4] = true;
	table_read_enable[5] = true;
	table_write_enable[5] = true;
	table_read_enable[6] = true;
	table_write_enable[6] = true;
	table_read_enable[7] = true;
	table_write_enable[7] = true;
	table_read_enable[8] = true;
	table_write_enable[8] = true;
	table_read_enable[9] = true;
	table_write_enable[9] = true;
	table_read_enable[10] = true;
	table_write_enable[10] = true;
	table_read_enable[11] = true;
	table_write_enable[11] = true;
	table_read_enable[12] = true;
	table_write_enable[12] = true;
	table_read_enable[13] = true;
	table_write_enable[13] = true;
	table_read_enable[14] = true;
	table_write_enable[14] = true;
	table_read_enable[15] = true;
	table_write_enable[15] = true;

	wait();

	while(true)
	{
		i = 0;
		while( !((in_adrress_1.read() >= table_start_adrress[i]) && (in_adrress_1.read() <= table_end_adrress[i])) )
		{
			i++;
		}

		//Ничего нельзя
		if(table_read_enable[i] == false && table_write_enable[i] == false && in_write_enable_1 == true && in_read_enable_1 == false)
		{
			out_write_enable_1.write(false);
			out_read_enable_1.write(false);
			out_error_1.write(true);
		}
		else if(table_read_enable[i] == false && table_write_enable[i] == false && in_write_enable_1 == false && in_read_enable_1 == true)
		{
			out_write_enable_1.write(false);
			out_read_enable_1.write(false);
			out_error_1.write(true);
		}
		//Можно только читать
		else if(table_read_enable[i] == true && table_write_enable[i] == false && in_write_enable_1 == true && in_read_enable_1 == false)
		{
			out_write_enable_1.write(false);
			out_read_enable_1.write(false);
			out_error_1.write(true);
		}
		//Можно только писать
		else if(table_read_enable[i] == false && table_write_enable[i] == true && in_write_enable_1 == false && in_read_enable_1 == true)
		{
			out_write_enable_1.write(false);
			out_read_enable_1.write(false);
			out_error_1.write(true);
		}
		else
		{
			out_write_enable_1.write(in_write_enable_1.read());
			out_read_enable_1.write(in_read_enable_1.read());
			out_error_1.write(false);
		}

		wait();
	}
}

void MPU::mpu_cthread_2()
{
	wait();

	while(true)
	{
		j = 0;
		while( !((in_adrress_2.read() >= table_start_adrress[j]) && (in_adrress_2.read() <= table_end_adrress[j])) )
		{
			j++;
		}

		//Ничего нельзя
		if(table_read_enable[j] == false && table_write_enable[j] == false && in_write_enable_2 == true && in_read_enable_2 == false)
		{
			out_write_enable_2.write(false);
			out_read_enable_2.write(false);
			out_error_2.write(true);
		}
		else if(table_read_enable[j] == false && table_write_enable[j] == false && in_write_enable_2 == false && in_read_enable_2 == true)
		{
			out_write_enable_2.write(false);
			out_read_enable_2.write(false);
			out_error_2.write(true);
		}
		//Можно только читать
		else if(table_read_enable[j] == true && table_write_enable[j] == false && in_write_enable_2 == true && in_read_enable_2 == false)
		{
			out_write_enable_2.write(false);
			out_read_enable_2.write(false);
			out_error_2.write(true);
		}
		//Можно только писать
		else if(table_read_enable[j] == false && table_write_enable[j] == true && in_write_enable_2 == false && in_read_enable_2 == true)
		{
			out_write_enable_2.write(false);
			out_read_enable_2.write(false);
			out_error_2.write(true);
		}
		else
		{
			out_write_enable_2.write(in_write_enable_2.read());
			out_read_enable_2.write(in_read_enable_2.read());
			out_error_2.write(false);
		}

		wait();
	}
}