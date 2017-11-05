
#include "systemc.h"
#include "register.h"

int sc_main(int argc, char* argv[]) 
{
    sc_clock clock("clock", 4, SC_NS);
    sc_signal<bool> reset;
    sc_signal<bool> areset;   
    sc_signal<bool> load;
    sc_signal<bool> register_in;   
    sc_signal<bool> register_out;       
    sc_signal<sc_uint<8> > register_data;
    sc_signal<sc_uint<8> > load_data;
    
    int i = 0;

    // Connect the DUT
    eightbit_register test_register("test_register");
    test_register.clock(clock);
    test_register.reset(reset);
    test_register.areset(areset);    
    test_register.load(load);    
    test_register.register_in(register_in);
    test_register.register_out(register_out);
    test_register.register_data(register_data);
    test_register.load_data(load_data);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("register_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, areset, "areset");    
    sc_trace(wf, register_in, "din");
    sc_trace(wf, register_out, "dout");    
    sc_trace(wf, register_data, "register_data");
    sc_trace(wf, load, "load");
    sc_trace(wf, load_data, "load_data");
    
    //Test code
    reset = 0;
    areset = 1;
    cout << "@" << sc_time_stamp() << " Asserting async reset\n" << endl;

    sc_start(6, SC_NS);
    areset = 0; 
    cout << "@" << sc_time_stamp() << " De-Asserting async reset\n" << endl;
    
    cout << "@" << sc_time_stamp() << " Register_in = 1 " << endl;
    register_in = 1;
    sc_start(4, SC_NS);
    assert(register_data.read() == 128);
    cout << endl;
    
    cout << "@" << sc_time_stamp() << " Register_in = 1 " << endl;
    register_in = 1;
    sc_start(4, SC_NS);
    assert(register_data.read() == 192);
    cout << endl;
    
    cout << "@" << sc_time_stamp() << " Register_in = 0 " << endl;   
    register_in = 0;
    sc_start(4, SC_NS);
    assert(register_data.read() == 96);
    cout << endl;
    
    cout << "@" << sc_time_stamp() << " Register_in = 0 " << endl;   
    register_in = 0;
    sc_start(4, SC_NS);
    assert(register_data.read() == 48);    
    cout << endl;  
       
    reset = 1; 
    cout << "@" << sc_time_stamp() << " Asserting sync reset\n" << endl;
    sc_start(4, SC_NS); 
    assert(register_data.read() == 0);
    
    reset = 0;  
    load_data = 25;
    load = 1;
    cout << "@" << sc_time_stamp() << " Asserting load\n" << endl;    
    sc_start(4, SC_NS);
    assert(register_data.read() == load_data);  
    
    load = 0;
    sc_start(12, SC_NS);   
    
    areset = 1;
    cout << "@" << sc_time_stamp() << " Asserting async reset\n" << endl;
    sc_start(5, SC_NS);
    areset = 0; 
    cout << "@" << sc_time_stamp() << " De-Asserting async reset\n" << endl;
 
    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0; 
}
