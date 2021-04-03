#include "gardener.h"


Gardener::Gardener()
{
    std::cout<< "Create thread" << std::endl;
    myThread = std::thread(cycle, static_cast<void*>(&myThreadData) ); 
}

Gardener::~Gardener()
{
    std::cout<< "Join thread" << std::endl;
    std::cout.flush();
    myThread.join();
}

void Gardener::cycle(void* data)
{
    while(true)
    {
        if (timeToWarter())
        {
            if (!waterThePlants())
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

bool Gardener::timeToWarter()
{
    std::cout<< "timeToWarter: false" << std::endl;
    return false;
}

bool Gardener::waterThePlants()
{
    std::cout<< "waterThePlants: true" << std::endl;
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