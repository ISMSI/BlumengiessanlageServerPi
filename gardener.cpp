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

        if (furtherRequests(warehouse))
        {
            taskOnDemand(warehouse);
        }

        if (!endOfTheWorkDay(warehouse))
        {
            taskOnDemand(warehouse);
        }
    }
}

bool Gardener::timeToWarter(Warehouse& warehouse)
{
    bool warterOnTime;
    uint16_t hour;
    uint16_t minute;
    uint16_t lst_year;
    uint16_t lst_month;
    uint16_t lst_day;
    uint16_t weekDay;
    uint16_t weekDayCurr;
    double lastWatering;
    bool ret;

    ret = warehouse.takeOut("waterOnTime",warterOnTime);
    ret = warehouse.takeOut("Time:hour",hour);
    ret = warehouse.takeOut("Time:minute",minute);
    ret = warehouse.takeOut("lastWateringDate:year",lst_year);
    ret = warehouse.takeOut("lastWateringDate:month",lst_month);
    ret = warehouse.takeOut("lastWateringDate:day",lst_day);
    ret = warehouse.takeOut("Time:weekday",weekDay);//0b0000 0000 0000 0000 = 0b0000 0000 0SoMoDi MiDoFrSa

    if (ret && warterOnTime)
    {
        time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const tm local_tm = *localtime(&tt);

        weekDayCurr = (0b01000000 >> local_tm.tm_wday);

        std::cout<< "Weekday bin today: " << std::hex << weekDayCurr << "; Weekday enabled: " << std::hex << weekDay << std::dec << std::endl;
        std::cout << "day: " << local_tm.tm_mday << "month: " << local_tm.tm_mon  << "year: " << local_tm.tm_year << std::endl;


        if((weekDayCurr & weekDay) == 0)
        {
            std::cout<< "Weekday " << local_tm.tm_wday << " is not enabled." << std::endl;
            return false;
        }

        if(local_tm.tm_year < lst_year) 
        {
            std::cout<< "Already wartered in a future year" << std::endl;
            return false;
        }

        if((local_tm.tm_year == lst_year) && (local_tm.tm_mon < lst_month))
        {
            std::cout<< "Already wartered in a future month" << std::endl;  
            return false;
        }

        if((local_tm.tm_mon == lst_month) && (local_tm.tm_mday <= lst_day) )
        {
            std::cout<< "Already wartered today" << std::endl;      
            return false;
        }

        if (local_tm.tm_hour < hour)
        {
            std::cout<< "The hour "<< local_tm.tm_hour << " is not later than " << hour << std::endl;  
            return false;
        }

        if ((local_tm.tm_hour == hour) && (local_tm.tm_min < minute))
        {
            std::cout<< "The minute "<< local_tm.tm_min << " is not later than " << minute << std::endl;  
            return false;
        }

        std::cout<< "timeToWarter" << std::endl;        

        return true;
        
    }
    return false;
}

bool Gardener::waterThePlants(Warehouse& warehouse)
{
    HardwareCommInterface& hwComm = warehouse.getHardwareComm();
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

    //return true; //do not warter

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

            if ( (warehouse.getPump().getState() == Aktor::OFF) && (hwComm.switchAktor(true, warehouse.getPump())) )
            {
                std::cout << "Pump turned on" << std::endl;
                warehouse.getPump().setState(Aktor::ON);
            }

            std::cout << "sleep..." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(valveIt->second.getWaterDuration_s()));
            std::cout << " done" << std::endl;

            if (valveIt->second.getState() == Aktor::ON)
            {
                std::cout << "Turn valve " << valveIt->second.getName() << " off" << std::endl;
                hwComm.switchAktor(false, valveIt->second);
            } 
        }
    }

    if (warehouse.getPump().getState() == Aktor::ON)
    {
        std::cout << "Turn pump off" << std::endl;
        hwComm.switchAktor(false, warehouse.getPump());
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

bool Gardener::furtherRequests(Warehouse& warehouse)
{
    

    if(warehouse.waterNow.load())
    {
        std::cout<< "furtherRequests: true" << std::endl;
        return true;
    }

    std::cout<< "furtherRequests: false" << std::endl;

    return false;
}

bool Gardener::taskOnDemand(Warehouse& warehouse)
{
    pthread_mutex_lock(&warehouse.waterLock);  
    if(warehouse.waterNow.load())
    {
        waterThePlants(warehouse);

        std::cout<< "Water now :D" << std::endl;
        
        warehouse.waterNow.store(false);
    }
    pthread_mutex_unlock(&warehouse.waterLock);

    std::cout<< "taskOnDemand: true" << std::endl;

    return true;
}

bool Gardener::endOfTheWorkDay(Warehouse& warehouse)
{
    int ret = 0;
    std::cout<<"Current Time :: " << std::endl;

    //std::this_thread::sleep_for(std::chrono::minutes(1));

    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += 60;
    //Calc remaining wait time

   
    std::cout<< "Begin to wait" << std::endl;
    
    pthread_mutex_lock(&warehouse.waterLock);
    while (ret == 0 && !warehouse.waterNow.load())
    {
        ret = pthread_cond_timedwait(&warehouse.waterWait, &warehouse.waterLock, &abstime); 
    }
    pthread_mutex_unlock(&warehouse.waterLock);
    

    std::cout<< "Wait done: " << ret  << std::endl;


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

    if(warehouse.waterNow.load())
    {
        std::cout<< "Async request" << std::endl;
        return false;
    }

    return true;
}