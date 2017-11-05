#include "WB.h"

void WB::wb_method()
{
		out_data_ron_result.write(in_data.read());
		out_adrress_ron_result.write(in_adrress_ron_result.read());

		switch(in_type_of_instr.read())
		{	
			case 0:
			case 1:
			case 2:
			case 4:
			case 5:
			out_write_ena.write(true);
			break;

			default:
			out_write_ena.write(false);
			break;
		}
}
