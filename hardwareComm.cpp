#include "hardwareComm.h"


HardwareComm::HardwareComm()
{
    programName = Py_DecodeLocale("HardwareComm", NULL);
    Py_SetProgramName(programName);
    Py_Initialize();
}

HardwareComm::~HardwareComm()
{
    Py_FinalizeEx();
    PyMem_RawFree(programName);
}

double HardwareComm::getSensorValue()
{
    PyRun_SimpleString("print('Hello World!')");

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
        printf("Error: Module");
        return -1;
    }

        printf("SMS:-1");
        PyRun_SimpleString("print('Hello World!')");

        PyObject* myConstString_SCL = PyUnicode_FromString((char*)"SCL");
        PyObject* myConstString_SDA = PyUnicode_FromString((char*)"SDA");
    
        PyObject* myConst_SCL = PyObject_GetAttr(myModule_board,myConstString_SCL);
        PyObject* myConst_SDA = PyObject_GetAttr(myModule_board, myConstString_SDA);

        PyObject* myFunction_I2C = PyObject_GetAttrString(myModule_busio,(char*)"I2C");
        PyObject* myFunction_TCA9548A = PyObject_GetAttrString(myModule_adafruit_tca9548a,(char*)"TCA9548A");
        PyObject* myFunction_ADS1115 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"ADS1115");
        PyObject* myFunction_analog_in = PyObject_GetAttrString(myModule_adafruit_ads1x15_analog_in,(char*)"AnalogIn");
        
        if( !myFunction_I2C || !PyCallable_Check(myFunction_I2C) )
        {
            printf("Error: myFunction_I2C");
            return -1;
        }
        if( !myFunction_TCA9548A || !PyCallable_Check(myFunction_TCA9548A) )
        {
            printf("Error: myFunction_TCA9548A");
            return -1;
        }
        if( !myFunction_ADS1115 || !PyCallable_Check(myFunction_ADS1115) )
        {
            printf("Error: myFunction_ADS1115");
            return -1;
        }
        if( !myFunction_analog_in || !PyCallable_Check(myFunction_analog_in) )
        {
            printf("Error: myFunction_analog_in");
            return -1;
        }

        printf("SMS0");
        PyRun_SimpleString("print('SMS0')");

        PyObject* myArgs_SDA_SCL = PyTuple_New(2);
        PyTuple_SetItem(myArgs_SDA_SCL,0,myConst_SCL);
        PyTuple_SetItem(myArgs_SDA_SCL,1,myConst_SDA);
        PyObject* myResult_i2c = PyObject_CallObject (myFunction_I2C,myArgs_SDA_SCL);

        printf("SMS1");
        PyRun_SimpleString("print('SMS1')");

        PyObject* myArgs_i2c_hex = PyTuple_New(2);
        PyObject* myValue_hex70 = PyLong_FromLong(0x70);
        PyTuple_SetItem(myArgs_i2c_hex,0,myResult_i2c);
        PyTuple_SetItem(myArgs_i2c_hex,1,myValue_hex70);
        PyObject* myResult_tca = PyObject_CallObject(myFunction_TCA9548A, myArgs_i2c_hex);

        printf("SMS2");
        PyRun_SimpleString("print('SMS2')");

        PyObject* myArgs_tca0_hex = PyTuple_New(2);
        PyObject* myValue_hex49 = PyLong_FromLong(0x49);
        PyObject* myValue_tca0 = PyTuple_GetItem(myResult_tca,0);
        PyTuple_SetItem(myArgs_tca0_hex,0,myValue_tca0);//problem?
        PyTuple_SetItem(myArgs_tca0_hex,1,myValue_hex49);//problem
        PyObject* myResult_tsl1 = PyObject_CallObject(myFunction_ADS1115, myArgs_tca0_hex);

        printf("SMS3");
        PyRun_SimpleString("print('SMS3')");

        PyObject* myAttrString_gain = PyUnicode_FromString((char*)"gain");
        PyObject* myValue_gain2_3 = PyFloat_FromDouble(2.0/3.0);
        PyObject_SetAttr(myResult_tsl1,myAttrString_gain, myValue_gain2_3);

        printf("SMS4");
        PyRun_SimpleString("print('SMS4')");

        PyObject* myConst_P0 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P0");  

        printf("SMS5");
        PyRun_SimpleString("print('SMS5')");

        PyObject* myArgs_tsl1_P0 = PyTuple_New(2);
        PyTuple_SetItem(myArgs_tsl1_P0,0,myResult_tsl1);
        PyTuple_SetItem(myArgs_tsl1_P0,1,myConst_P0);
        PyObject* myResult_chan1 = PyObject_CallObject(myFunction_analog_in, myArgs_tsl1_P0);


        printf("Result: Function: %f", PyFloat_AsDouble(myResult_chan1));

    return 0;
}