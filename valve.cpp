#include "valve.h"


Valve::Valve()
: Aktor("null", -1)
{

}
Valve::Valve(std::string name, uint8_t pin, int16_t waterDuration)
: Aktor(name,pin)
{
    this->waterDuration = waterDuration;
}

Valve::~Valve()
{
    
}