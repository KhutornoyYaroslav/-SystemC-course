#include "systemc.h"

SC_MODULE(MPU) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
	sc_in<bool> reset;
	sc_in<sc_uint<32> > in_adrress_1;
	sc_in<sc_uint<32> > in_adrress_2;
	sc_in<bool> in_write_enable_1;
	sc_in<bool> in_read_enable_1;
	sc_in<bool> in_write_enable_2;
	sc_in<bool> in_read_enable_2;
	sc_out<bool> out_write_enable_1;
	sc_out<bool> out_read_enable_1;
	sc_out<bool> out_write_enable_2;
	sc_out<bool> out_read_enable_2;
	sc_out<bool> out_error;

    //------------Local Variables Here---------------------
	sc_signal<bool> table_read_enable[16];
	sc_signal<bool> table_write_enable[16];
	sc_signal<sc_uint<32> > table_start_adrress[16];
	sc_signal<sc_uint<32> > table_end_adrress[16];
	sc_signal<bool> out_error_1;
	sc_signal<bool> out_error_2;
	int i, j;

    //------------Code Starts Here-------------------------
	void mpu_cthread_1();
	void mpu_cthread_2();
	void signal_compiler();

    //------------Constructor Here-------------------------   
    SC_CTOR(MPU) : 

		clock("clock"), 
		reset("reset"),
		in_adrress_1("in_adrress_1"), 
		in_adrress_2("in_adrress_2"), 
		in_write_enable_1("in_write_enable_1"), 
		in_read_enable_1("in_read_enable_1"), 
		in_write_enable_2("in_write_enable_2"), 
		in_read_enable_2("in_read_enable_2"), 
		out_write_enable_1("out_write_enable_1"), 
		out_read_enable_1("out_read_enable_1"), 
		out_write_enable_2("out_write_enable_2"), 
		out_read_enable_2("out_read_enable_2"), 
		out_error("out_error")

    {
        cout << "MPU is now created..." << endl;

        SC_CTHREAD(mpu_cthread_1, clock.pos());
        reset_signal_is(reset, true);

        SC_CTHREAD(mpu_cthread_2, clock.pos());
        reset_signal_is(reset, true);

		SC_METHOD(signal_compiler);
        sensitive << out_error_1 << out_error_2;
    }
};