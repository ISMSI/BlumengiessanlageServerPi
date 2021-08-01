#ifndef HARDWARE_COMM_INTERFACE_H
#define HARDWARE_COMM_INTERFACE_H



#include <map>
#include "pump.h"
#include "aktor.h"
#include "valve.h"

class HardwareCommInterface
{

    public:
        HardwareCommInterface(std::map<std::string, Valve>& shelfValve, Pump& pump);
        virtual ~HardwareCommInterface() = 0;
        virtual double getSensorValue() = 0;
        virtual bool switchAktor(bool on, Aktor& aktor) = 0;

    private:
        inline HardwareCommInterface::~HardwareCommInterface()
        {

        }
};

#endif //HARDWARE_COMM_INTERFACE_H