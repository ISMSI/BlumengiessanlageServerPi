#include "aktor.h"

Aktor::Aktor(std::string name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
}

Aktor::~Aktor()
{

}

uint8_t Aktor::getPin()
{
    return pin;
}

