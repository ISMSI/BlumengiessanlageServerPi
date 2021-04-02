#ifndef HARDWARE_COMM_H
#define HARDWARE_COMM_H


#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>       // std::cout
#include <string>



class HardwareComm
{

private:
wchar_t *programName;
 
public:
    HardwareComm();
    ~HardwareComm();
    double getSensorValue();

};
 
#endif //HARDWARE_COMM_H