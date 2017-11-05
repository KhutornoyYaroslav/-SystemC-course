

#include "DECODE.h"

void DECODE::decode_cthread() 
{   
	out_type_of_instr.write(15);
    wait();
    
    while (true) 
    {
		if(enable == true)
		{
			out_type_of_instr = (sc_uint<4> )in_decode_instr.read().range(31,28);
			out_type_of_operation = (sc_uint<3> )in_decode_instr.read().range(27,25);
			out_adrress_ron_result = (sc_uint<5> )in_decode_instr.read().range(24,20); 
			out_direct_data = (sc_uint<20> )in_decode_instr.read().range(19,0);
			out_branch_adrress = (sc_uint<25> )in_decode_instr.read().range(24,0);
		}

		wait();
    }
}

void DECODE::decode_method()
{
	out_adrress_ron_1 = (sc_uint<5> )in_decode_instr.read().range(4,0);
	out_adrress_ron_2 = (sc_uint<5> )in_decode_instr.read().range(9,5);
}