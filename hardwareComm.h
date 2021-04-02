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

        PyObject* myFunction_I2C;
        PyObject* myFunction_TCA9548A;
        PyObject* myFunction_ADS1115;
        PyObject* myFunction_analog_in;
        PyObject* myConst_SCL;
        PyObject* myConst_SDA;
        PyObject* myConst_P0;
        PyObject* myConst_P1;
        PyObject* myConst_P2;
        PyObject* myConst_P3;
        PyObject* myConst_P4;
        PyObject* myConst_P5;
        PyObject* myConst_P6;
        PyObject* myConst_P7;
 
public:
    HardwareComm();
    ~HardwareComm();
    double getSensorValue();
    bool initFunctions();

};
 
#endif //HARDWARE_COMM_H