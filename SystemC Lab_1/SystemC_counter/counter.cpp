
#include "counter.h"

void eightbit_counter::counter_action() 
{   

    mycounter = 0;
    cout << "@" << sc_time_stamp() << " :: Counter sreset " << mycounter << endl;
    counter_data.write(mycounter);
    wait();
    
    while (true) 
    {
        if(up_down.read())
        {
            mycounter++;
            cout << "@" << sc_time_stamp() << " :: Counter add " << mycounter << endl;
            counter_data.write(mycounter);
            wait();
        }        
        else
        {   
            mycounter--;
            cout << "@" << sc_time_stamp() << " :: Counter sub " << mycounter << endl;           
            counter_data.write(mycounter);
            wait();
        }
    }
}
