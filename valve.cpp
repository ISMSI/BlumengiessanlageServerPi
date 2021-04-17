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

Valve::Valve(std::string name, uint8_t pin, int16_t waterDuration, bool enabled)
:Valve(name, pin, waterDuration)
{
    this->enabled = enabled;
}

void Valve::enable()
{
    this->enabled = true;
}

void Valve::disable()
{
    this->enabled = false;
}

bool Valve::isEnabled()
{
    return this->enabled;
}

Valve::~Valve()
{
    
}