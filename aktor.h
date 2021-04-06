#ifndef AKTOR_H
#define AKTOR_H

#include <iostream>
#include <string>



class Aktor
{
public:
    enum state {OFF, GO_ON, ON, GO_OFF};
protected:

state current_state;
uint8_t pin;
std::string name;


public:
Aktor(std::string name, uint8_t pin);
~Aktor();
uint8_t getPin();
enum Aktor::state getState();
void setState(Aktor::state newState);
};





#endif //AKTOR_H
