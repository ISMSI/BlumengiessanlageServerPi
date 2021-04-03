#include "gardener.h"


Gardener::Gardener(Warehouse warehouse) : myThreadData{warehouse}
{
    myThread = std::thread(cycle, static_cast<void*>(&myThreadData) ); 
}

Gardener::~Gardener()
{
    myThread.join();
}

void Gardener::cycle(void* data)
{
    ThreadData* threadData = static_cast<ThreadData*>(data);
    Warehouse& warehouse = threadData->warehouse;

    while(true)
    {
        if (timeToWarter(warehouse))
        {
            if (!waterThePlants(warehouse))
            {
                if (!emergencyStop() )
                {
                    emergencyAlert();
                }
            }
        }

        if (furtherRequests())
        {
            taskOnDemand();
        }

        if (endOfTheWorkDay())
        {
            taskOnDemand();
        }
    }
}

bool Gardener::timeToWarter(Warehouse& warehouse)
{
    bool warterOnTime;
    bool wateredToday;
    uint16_t hour;
    uint16_t minute;
    uint16_t lst_year;
    uint16_t lst_month;
    uint16_t lst_day;
    double lastWatering;
    bool ret;

    ret = warehouse.takeOut("waterOnTime",warterOnTime);
    ret = warehouse.takeOut("Time:hour",hour);
    ret = warehouse.takeOut("Time:minute",minute);
    ret = warehouse.takeOut("lastWateringDate:year",lst_year);
    ret = warehouse.takeOut("lastWateringDate:month",lst_month);
    ret = warehouse.takeOut("lastWateringDate:day",lst_day);


    if (ret && warterOnTime)
    {
        time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        tm local_tm = *localtime(&tt);

        if(local_tm.tm_mday = lst_day) 
        {
            return false;
        }

        if(local_tm.tm_mon = lst_month)
        {
            return false;
        }

        if(local_tm.tm_mon = lst_year) 
        {
            return false;
        }

        if (local_tm.tm_hour < hour)
        {
            return false;
        }

        if (local_tm.tm_min < minute)
        {
            return false;
        }

        std::cout<< "timeToWarter" << std::endl;        

        return true;
        
    }
    return false;
}

bool Gardener::waterThePlants(Warehouse& warehouse)
{
    uint16_t lst_year;
    uint16_t lst_month;
    uint16_t lst_day;

    std::cout<< "waterThePlants: true" << std::endl;

    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm local_tm = *localtime(&tt);

    lst_year = local_tm.tm_year;
    lst_month = local_tm.tm_mon;
    lst_day = local_tm.tm_mday;

    warehouse.putIn("lastWateringDate:year",lst_year);
    warehouse.putIn("lastWateringDate:month",lst_month);
    warehouse.putIn("lastWateringDate:day",lst_day);

    return true;
}

bool Gardener::emergencyStop()
{
    std::cout<< "emergencyStop: true" << std::endl;
    return true;
}

bool Gardener::emergencyAlert()
{
    std::cout<< "emergencyAlert: true" << std::endl;
    return true;
}

bool Gardener::furtherRequests()
{
    std::cout<< "furtherRequests: false" << std::endl;
    return false;
}

bool Gardener::taskOnDemand()
{
    std::cout<< "taskOnDemand: true" << std::endl;
    return true;
}

bool Gardener::endOfTheWorkDay(/*warehouse*/)
{
    std::cout<<"Current Time :: ";

    time_t timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&timeStamp) << std::endl;
  
    std::chrono::system_clock::time_point timePt = std::chrono::system_clock::now() + std::chrono::seconds(10);
   
    std::cout << "Sleeping Until :: "; 
    
    
    timeStamp = std::chrono::system_clock::to_time_t(timePt);
    std::cout << std::ctime(&timeStamp) << std::endl;
  
    std::this_thread::sleep_until(timePt);
  
    std::cout<<"Woke up...Current Time :: ";
    
    timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&timeStamp) << std::endl;

    return true;
}