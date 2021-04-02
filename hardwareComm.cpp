#include "hardwareComm.h"


HardwareComm::HardwareComm()
{
    programName = Py_DecodeLocale("HardwareComm", NULL);
    Py_SetProgramName(programName);
    Py_Initialize();
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC1, myConst_P0));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC1, myConst_P1));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC2, myConst_P2));
    adcChannelMap.insert(std::make_pair(HardwareComm::CHADC3, myConst_P3));
}

HardwareComm::~HardwareComm()
{
    Py_FinalizeEx();
    PyMem_RawFree(programName);
}

bool HardwareComm::initFunctions()
{

    PyObject* myModuleString_board = PyUnicode_FromString((char*)"board");
    PyObject* myModuleString_busio = PyUnicode_FromString((char*)"busio");
    PyObject* myModuleString_adafruit_tca9548a = PyUnicode_FromString((char*)"adafruit_tca9548a");
    PyObject* myModuleString_adafruit_ads1x15_ads1115 = PyUnicode_FromString((char*)"adafruit_ads1x15.ads1115");
    PyObject* myModuleString_adafruit_ads1x15_analog_in = PyUnicode_FromString((char*)"adafruit_ads1x15.analog_in");

    PyObject* myModule_board = PyImport_Import(myModuleString_board);
    PyObject* myModule_busio = PyImport_Import(myModuleString_busio);
    PyObject* myModule_adafruit_tca9548a = PyImport_Import(myModuleString_adafruit_tca9548a);
    PyObject* myModule_adafruit_ads1x15_ads1115 = PyImport_Import(myModuleString_adafruit_ads1x15_ads1115);
    PyObject* myModule_adafruit_ads1x15_analog_in = PyImport_Import(myModuleString_adafruit_ads1x15_analog_in);

    if (myModule_board == NULL
    || myModule_busio == NULL
    || myModule_adafruit_tca9548a == NULL
    || myModule_adafruit_ads1x15_ads1115 == NULL
    || myModule_adafruit_ads1x15_analog_in == NULL
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

        myConst_SCL = PyObject_GetAttr(myModule_board,myConstString_SCL);
        myConst_SDA = PyObject_GetAttr(myModule_board, myConstString_SDA);
        myConst_P0 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P0");
        myConst_P1 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P1");
        myConst_P2 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P2");
        myConst_P3 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P3");
        
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

        return true;
}

double HardwareComm::getSensorValue(MUX_ADDRESS muxAddress, MUX_CHANNEL muxChannel, ADC_ADDRESS adcAddress, ADC_CHANNEL adcChannel)
{
        /* Get i2c obj */
        PyObject* myArgs_SDA_SCL = PyTuple_New(2);
        PyTuple_SetItem(myArgs_SDA_SCL,0,myConst_SCL);
        PyTuple_SetItem(myArgs_SDA_SCL,1,myConst_SDA);

        PyObject* myResult_i2c = PyObject_CallObject (myFunction_I2C,myArgs_SDA_SCL);


        /* Get MUX obj */
        PyObject* myArgs_i2c = PyTuple_New(1);
        PyTuple_SetItem(myArgs_i2c,0,myResult_i2c);

        PyObject* myValue_muxAddress = PyLong_FromLong(muxAddress);
        PyObject* myArgs_muxAddress = PyDict_New();
        PyDict_SetItem(myArgs_muxAddress, myKey_address, myValue_muxAddress);

        PyObject* myResult_tca = PyObject_Call(myFunction_TCA9548A, myArgs_i2c, myArgs_muxAddress);


        /* Get ADC obj from MUX channel */
        PyObject* myArgs_tca = PyTuple_New(1);
        PyObject* myValue_tca = PyObject_GetItem(myResult_tca,PyLong_FromLong(muxChannel));
        PyTuple_SetItem(myArgs_tca,0,myValue_tca);

        PyObject* myValue_adcAddress = PyLong_FromLong(adcAddress);
        PyObject* myArgs_adcAddress = PyDict_New();
        PyDict_SetItem(myArgs_adcAddress, myKey_address, myValue_adcAddress);

        PyObject* myResult_tsl = PyObject_Call(myFunction_ADS1115, myArgs_tca, myArgs_adcAddress);


        /* Configure gain for ADC*/
        PyObject* myAttrString_gain = PyUnicode_FromString((char*)"gain");
        PyObject* myValue_gain2_3 = PyFloat_FromDouble(2.0/3.0);
        PyObject_SetAttr(myResult_tsl,myAttrString_gain, myValue_gain2_3);


        /* Get sensore value obj from ADC channel 0*/
        PyObject* myArgs_tsl_P = PyTuple_New(2);
        PyTuple_SetItem(myArgs_tsl_P,0,myResult_tsl);
        PyTuple_SetItem(myArgs_tsl_P,1,adcChannelMap[adcChannel]);

        PyObject* myResult_chan = PyObject_CallObject(myFunction_analog_in, myArgs_tsl_P);

    /* Get voltage value from sensor value obj*/
    return PyFloat_AsDouble(PyObject_GetAttrString(myResult_chan,"voltage"));
}