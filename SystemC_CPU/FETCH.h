#include "systemc.h"

SC_MODULE(FETCH) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> enable;
    sc_in<bool> reset;
	sc_out<bool> ready;
	sc_out<sc_uint<32> > out_adrress_to_mem;
	sc_in<sc_int<32> > in_instruction_from_mem;
	sc_in<bool> in_ack_from_mem;
	sc_out<sc_int<32> > out_instruction_to_decode;
	sc_in<sc_uint<25> > in_branch_adrress_from_exec;
	sc_in<bool> in_branch_adrress_load_from_exec;
	sc_out<bool> fetch_read_enable; 
	sc_out<bool> fetch_write_enable; 

    //------------Local Variables Here---------------------
	sc_uint<32> PC;
	sc_signal<bool> flag;

    //------------Code Starts Here-------------------------
    void fetch_cthread();

    //------------Constructor Here-------------------------   
    SC_CTOR(FETCH) : 

		clock("clock"), 
		enable("enable"),
		reset("reset"),
		ready("ready"),
		out_adrress_to_mem("out_adrress_to_mem"),
		in_instruction_from_mem("in_instruction_from_mem"),
		out_instruction_to_decode("out_instruction_to_decode"),
		in_ack_from_mem("in_ack_from_mem"),
		in_branch_adrress_from_exec("in_branch_adrress_from_exec"),
		in_branch_adrress_load_from_exec("in_branch_adrress_load_from_exec"),
		fetch_read_enable("fetch_read_enable"), 
		fetch_write_enable("fetch_write_enable") 

    {
        cout << "FETCH is now created..." << endl;

        SC_CTHREAD(fetch_cthread, clock.pos());        
        reset_signal_is(reset, true);   
    }
};