
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "warehouse.h"
#include "multiServer.h"
#include <signal.h>
#include "hardwareComm.h"

void static test()
{
    for(int i = 10; i >= 0 ; i--)
   {
       std::cout << "Countdown: " << i << std::endl;
   } 
}


int main()
{
    sigset_t signals;
    int sig;

    sigemptyset(&signals);
    sigaddset(&signals, SIGINT);
    sigaddset(&signals, SIGTERM);



    std::cout << "Hello World, Sweety!" << std::endl;

    //Warehouse warehouse = Warehouse();
    //MultiServer multiServer("192.168.1.13", 3134/*, warehouse*/);

    //std::thread test_th = std::thread(test);
    //test_th.join();

    HardwareComm comm = HardwareComm();
    comm.getSensorValue(comm.MUX0,comm.ADC1);

    //sigwait(&signals, &sig);


    return 0;
} 