#ifndef VALVE_H
#define VALVE_H

#include <iostream>
#include "aktor.h"

class Valve : public Aktor
{
private:
int16_t waterDuration_s;
bool enabled = false;

public:
Valve();
Valve(std::string name, uint8_t pin, int16_t waterDuration);
Valve(std::string name, uint8_t pin, int16_t waterDuration, bool enabled);
~Valve();
void enable();
void disable();
bool isEnabled();
void setWaterDuration_s(int16_t waterDuration_s);
int16_t getWaterDuration_s();
};




#endif //VALVE_H
