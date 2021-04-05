#ifndef VALVE_H
#define VALVE_H

#include <iostream>
#include "aktor.h"

class Valve : public Aktor
{
private:
int16_t waterDuration;

public:
Valve();
Valve(std::string name, uint8_t pin, int16_t waterDuration);
~Valve();

};




#endif //VALVE_H
