
#include "systemc.h"
#include "counter.h"

int sc_main(int argc, char* argv[]) 
{
    sc_clock clock("clock", 5, SC_NS);
    sc_signal<bool> reset;
    sc_signal<bool> areset;   
    sc_signal<bool> up_down;   
    sc_signal<sc_uint<8> > counter_data; 

    int i = 0;

    // Connect the DUT
    eightbit_counter test_counter("test_counter");
    test_counter.clock(clock);
    test_counter.reset(reset);
    test_counter.areset(areset);    
    test_counter.up_down(up_down);    
    test_counter.counter_data(counter_data);   

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("counter_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, up_down, "up_down");    
    sc_trace(wf, counter_data, "counter_data");

    //Test code
    up_down = 1;
    reset = 0;
    areset = 1;
    cout << "@" << sc_time_stamp() << " Asserting async reset\n" << endl;

    sc_start(5, SC_NS);

    areset = 0;
    up_down = 1;
    sc_start(5, SC_NS);
    assert(counter_data.read() == 1);
    cout << endl;

    sc_start(5, SC_NS);
    assert(counter_data.read() == 2);
    cout << endl;

    sc_start(5, SC_NS);
    assert(counter_data.read() == 3);
    cout << endl;

    up_down = 0;
    sc_start(5, SC_NS);
    assert(counter_data.read() == 2);
    cout << endl;

    up_down = 1;
    sc_start(4, SC_NS);
    assert(counter_data.read() == 3);
    cout << endl;

	reset = 1;
    sc_start(5, SC_NS);
    assert(counter_data.read() == 0);
    cout << endl;

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}
