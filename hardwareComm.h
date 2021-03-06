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
#include "pump.h"
#include "aktor.h"
#include "valve.h"



class HardwareComm
{
public:
    enum ADC_CHANNEL
    {
        CHADC0 = 0,
        CHADC1 = 1,
        CHADC2 = 2,
        CHADC3 = 3,
    };

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

    enum MUX_CHANNEL
    {
        CHMUX0 = 0,
        CHMUX1 = 1,
        CHMUX2 = 2,
        CHMUX3 = 3,
    };

    enum ADC_ADDRESS
    {
        ADC0 = 0x48,
        ADC1 = 0x49,
        ADC2 = 0x4A,
        ADC3 = 0x4B,
    };



    double getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel);
    bool switchAktor(bool on, Aktor& aktor);
private:
    bool initFunctionsSensor();
    bool initFunctionsAktor(std::map<std::string, Valve> shelfValve, Pump pump);
    bool cleanupFunctionsAktor();
    bool initGpioPin(uint8_t pin);



};
 
#endif //HARDWARE_COMM_H