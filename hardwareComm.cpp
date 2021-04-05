#include "hardwareComm.h"


HardwareComm::HardwareComm(std::map<std::string, Valve> shelfValve, Pump pump)
{
    programName = Py_DecodeLocale("HardwareComm", NULL);
    Py_SetProgramName(programName);
    Py_Initialize();
    initFunctions(shelfValve, pump);
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC0, myConst_P0));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC1, myConst_P1));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC2, myConst_P2));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC3, myConst_P3));
}

HardwareComm::~HardwareComm()
{
    cleanupFunctions();
    Py_FinalizeEx();
    PyMem_RawFree(programName);
}

bool HardwareComm::initGpioPin(uint8_t pin)
{
    /*Aktor -- Set GPIO pin as output*/
    PyObject* myArgs_PORT_OUT = PyTuple_New(2);
    PyObject* myValue_PORT = PyLong_FromLong(pin);
    Py_INCREF(myValue_PORT);
    Py_INCREF(myConst_OUT);
    PyTuple_SetItem(myArgs_PORT_OUT,0,myValue_PORT);
    PyTuple_SetItem(myArgs_PORT_OUT,1,myConst_OUT);

    PyObject* myResult_gpio_output = PyObject_CallObject (myFunction_gpio_setup, myArgs_PORT_OUT);
    Py_DECREF(myArgs_PORT_OUT);

    if(!myResult_gpio_output)
    {
        std::cout << "Error with port " << pin << "setting output" << std::endl;
        return false;
    }
    Py_DECREF(myResult_gpio_output);


    /*Aktor -- Set GPIO pin high*/
    PyObject* myArgs_PORT_HIGH = PyTuple_New(2);
    Py_INCREF(myConst_HIGH);
    PyTuple_SetItem(myArgs_PORT_HIGH,0,myValue_PORT);
    PyTuple_SetItem(myArgs_PORT_HIGH,0,myConst_HIGH);

    PyObject* myResult_gpio_high = PyObject_CallObject (myFunction_gpio_output, myArgs_PORT_HIGH);
    Py_DECREF(myArgs_PORT_HIGH);
    if(!myResult_gpio_high)
    {
        std::cout << "Error with port " << pin << "setting high" << std::endl;
        return false;
    }
    Py_DECREF(myResult_gpio_high);

    return true;
}

