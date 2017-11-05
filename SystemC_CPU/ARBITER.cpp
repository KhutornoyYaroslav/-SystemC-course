#include "ARBITER.h"

void ARBITER::arbiter_action() 
{   
	////сделать нормально!
	if(in_fetch_ready == true && in_mem_ready == true && in_stop == false)
	{
		out_fetch_enable = true;
		out_exec_enable = true;
		out_decode_enable = true;
		out_mem_enable = true;
	}
	else if(in_fetch_ready == false && in_mem_ready == true && in_stop == false)
	{
		out_fetch_enable = true;
		out_exec_enable = false;
		out_decode_enable = false;
		out_mem_enable = false;
	}
	else if(in_fetch_ready == true && in_mem_ready == false && in_stop == false)
	{
		out_fetch_enable = false;
		out_exec_enable = false;
		out_decode_enable = false;
		out_mem_enable = true;
	}
	else if(in_fetch_ready == false && in_mem_ready == false && in_stop == false)
	{
		out_fetch_enable = true;
		out_exec_enable = false;
		out_decode_enable = false;
		out_mem_enable = true;
	}
	else //if(in_stop == true)
	{
		out_fetch_enable = false;
		out_exec_enable = false;
		out_decode_enable = false;
		out_mem_enable = false;		
	};


	if(in_branch_adrress_load_to_fecth == true || reset == true)
	{
		out_reset = true;
	}
	else
	{
		out_reset = false;
	};

}
