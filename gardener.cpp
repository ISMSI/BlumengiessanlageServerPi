#include "gardener.h"


Gardener::Gardener(Warehouse& warehouse) : myThreadData{warehouse}
{
    pthread_create(&myThread, NULL, cycle, static_cast<void*>(&myThreadData) ); 
}

Gardener::~Gardener()
{
    pthread_join(myThread, NULL);
}

void* Gardener::cycle(void* data)
{
    ThreadData* threadData = static_cast<ThreadData*>(data);
    Warehouse& warehouse = threadData->warehouse;
    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);

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
    HardwareComm& hwComm = warehouse.getHardwareComm();
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

    for (std::map<std::string, Valve>::iterator valveIt = warehouse.getFirstValve(); valveIt != warehouse.getLastValve(); ++valveIt) 
    {
        if(valveIt->second.isEnabled())
        {
            if(valveIt->second.getState() != Aktor::OFF)
            {
                std::cerr << "Valve " << valveIt->second.getName() << " is not closed!" << std::endl;
                return false;
            }

            if (hwComm.switchAktor(true, valveIt->second))
            {
                std::cout << "Valve " << valveIt->second.getName() << " opend" << std::endl;
                valveIt->second.setState(Aktor::ON);
            }

            if (warehouse.getPump().getState() != Aktor::OFF)
            {
                std::cerr << "Pump is not turned off" << std::endl;
                return false;
            }

            if (hwComm.switchAktor(true, warehouse.getPump()))
            {
                std::cout << "Pump turned on" << std::endl;
                warehouse.getPump().setState(Aktor::ON);
            }

            std::this_thread::sleep_for(std::chrono::seconds(valveIt->second.getWaterDuration_s()));

            if (warehouse.getPump().getState() == Aktor::ON)
            {
                std::cout << "Turn pump off" << std::endl;
                hwComm.switchAktor(false, warehouse.getPump());
            }

            if (valveIt->second.getState() == Aktor::ON)
            {
                std::cout << "Turn valve " << valveIt->second.getName() << " off" << std::endl;
                hwComm.switchAktor(false, valveIt->second);
            } 
        }
    }

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
    std::cout<<"Current Time :: " << std::endl;

    std::this_thread::sleep_for(std::chrono::minutes(1));

    /*time_t timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&timeStamp) << std::endl;
  
    std::chrono::system_clock::time_point timePt = std::chrono::system_clock::now() + std::chrono::seconds(60);
   
    std::cout << "Sleeping Until :: "; 
    
    
    timeStamp = std::chrono::system_clock::to_time_t(timePt);
    std::cout << std::ctime(&timeStamp) << std::endl;
  
    std::this_thread::sleep_until(timePt);
  
    std::cout<<"Woke up...Current Time :: ";
    
    timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&timeStamp) << std::endl;*/

    return true;
}