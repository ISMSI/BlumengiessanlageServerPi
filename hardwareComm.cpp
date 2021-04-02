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
        myConst_P4 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P4");
        myConst_P5 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P5");
        myConst_P6 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P6");
        myConst_P7 = PyObject_GetAttrString(myModule_adafruit_ads1x15_ads1115,(char*)"P7");
        
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

double HardwareComm::getSensorValue()
{
        PyObject* myArgs_SDA_SCL = PyTuple_New(2);
        PyTuple_SetItem(myArgs_SDA_SCL,0,myConst_SCL);
        PyTuple_SetItem(myArgs_SDA_SCL,1,myConst_SDA);
        PyObject* myResult_i2c = PyObject_CallObject (myFunction_I2C,myArgs_SDA_SCL);

        PyObject* myArgs_i2c_hex = PyTuple_New(1);
        PyObject* myValue_hex70 = PyLong_FromLong(0x70);
        PyTuple_SetItem(myArgs_i2c_hex,0,myResult_i2c);

        PyObject* myKey_address = PyUnicode_FromString("address");
        PyObject* myArgs_hex = PyDict_New();
        PyDict_SetItem(myArgs_hex, myKey_address, myValue_hex70);

        PyObject* myResult_tca = PyObject_Call(myFunction_TCA9548A, myArgs_i2c_hex, myArgs_hex);

        PyObject* myArgs_tca0_hex = PyTuple_New(1);
        //PyObject* myValue_hex49 = PyLong_FromLong(0x49);
        PyTypeObject* type = myResult_tca->ob_type;
        const char* p = type->tp_name;
        std::cout << "The type is" << p <<std::endl;
        PyObject* myValue_tca0 = PyObject_GetItem(myResult_tca,PyLong_FromLong(0)); //PyTuple_GetItem wrong
        PyTuple_SetItem(myArgs_tca0_hex,0,myValue_tca0);//problem?

        PyObject* myValue_hex49 = PyLong_FromLong(0x49);
        PyObject* myKey_address2 = PyUnicode_FromString("address");
        PyObject* myArgs_hex2 = PyDict_New();
        PyDict_SetItem(myArgs_hex2, myKey_address2, myValue_hex49);

        //PyTuple_SetItem(myArgs_tca0_hex,1,myValue_hex49);//problem
        PyObject* myResult_tsl1 = PyObject_Call(myFunction_ADS1115, myArgs_tca0_hex, myArgs_hex2);

        PyObject* myAttrString_gain = PyUnicode_FromString((char*)"gain");
        PyObject* myValue_gain2_3 = PyFloat_FromDouble(2.0/3.0);
        PyObject_SetAttr(myResult_tsl1,myAttrString_gain, myValue_gain2_3);

        

        PyObject* myArgs_tsl1_P0 = PyTuple_New(2);
        PyTuple_SetItem(myArgs_tsl1_P0,0,myResult_tsl1);
        PyTuple_SetItem(myArgs_tsl1_P0,1,myConst_P0);
        PyObject* myResult_chan1 = PyObject_CallObject(myFunction_analog_in, myArgs_tsl1_P0);

        std::cout << "Result: Function: " << PyFloat_AsDouble(PyObject_GetAttrString(myResult_chan1,"voltage")) << std::endl;

    return 0;
}