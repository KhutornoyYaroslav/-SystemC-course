
#include "systemc.h"
#include "math.h"

SC_MODULE(L1) 
{
    //--------------------Ports Here-----------------------
	sc_in_clk clock; 
    sc_in<bool> reset; 
	sc_in<sc_uint<32> > in_adrress;
	sc_in<sc_int<32> > in_data;
	sc_out<sc_int<32> > out_data;
	sc_in<bool> in_read_enable; 
	sc_in<bool> in_write_enable; 
	sc_out<bool> out_ack;
	sc_out<sc_uint<32> > out_ram_adrress; 
	sc_in<sc_int<32> > in_ram_data; 
	sc_out<sc_int<32> > out_ram_data; 
	sc_out<bool> out_ram_write_enable; 
	sc_out<bool> out_ram_read_enable; 
	sc_in<bool> in_ram_ack;

    //------------Local Variables Here---------------------
	sc_signal<sc_uint<4> > state;
	sc_signal<sc_int<32> > memory[256]; //менять в зависимости от width
	sc_signal<sc_int<27> > tag[256]; //менять в зависимости от width
	sc_signal<bool> empty[256]; //менять в зависимости от width
	sc_signal<sc_uint<8> > adrress_l1; //Изменить разрядность в зависимости от width
	sc_signal<sc_uint<32> > adrress_ram;
	sc_signal<sc_int<27> > tag_value;  //менять в зависимости от width
	sc_signal<int> i;
	sc_signal<bool> isempty;
	sc_signal<bool> isvalid;
	sc_signal<bool> hold_write_enable;
	sc_signal<bool> hold_read_enable;
	int width;
	int size;
	int l1_length;

    //------------Code Starts Here-------------------------
	void signal_compiler();
    void state_switcher();
	void post_state();

    //------------Constructor Here-------------------------   
    SC_CTOR(L1) : 

		clock("clock"),
		reset("reset"),
		in_adrress("in_adrress"),
		in_data("in_data"),
		out_data("out_data"),
		in_read_enable("in_read_enable"),
		in_write_enable("in_write_enable"),
		out_ack("out_ack"),
		out_ram_adrress("out_ram_adrress"),
		in_ram_data("in_ram_data"),
		out_ram_data("out_ram_data"),
		out_ram_write_enable("out_ram_write_enable"),
		out_ram_read_enable("out_ram_read_enable"),
		in_ram_ack("in_ram_ack")

    {
		l1_length = 0; //Разобраться
		width = 8;
		size = pow(2,width);

        cout << "L1 is now created... " << "L1 size is " << size << "..." << endl;

        SC_CTHREAD(state_switcher, clock.pos());
        reset_signal_is(reset, true);

        SC_METHOD(post_state);
        sensitive << state << in_adrress << in_data << in_read_enable << in_write_enable;

		SC_METHOD(signal_compiler);
        sensitive << in_adrress << state;
    }
};