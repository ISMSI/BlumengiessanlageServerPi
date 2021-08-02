#include "hardwareCommDummy.h"

HardwareCommDummy::HardwareCommDummy(std::map<std::string, Valve>& shelfValve, Pump& pump)
: HardwareCommInterface(shelfValve, pump)
{

}

HardwareCommDummy::~HardwareCommDummy()
{
    
}

double HardwareCommDummy::getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel)
{
    return 1.23;
}

bool HardwareCommDummy::switchAktor(bool on, Aktor& aktor)
{
    if(on)
    {
        std::cout << "Dummy aktor "<< aktor.getName() << " on" << std::endl;
        aktor.setState(Aktor::ON);
    }
    else
    {
        std::cout << "Dummy aktor " << aktor.getName() << " off" << std::endl;
        aktor.setState(Aktor::OFF);
    }

    return true;
}