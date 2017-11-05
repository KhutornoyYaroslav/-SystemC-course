
#include "systemc.h"
#include "SM.h"

int sc_main(int argc, char* argv[]) 
{
    sc_clock clock("clock", 5, SC_NS);
    sc_signal<bool> areset;
    sc_signal<sc_uint<2> > in;
    sc_signal<sc_uint<2> > y;
    sc_signal<sc_uint<2> > state;

    int i = 0;
    // Connect the DUT
    state_machine test_SM("test_SM");
    test_SM.clock(clock);
    test_SM.areset(areset);
    test_SM.in(in);
    test_SM.y(y);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("SM_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, areset, "areset");
    sc_trace(wf, in, "in");
    sc_trace(wf, y, "y");
    sc_trace(wf, test_SM.state, "state");

    areset = 1; // Assert the reset
    cout << "@" << sc_time_stamp() << " Asserting areset\n" << endl;
    sc_start(2.5, SC_NS);

    areset = 0; // De-assert the reset
    cout << "@" << sc_time_stamp() << " De-Asserting areset\n" << endl;
    sc_start(1.5, SC_NS);

	in = 2;
    sc_start(5, SC_NS);
    assert(y.read() == 2);

    in = 3;
    sc_start(5, SC_NS);
    assert(y.read() == 3);

    in = 0;
    sc_start(5, SC_NS);
    assert(y.read() == 3);

    in = 1;
    sc_start(5, SC_NS);
    assert(y.read() == 3);

    in = 3;
    sc_start(5, SC_NS);
    assert(y.read() == 0);

    in = 1;
    sc_start(5, SC_NS);
    assert(y.read() == 0);

    in = 3;
    sc_start(5, SC_NS);
    assert(y.read() == 0);

    in = 2;
    sc_start(5, SC_NS);
    assert(y.read() == 3);

    in = 2;
    sc_start(5, SC_NS);
    assert(y.read() == 2);
	
//вернулись в состояние 0, обошли из 0 через 1 в 3 полностью.
//теперь проверяем диагональные переходы из 0 в 3 и обратно.

	in = 0;
    sc_start(5, SC_NS);
    assert(y.read() == 0);

	in = 0;
    sc_start(5, SC_NS);
    assert(y.read() == 2);

//теперь из 0 в 2 и обратно

	in = 1;
    sc_start(5, SC_NS);
    assert(y.read() == 1);

	in = 0;
    sc_start(5, SC_NS);
    assert(y.read() == 2);

	in = 1;
    sc_start(5, SC_NS);
    assert(y.read() == 1);

// Теперь проверяем из 0 в 2, из 2 в 2, из 2 в 3

	in = 1;
    sc_start(5, SC_NS);
    assert(y.read() == 1);

	in = 3;
    sc_start(5, SC_NS);
    assert(y.read() == 1);

	in = 2;
    sc_start(5, SC_NS);
    assert(y.read() == 0);

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0; 
}
