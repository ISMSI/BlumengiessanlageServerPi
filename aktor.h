#ifndef AKTOR_H
#define AKTOR_H

#include <iostream>
#include <string>



class Aktor
{
protected:
enum state {OFF, GO_ON, ON, GO_OFF};
state current_state;
uint8_t pin;
std::string name;


public:
Aktor(std::string name, uint8_t pin);
~Aktor();
uint8_t getPin();
};




#endif //AKTOR_H
