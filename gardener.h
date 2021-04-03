#ifndef GARDENER_H
#define GARDENER_H

#include <thread>         // std::thread
#include <chrono>
#include <iostream>

class Gardener
{
private:
    struct ThreadData 
    {
        //hardwarecomm
        //warehouse
        //multiserver
    };

    ThreadData myThreadData;
    std::thread myThread;

    static void cycle(void* data);
    static bool timeToWarter();
    static bool waterThePlants();
    static bool emergencyStop();
    static bool emergencyAlert();
    static bool furtherRequests();
    static bool taskOnDemand();
    static bool endOfTheWorkDay();

    public:
    Gardener();
    ~Gardener();

    

};


#endif //GARDENER_H