#include "FETCH.h"

void FETCH::fetch_cthread() 
{ 
	PC = 0;
	out_adrress_to_mem = PC;
	out_instruction_to_decode.write(4026531840);
    wait();

	flag.write(false);
	fetch_write_enable.write(false);
	fetch_read_enable.write(false); 
	ready.write(false); 
	wait();

    while (true)
    {
		if(enable == true)
		{
			fetch_write_enable.write(false);
			fetch_read_enable.write(true); 
			ready.write(false);

			while(in_ack_from_mem.read() == false)
			{
				if(in_branch_adrress_load_from_exec.read() == true)
				{
					flag.write(true);
					PC = (0,0,0,0,0,0,0,in_branch_adrress_from_exec.read()) - 1;
					out_instruction_to_decode.write(4026531840);
				}
				wait();

				fetch_write_enable.write(false);
				fetch_read_enable.write(false); 
			}

			PC = PC + 1;
			ready.write(true);

			if(flag == false)
			{
				out_instruction_to_decode.write(in_instruction_from_mem.read());
			}

			flag.write(false);
			out_adrress_to_mem = PC;
		}

	wait();
    }
}

