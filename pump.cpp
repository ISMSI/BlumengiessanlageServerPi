#include "pump.h"


Pump::Pump()
: Aktor("null", -1)
{

}

Pump::Pump(std::string name, uint8_t pin)
: Aktor(name, pin)
{
    
}

Pump::~Pump()
{
    
}