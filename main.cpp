
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <signal.h>
#include <chrono>

#include "warehouse.h"
#include "multiServer.h"
#include "hardwareComm.h"
#include "gardener.h"

void handler(int signo, siginfo_t *info, void *extra)
{
    exit(0);
}

int main()
{
    sigset_t signals;
    int sig;

    sigemptyset(&signals);
    sigaddset(&signals, SIGINT);

    std::cout << "Hello World, Sweety!" << std::endl;

    Warehouse warehouse;
    
    MultiServer multiServer("192.168.1.13", 3132/*, warehouse*/);
    Gardener myGardner(warehouse);

    //std::thread test_th = std::thread(test);
    //test_th.join();

    /*std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC0) << std::endl;
    std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC1) << std::endl;
    std::cout << comm.getSensorValue(comm.MUX0,comm.CHMUX0,comm.ADC1, comm.CHADC2) << std::endl;*/

    /*for (int i = 0; i < 5; i++)
    {
        comm.switchAktor(false, pump);
        comm.switchAktor(true, tmpMap["Test_VALVE"]);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));


        comm.switchAktor(true, pump);
        comm.switchAktor(false, tmpMap["Test_VALVE"]);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }*/

    

    std::cout << "Wait for signals" << std::endl;
    struct sigaction action;

    action.sa_flags = SA_SIGINFO; 
    action.sa_sigaction = handler;
    sigaction(SIGINT, &action, NULL);

    sigwait(&signals, &sig);

    return 0;
}