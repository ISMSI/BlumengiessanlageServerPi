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
        PyObject* myKey_address = PyUnicode_FromString("address");
 
public:
    HardwareComm();
    ~HardwareComm();

    enum MUX_ADDRESS
    {
        MUX0 = 0x70,
        MUX1 = 0x71,
        MUX2 = 0x72,
        MUX3 = 0x73,
        MUX4 = 0x74,
        MUX5 = 0x75,
        MUX6 = 0x76,
        MUX7 = 0x77
    };

    enum ADC_ADDRESS
    {
        ADC0 = 0x48,
        ADC1 = 0x49,
        ADC2 = 0x4A,
        ADC3 = 0x4B,
    };

    double getSensorValue(MUX_ADDRESS muxAddress, ADC_ADDRESS adcAddress);
    bool initFunctions();



};
 
#endif //HARDWARE_COMM_H