
#include "register.h"

void eightbit_register::register_store() 
{   
    myregister = 0;
    register_data.write(myregister);
    wait();

    while (true) 
    {
        if(load.read())
        {
            myregister = load_data.read();
            cout << "@" << sc_time_stamp() << " :: Have load " << myregister << endl;
            register_data.write(myregister);
            wait();
        }        
        else
        {   
            register_out.write(myregister.bit(0));
            myregister = (register_in, myregister.range(7, 1));
            cout << "@" << sc_time_stamp() << " :: Have stored " << myregister << endl;
            register_data.write(myregister);
            wait();
        }
    }
}
