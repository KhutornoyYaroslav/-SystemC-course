
#include "systemc.h"
#include "fifo.h"

int sc_main(int argc, char* argv[]) 
{
    sc_clock clock("clock", 5, SC_NS);

    sc_signal<bool> sreset_n; 
    sc_signal<char> data_in;
	sc_signal<bool> push;
	sc_signal<bool> pop;

	sc_signal<char> data_out;
	sc_signal<bool> empty;
	sc_signal<bool> full;

    // Connect the DUT
    fifo test_fifo("test_fifo", 15);
    test_fifo.clock(clock);
    test_fifo.sreset_n(sreset_n);
    test_fifo.data_in(data_in);
    test_fifo.data_out(data_out);
    test_fifo.push(push);
    test_fifo.pop(pop);
    test_fifo.empty(empty);
    test_fifo.full(full);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("fifo_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, sreset_n, "sreset_n");
    sc_trace(wf, data_in, "data_in");
    sc_trace(wf, data_out, "data_out");
    sc_trace(wf, push, "push");
    sc_trace(wf, pop, "pop");
    sc_trace(wf, empty, "empty");
    sc_trace(wf, full, "full");

	//------------------------Сброс устройства------------------------
	cout << endl << "-----Reset FIFO-----" << endl;

    sreset_n = 0; 
    cout << "@" << sc_time_stamp() << " Asserting reset" << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
    sc_start(5, SC_NS);

    sreset_n = 1; 
    cout << "@" << sc_time_stamp() << " De-Asserting reset" << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
	sc_start(4, SC_NS);

	//---------------------------Только PUSH---------------------------
	cout << endl << "-----Only Push FIFO-----" << endl;

	data_in = 'a';
	for(int i = 0; i < test_fifo.size-1; i++)
	{	
		push = 1;
		pop = 0;			
		sc_start(5, SC_NS);
		cout << "@" << sc_time_stamp() << " Only Push - " << data_in << "; full = " << 
			full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && !empty);
		data_in = data_in.read() + 1;
	}

	push = 1;
	pop = 0;			
	sc_start(5, SC_NS);
	cout << "@" << sc_time_stamp() << " Only Push - " << data_in << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
	assert( full && !empty);

	data_in = data_in.read() + 1;
	push = 1;
	pop = 0;			
	sc_start(5, SC_NS);
	cout << "Trying to insert data in full FIFO:" << endl;
	cout << "@" << sc_time_stamp() << " Only Push - " << data_in << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
	assert( full && !empty);

	//---------------------------Только POP---------------------------
	cout << endl << "-----Only Pop FIFO-----" << endl;

	for(int i = 0; i < test_fifo.size-1; i++)
	{	
		push = 0;
		pop = 1;
		sc_start(5, SC_NS);	
		cout << "@" << sc_time_stamp() << " Only Pop - " << data_out.read() << "; full = " << 
			full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && !empty);

	}

	push = 0;
	pop = 1;
	sc_start(5, SC_NS);	
	cout << "@" << sc_time_stamp() << " Only Pop - " << data_out.read() << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && empty);

	push = 0;
	pop = 1;
	sc_start(5, SC_NS);	
	cout << "Trying to read data from empty FIFO:" << endl;
	cout << "@" << sc_time_stamp() << " Only Pop - " << data_out.read() << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && empty);

	//------------------Одновременно PUSH и POP------------------------
	cout << endl << "-----Push and Pop FIFO-----" << endl;
	data_in = 'f';

	push = 1;
	pop = 0;			
	sc_start(5, SC_NS);
	cout << "@" << sc_time_stamp() << " Only Push - " << data_in << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
	assert( !full && !empty);
	data_in = data_in.read() + 1;

	for(int i = 0; i < test_fifo.size-1; i++)
	{	
		push = 1;
		pop = 1;
		sc_start(5, SC_NS);	
		cout << "@" << sc_time_stamp() << " Pop and Push. Pop - " << data_out.read() <<"; Push - "<< data_in <<"; full = " << 
			full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && !empty);
		data_in = data_in.read() + 1;
	}

	push = 0;
	pop = 1;
	sc_start(5, SC_NS);	
	cout << "@" << sc_time_stamp() << " Only Pop - " << data_out.read() << "; full = " << 
		full.read() << "; empty = " << empty.read() << ";" << endl;
		assert( !full && empty);

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}
