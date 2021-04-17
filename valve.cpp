#include "valve.h"


Valve::Valve()
: Aktor("null", -1)
{

}
Valve::Valve(std::string name, uint8_t pin, int16_t waterDuration_s)
: Aktor(name,pin)
{
    this->waterDuration_s = waterDuration_s;
    
}

Valve::Valve(std::string name, uint8_t pin, int16_t waterDuration, bool enabled)
:Valve(name, pin, waterDuration)
{
    this->enabled = enabled;
}

void Valve::setWaterDuration_s(int16_t waterDuration_ms)
{
    this->waterDuration_s = waterDuration_ms;
}

int16_t Valve::getWaterDuration_s()
{
    return this->waterDuration_s;
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