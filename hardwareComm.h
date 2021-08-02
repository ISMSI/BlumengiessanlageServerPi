#ifndef HARDWARE_COMM_H
#define HARDWARE_COMM_H


#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>       // std::cout
#include <string>
#include <map>
#include "hardwareCommInterface.h"
#include "pump.h"
#include "aktor.h"
#include "valve.h"



class HardwareComm: public HardwareCommInterface
{
public:


private:
wchar_t *programName;

        PyObject* myFunction_I2C;
        PyObject* myFunction_TCA9548A;
        PyObject* myFunction_ADS1115;
        PyObject* myFunction_analog_in;

        /* Aktor */
        PyObject* myFunction_gpio_setmode;
        PyObject* myFunction_gpio_setup;
        PyObject* myFunction_gpio_output;
        PyObject* myFunction_gpio_cleanup;

        PyObject* myConst_SCL;
        PyObject* myConst_SDA;
        PyObject* myConst_P0;
        PyObject* myConst_P1;
        PyObject* myConst_P2;
        PyObject* myConst_P3;

        /* Aktor */
        PyObject* myConst_BOARD;
        PyObject* myConst_OUT;
        PyObject* myConst_HIGH;
        PyObject* myConst_LOW;

        PyObject* myKey_address = PyUnicode_FromString("address");
 
        std::map<uint8_t, PyObject*> adcChannelMap;
        

public:
    HardwareComm(std::map<std::string, Valve>& shelfValve, Pump& pump);
    ~HardwareComm();

    double getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel);
    bool switchAktor(bool on, Aktor& aktor);
private:
    bool initFunctionsSensor();
    bool initFunctionsAktor(std::map<std::string, Valve> shelfValve, Pump pump);
    bool cleanupFunctionsAktor();
    bool initGpioPin(uint8_t pin);



};
 
#endif //HARDWARE_COMM_H