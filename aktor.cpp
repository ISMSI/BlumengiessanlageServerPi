#include "aktor.h"

Aktor::Aktor(std::string name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    current_state = OFF;
}

Aktor::~Aktor()
{

}

uint8_t Aktor::getPin()
{
    return pin;
}

void Aktor::setState(Aktor::state newState)
{
    current_state = newState;
}

enum Aktor::state Aktor::getState()
{
    return current_state;
}
