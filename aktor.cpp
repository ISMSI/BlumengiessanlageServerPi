#include "aktor.h"

Aktor::Aktor(std::string name, uint8_t pin)
{
    this->name = name;
    this->pin = pin;
    current_state = Aktor::OFF;
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

std::string Aktor::getName()
{
    return this->name;
}

void Aktor::setName(std::string name)
{
    this->name = name;
}