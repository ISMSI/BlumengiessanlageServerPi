#ifndef HARDWARE_COMM_INTERFACE_H
#define HARDWARE_COMM_INTERFACE_H



#include <map>
#include "pump.h"
#include "aktor.h"
#include "valve.h"

class HardwareCommInterface
{
    public:
        enum ADC_CHANNEL
        {
            CHADC0 = 0,
            CHADC1 = 1,
            CHADC2 = 2,
            CHADC3 = 3,
        };

        enum MUX_ADDRESS
        {
            MUX0 = 0x70,
            MUX1 = 0x71,
            MUX2 = 0x72,
            MUX3 = 0x73,
            MUX4 = 0x74,
            MUX5 = 0x75,
            MUX6 = 0x76,
            MUX7 = 0x77
        };

        enum MUX_CHANNEL
        {
            CHMUX0 = 0,
            CHMUX1 = 1,
            CHMUX2 = 2,
            CHMUX3 = 3,
        };

        enum ADC_ADDRESS
        {
            ADC0 = 0x48,
            ADC1 = 0x49,
            ADC2 = 0x4A,
            ADC3 = 0x4B,
        };

        HardwareCommInterface(std::map<std::string, Valve>& shelfValve, Pump& pump);
        virtual ~HardwareCommInterface() = 0;
        virtual double getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel) = 0;
        virtual bool switchAktor(bool on, Aktor& aktor) = 0;
};

inline HardwareCommInterface::HardwareCommInterface(std::map<std::string, Valve>& shelfValve, Pump& pump)
{

}

inline HardwareCommInterface::~HardwareCommInterface()
{

}

#endif //HARDWARE_COMM_INTERFACE_H