bool HardwareComm::initFunctions(std::map<std::string, Valve> shelfValve, Pump pump)
{

    PyObject* myModuleString_board = PyUnicode_FromString((char*)"board");
    PyObject* myModuleString_busio = PyUnicode_FromString((char*)"busio");
    PyObject* myModuleString_adafruit_tca9548a = PyUnicode_FromString((char*)"adafruit_tca9548a");
    PyObject* myModuleString_adafruit_ads1x15_ads1115 = PyUnicode_FromString((char*)"adafruit_ads1x15.ads1115");
    PyObject* myModuleString_adafruit_ads1x15_analog_in = PyUnicode_FromString((char*)"adafruit_ads1x15.analog_in");

    /* Aktor */
    PyObject* myModuleString_rpi_gpio = PyUnicode_FromString((char*)"RPi.GPIO");

    PyObject* myModule_board = PyImport_Import(myModuleString_board);
    PyObject* myModule_busio = PyImport_Import(myModuleString_busio);
    PyObject* myModule_adafruit_tca9548a = PyImport_Import(myModuleString_adafruit_tca9548a);
    PyObject* myModule_adafruit_ads1x15_ads1115 = PyImport_Import(myModuleString_adafruit_ads1x15_ads1115);
    PyObject* myModule_adafruit_ads1x15_analog_in = PyImport_Import(myModuleString_adafruit_ads1x15_analog_in);

    /* Aktor */
    PyObject* myModule_rpi_gpio = PyImport_Import(myModuleString_rpi_gpio);


    if (myModule_board == NULL
    || myModule_busio == NULL
    || myModule_adafruit_tca9548a == NULL
    || myModule_adafruit_ads1x15_ads1115 == NULL
    || myModule_adafruit_ads1x15_analog_in == NULL
    || myModule_rpi_gpio == NULL
    )
    {
        std::cout << "Error: Module" << std::endl;
        return false;
    }

        PyObject* myConstString_SCL = PyUnicode_FromString((char*)"SCL");
        PyObject* myConstString_SDA = PyUnicode_FromString((char*)"SDA");

        myFunction_I2C = PyObject_GetAttrString(myModule_busio,(char*)"I2C");
        myFunction_TCA9548A = PyObject_GetAttrString(myModule_adafruit_tca9548a,(char*)"TCA9548A");
        myFunction_ADS1115 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"ADS1115");
        myFunction_analog_in = PyObject_GetAttrString(myModule_adafruit_ads1x15_analog_in,(char*)"AnalogIn");

        /* Aktor */
        myFunction_gpio_setmode = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"setmode");
        myFunction_gpio_setup = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"setup");
        myFunction_gpio_output = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"output");
        myFunction_gpio_cleanup = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"cleanup");

        myConst_SCL = PyObject_GetAttr(myModule_board,myConstString_SCL);
        myConst_SDA = PyObject_GetAttr(myModule_board, myConstString_SDA);

        myConst_P0 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P0");
        myConst_P1 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P1");
        myConst_P2 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P2");
        myConst_P3 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P3");

        /* Aktor */
        myConst_BOARD = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"BOARD");
        myConst_OUT = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"OUT");
        myConst_HIGH = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"HIGH");
        myConst_LOW = PyObject_GetAttrString(myModule_rpi_gpio,(char*)"LOW");
        
        if( !myFunction_I2C || !PyCallable_Check(myFunction_I2C) )
        {
            std::cout << "Error: myFunction_I2C" << std::endl;
            return false;
        }
        if( !myFunction_TCA9548A || !PyCallable_Check(myFunction_TCA9548A) )
        {
            std::cout << "Error: myFunction_TCA9548A" << std::endl;
            return false;
        }
        if( !myFunction_ADS1115 || !PyCallable_Check(myFunction_ADS1115) )
        {
            std::cout << "Error: myFunction_ADS1115" << std::endl;
            return false;
        }
        if( !myFunction_analog_in || !PyCallable_Check(myFunction_analog_in) )
        {
            std::cout << "Error: myFunction_analog_in" << std::endl;
            return false;
        }

        /*Aktor*/
        if( !myFunction_gpio_setmode || !PyCallable_Check(myFunction_gpio_setmode) )
        {
            std::cout << "Error: myFunction_gpio_setmode" << std::endl;
            return false;
        }
        if( !myFunction_gpio_setup || !PyCallable_Check(myFunction_gpio_setup) )
        {
            std::cout << "Error: myFunction_gpio_setup" << std::endl;
            return false;
        }
        if( !myFunction_gpio_output || !PyCallable_Check(myFunction_gpio_output) )
        {
            std::cout << "Error: myFunction_gpio_output" << std::endl;
            return false;
        }
        if( !myFunction_gpio_cleanup || !PyCallable_Check(myFunction_gpio_cleanup) )
        {
            std::cout << "Error: myFunction_gpio_cleanup" << std::endl;
            return false;
        }

        /*Aktor -- Set GPIO mode*/
        PyObject* myArgs_BOARD = PyTuple_New(1);
        PyTuple_SetItem(myArgs_BOARD,0,myConst_BOARD);

        PyObject* myResult_gpio_mode = PyObject_CallObject (myFunction_gpio_setmode, myArgs_BOARD);

        if(!myResult_gpio_mode)
        {
            std::cout << "Error with set GPIO mode" << std::endl;
        }

        for (std::map<std::string,Valve>::iterator it=shelfValve.begin(); it!=shelfValve.end(); ++it)
        {
            initGpioPin(it->second.getPin());
        }
        initGpioPin(pump.getPin());

        return true;
}

