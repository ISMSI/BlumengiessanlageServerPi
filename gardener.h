#ifndef GARDENER_H
#define GARDENER_H

#include <thread>         // std::thread
#include <chrono>
#include <iostream>

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
    std::thread myThread;

    static void cycle(void* data);
    static bool timeToWarter(Warehouse& Warehouse);
    static bool waterThePlants(Warehouse& Warehouse);
    static bool emergencyStop();
    static bool emergencyAlert();
    static bool furtherRequests();
    static bool taskOnDemand();
    static bool endOfTheWorkDay();

    public:
    Gardener(Warehouse warehouse);
    ~Gardener();

    

};


#endif //GARDENER_H