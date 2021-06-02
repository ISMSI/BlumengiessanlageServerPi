#ifndef GARDENER_H
#define GARDENER_H

#include <pthread.h>         // std::thread
#include <thread>
#include <chrono>
#include <iostream>
#include <signal.h>

#include "warehouse.h"

class Gardener
{
private:
    struct ThreadData 
    {
        //hardwarecomm
        Warehouse& warehouse;
        //multiserver
    };

    ThreadData myThreadData;
    pthread_t myThread;

    static void* cycle(void* data);
    static bool timeToWarter(Warehouse& Warehouse);
    static bool waterThePlants(Warehouse& Warehouse);
    static bool emergencyStop();
    static bool emergencyAlert();
    static bool furtherRequests(Warehouse& warehouse);
    static bool taskOnDemand(Warehouse& warehouse);
    static bool endOfTheWorkDay(Warehouse& warehouse);

    public:
    Gardener(Warehouse& warehouse);
    ~Gardener();

    

};


#endif //GARDENER_H