double HardwareComm::getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel)
{
        /* Get i2c obj */
        PyObject* myArgs_SDA_SCL = PyTuple_New(2);
        PyTuple_SetItem(myArgs_SDA_SCL,0,myConst_SCL);
        PyTuple_SetItem(myArgs_SDA_SCL,1,myConst_SDA);

        PyObject* myResult_i2c = PyObject_CallObject (myFunction_I2C,myArgs_SDA_SCL);

        if(!myResult_i2c)
        {
            std::cout << "Error with i2c" << std::endl;
        }


        /* Get MUX obj */
        PyObject* myArgs_i2c = PyTuple_New(1);
        PyTuple_SetItem(myArgs_i2c,0,myResult_i2c);

        PyObject* myValue_muxAddress = PyLong_FromLong(muxAddress);
        PyObject* myArgs_muxAddress = PyDict_New();
        PyDict_SetItem(myArgs_muxAddress, myKey_address, myValue_muxAddress);

        PyObject* myResult_tca = PyObject_Call(myFunction_TCA9548A, myArgs_i2c, myArgs_muxAddress);

        if(!myResult_tca)
        {
            std::cout << "Error with MUX TCA9548A: MUX address is " << muxAddress << std::endl;
        }


        /* Get ADC obj from MUX channel */
        PyObject* myArgs_tca = PyTuple_New(1);
        PyObject* myValue_tca = PyObject_GetItem(myResult_tca,PyLong_FromLong(muxChannel));
        PyTuple_SetItem(myArgs_tca,0,myValue_tca);

        PyObject* myValue_adcAddress = PyLong_FromLong(adcAddress);
        PyObject* myArgs_adcAddress = PyDict_New();
        PyDict_SetItem(myArgs_adcAddress, myKey_address, myValue_adcAddress);

        PyObject* myResult_tsl = PyObject_Call(myFunction_ADS1115, myArgs_tca, myArgs_adcAddress);

        if(!myResult_tsl)
        {
            std::cout << "Error with multiplexer channel " << muxChannel << " or ADC address " << adcAddress << std::endl;
        }


        /* Configure gain for ADC*/
        PyObject* myAttrString_gain = PyUnicode_FromString((char*)"gain");
        PyObject* myValue_gain2_3 = PyFloat_FromDouble(2.0/3.0);
        PyObject_SetAttr(myResult_tsl,myAttrString_gain, myValue_gain2_3);


        /* Get sensore value obj from ADC channel 0*/
        PyObject* myArgs_tsl_P = PyTuple_New(2);
        PyTuple_SetItem(myArgs_tsl_P,0, myResult_tsl);
        PyTuple_SetItem(myArgs_tsl_P,1, adcChannelMap[adcChannel]);

        PyObject* myResult_chan = PyObject_CallObject(myFunction_analog_in, myArgs_tsl_P);

        if(!myResult_chan)
        {
            std::cout << "Error with ADC channel " << adcChannel << std::endl;
        }

    /* Get voltage value from sensor value obj*/
    return PyFloat_AsDouble(PyObject_GetAttrString(myResult_chan,"voltage"));
}

bool HardwareComm::switchAktor(bool on, Aktor aktor)
{
    uint8_t pin = aktor.getPin();

    /*Aktor -- Set GPIO pin as output*/
    PyObject* myArgs_PORT_LH = PyTuple_New(2);
    PyObject* myValue_PORT = PyLong_FromLong(pin);
    PyTuple_SetItem(myArgs_PORT_LH,0,myValue_PORT);
    if(on)
    {
        Py_INCREF(myConst_LOW);
        PyTuple_SetItem(myArgs_PORT_LH,1,myConst_LOW);
    }
    else
    {
        Py_INCREF(myConst_HIGH);
        PyTuple_SetItem(myArgs_PORT_LH,1,myConst_HIGH);
    }

    PyObject* myResult_gpio_low_high = PyObject_CallObject (myFunction_gpio_output, myArgs_PORT_LH);
    Py_DECREF(myArgs_PORT_LH);

    if(!myResult_gpio_low_high)
    {
        std::cout << "Error with port " << pin << "setting output" << std::endl;
        return false;
    }
    Py_DECREF(myResult_gpio_low_high);
    return true;
}


bool HardwareComm::cleanupFunctions()
{
    /*Aktor -- Cleanup*/
    PyObject* myResult_gpio_cleanup = PyObject_CallObject (myFunction_gpio_cleanup, NULL);

    if(!myResult_gpio_cleanup)
    {
        std::cout << "Error with cleanup" << std::endl;
        return false;
    }
    Py_DECREF(myResult_gpio_cleanup);
    return true;

}