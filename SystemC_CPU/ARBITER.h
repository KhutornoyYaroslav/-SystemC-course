
#include "systemc.h"

SC_MODULE(ARBITER) 
{
    //--------------------Ports Here-----------------------
    sc_in<bool> reset;	
	sc_in<bool> in_fetch_ready;
	sc_in<bool> in_mem_ready;
	sc_in<bool> in_branch_adrress_load_to_fecth;
	sc_out<bool> out_fetch_enable;
	sc_out<bool> out_exec_enable;
	sc_out<bool> out_decode_enable;
	sc_out<bool> out_mem_enable;
	sc_out<bool> out_reset;
	sc_in<bool> in_stop;

    //------------Local Variables Here---------------------


    //------------Code Starts Here-------------------------
    void arbiter_action();
    void arbiter_cthread();   

    //------------Constructor Here-------------------------   
    SC_CTOR(ARBITER) : 

		reset("reset"),
		in_fetch_ready("in_fetch_ready"),
		in_mem_ready("in_mem_ready"),
		in_branch_adrress_load_to_fecth("in_branch_adrress_load_to_fecth"),
		out_fetch_enable("out_fetch_enable"),
		out_exec_enable("out_exec_enable"),
		out_decode_enable("out_decode_enable"),
		out_mem_enable("out_mem_enable"),
		in_stop("in_stop")

    {
        cout << "ARBITER is now created..." << endl;

		SC_METHOD(arbiter_action);
        sensitive << in_fetch_ready << in_mem_ready << in_branch_adrress_load_to_fecth  << reset << in_stop;
    }
};