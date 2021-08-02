#ifndef HARDWARE_COMM_DUMMY_H
#define HARDWARE_COMM_DUMMY_H

#include <stdio.h>
#include "hardwareCommInterface.h"


class HardwareCommDummy : public HardwareCommInterface
{
private:
    /* data */
public:
    HardwareCommDummy(std::map<std::string, Valve>& shelfValve, Pump& pump);
    ~HardwareCommDummy();
    double getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel);
    bool switchAktor(bool on, Aktor& aktor);
};


#endif //HARDWARE_COMM_DUMMY_H