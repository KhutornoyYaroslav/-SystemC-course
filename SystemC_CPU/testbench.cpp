#include "main_module.h"

int sc_main(int argc, char* argv[]) 
{
    sc_clock clock("clock", 2, SC_NS);
    sc_signal<bool> reset;
    sc_signal<bool> out_mpu_error;

    // Connect the DUT
    main_module CPU("CPU");
	CPU.clock(clock);
	CPU.reset(reset);
	CPU.out_mpu_error(out_mpu_error);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("all_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
	sc_trace(wf, out_mpu_error, "out_mpu_error");

    //Test code
    reset = 1;
    cout << "@" << sc_time_stamp() << " Asserting sync reset\n" << endl;
    sc_start(1, SC_NS);
    reset = 0;

	////Для программы фильтрации
	//int start_adr = 3400;
	//int num_el = 81;

	//Для программы умножения
	//int start_adr = 2000;
	//int num_el = 20;

	//Для программы сортировки
	int start_adr = 2500;
	int num_el = 76;

	cout << "-------RAM-before------" << endl;
	for(int i=start_adr; i < start_adr+num_el; i++)
	{
		cout << "ram_memory["<<i<<"] = " << CPU.ram_comp.memory[i] << endl;
	}
	cout << "----------------------" << endl;


	while((CPU.stop != true) && (out_mpu_error != true))
	{
		sc_start(1, SC_NS);
	}

	if(out_mpu_error == true)
	{
		cout << "MPU error!" << endl;
	}
	if(CPU.stop == true)
	{
		cout << "CPU stopped!" << endl;
	}

	cout << "-------RAM-after------" << endl;
	for(int i=start_adr; i < start_adr+num_el; i++)
	{
		cout << "ram_memory["<<i<<"] = " << CPU.ram_comp.memory[i] << endl;
	}
	cout << "----------------------" << endl;

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}