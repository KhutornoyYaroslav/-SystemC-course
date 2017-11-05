#include "execute.h"

void EXECUTE::execute_alu()
{   
        switch(in_type_of_operation.read())
		{
			case 1: //сложение
				tmp_result = in_operand_1.read() + sig_operand_2.read();
				sig_result_alu.write(static_cast<int>(tmp_result.range(31,0)));
				out_c_flag.write(tmp_result.bit(32));
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;

			case 2: //вычитание
				tmp_result = in_operand_1.read() - sig_operand_2.read();
				sig_result_alu.write(static_cast<int>(tmp_result.range(31,0)));
				out_c_flag.write(tmp_result.bit(32));
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;

			case 3: //умножение	
				tmp_result = static_cast<sc_int<64> >(in_operand_1.read()) * static_cast<sc_int<64> >(sig_operand_2.read());	
				sig_result_alu.write(static_cast<int>(tmp_result.range(31,0)));
				out_c_flag.write(false);
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;

			case 4: //сдвиг влево		
				tmp_result = in_operand_1.read();
				sig_result_alu.write(static_cast<int>((tmp_result.bit(31), tmp_result.range(29,0), 0)));
				out_c_flag.write(false);
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;

			case 5: //сдвиг вправо	
				tmp_result = in_operand_1.read();
				sig_result_alu.write(static_cast<int>((tmp_result.bit(31), 0, tmp_result.range(30,1))));
				out_c_flag.write(false);
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;

			default:
				sig_result_alu.write(static_cast<int>(tmp_result.range(31,0)));
				out_c_flag.write(tmp_result.bit(32));
				out_z_flag.write(!(tmp_result.range(31,0).or_reduce()));
				break;
    };
};

void EXECUTE::execute_pre_alu()
{ 
	switch(in_type_of_instr.read())
	{
		case 1:
			sig_operand_2 = 1;
			break;

		default:
			sig_operand_2 = in_operand_2.read();
			break;
	};
};

void EXECUTE::execute_buffer() 
{
	out_branch_adrress_load_to_fecth.write(false);
	out_type_of_instr.write(15);
    wait();
    
    while (true) 
    {					
		out_branch_adrress_load_to_fecth.write(false);

		if(enable == true)
		{	
			out_adrress_ron_result.write(in_adrress_ron_result);
			out_adrress_mem.write((sc_uint<32> )in_operand_1.read());
			out_branch_adrress_to_fetch.write(in_branch_adrress.read());

			switch(in_type_of_instr.read())
			{	
				case 0: //ALU
				case 1: //ALU
				case 2: //LOAD
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(false);
					break;

				case 3: //STORE
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(in_operand_2.read());
					out_branch_adrress_load_to_fecth.write(false);//
					out_stop.write(false);
					break;

				case 4: //MOV
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(in_operand_1.read());	
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(false);
					break;

				case 5: //DIRECT
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write((0,0,0,0,0,0,0,0,0,0,0,0,in_direct_data.read()));
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(false);
					break;

				case 6: //JMP
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(true);
					out_stop.write(false);
					break;

				case 7: //JNZ
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_stop.write(false);
					if(out_z_flag.read() == false)
						out_branch_adrress_load_to_fecth.write(true);
					else
						out_branch_adrress_load_to_fecth.write(false);
					break;

				case 8: //JZ
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_stop.write(false);
					if(out_z_flag.read() == true)
						out_branch_adrress_load_to_fecth.write(true);
					else
						out_branch_adrress_load_to_fecth.write(false);
					break;

				case 9: //JNC
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_stop.write(false);
					if(out_c_flag.read() == false)
						out_branch_adrress_load_to_fecth.write(true);
					else
						out_branch_adrress_load_to_fecth.write(false);
					break;

				case 10: //JC
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_stop.write(false);
					if(out_c_flag.read() == true)
						out_branch_adrress_load_to_fecth.write(true);
					else
						out_branch_adrress_load_to_fecth.write(false);
					break;

				case 12: //STOP
					out_type_of_instr.write(15);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(true);
					break;

				case 13: //IN
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(true);
					break;

				case 14: //OUT
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(in_operand_1.read());	
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(true);
					break;

				case 15: //NOPE
					out_type_of_instr.write(15);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(false);
					break;

				default:
					out_type_of_instr.write(in_type_of_instr);
					out_result_main.write(sig_result_alu.read());
					out_branch_adrress_load_to_fecth.write(false);
					out_stop.write(false);
					break;
			};	
		}
		wait();
	};
};