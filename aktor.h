#ifndef AKTOR_H
#define AKTOR_H

#include <iostream>
#include <string>



class Aktor
{
private:
enum state {OFF, GO_ON, ON, GO_OFF};
state current_state;
uint8_t pin;
std::string name;


public:
Aktor(std::string name, uint8_t pin);
~Aktor();

};




#endif //AKTOR_H
