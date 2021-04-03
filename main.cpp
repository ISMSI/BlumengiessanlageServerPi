
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <signal.h>

#include "warehouse.h"
#include "multiServer.h"
#include "hardwareComm.h"
#include "gardener.h"

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

    Warehouse warehouse;
    //MultiServer multiServer("192.168.1.13", 3134/*, warehouse*/);

    //std::thread test_th = std::thread(test);
    //test_th.join();

    /*HardwareComm comm = HardwareComm();
    std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC0) << std::endl;
    std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC1) << std::endl;
    std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC2) << std::endl;*/

    Gardener myGardner(warehouse);

    std::cout << "Wait for signals" << std::endl;
    sigwait(&signals, &sig);


    return 0;
} 