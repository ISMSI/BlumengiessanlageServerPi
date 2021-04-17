#ifndef VALVE_H
#define VALVE_H

#include <iostream>
#include "aktor.h"

class Valve : public Aktor
{
private:
int16_t waterDuration;
bool enabled = false;

public:
Valve();
Valve(std::string name, uint8_t pin, int16_t waterDuration);
Valve(std::string name, uint8_t pin, int16_t waterDuration, bool enabled);
~Valve();
void enable();
void disable();
bool isEnabled();

};




#endif //VALVE_H
