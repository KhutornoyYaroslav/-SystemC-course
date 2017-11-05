#include "RON.h"

void RON::ron_action() 
{   
    wait();
    
    while (true) 
    {
		if(enable == true)
		{
			out_data_ron_1 = data[const int(in_adrress_ron_1.read())];
			out_data_ron_2 = data[const int(in_adrress_ron_2.read())];

			if(in_write_enable_result.read() == true)
			{
				data[const int(in_adrress_ron_result.read())] = in_data_ron_result.read();
			}
		}
		
		wait();
    };
}
