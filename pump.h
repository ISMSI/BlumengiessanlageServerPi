#ifndef PUMP_H
#define PUMP_H

#include <iostream>
#include "aktor.h"

class Pump : Aktor
{
private:


public:
Pump();
Pump(std::string name, uint8_t pin);
~Pump();

};




#endif //PUMP_H
