#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
#include <pthread.h>
#include <atomic>
#include "aktor.h"
#include "pump.h"
#include "valve.h"
#include "sensor.h"
#include "hardwareComm.h"

 
class Warehouse
{
private:
std::unordered_map<std::string, bool> shelfBool;
std::unordered_map<std::string, uint16_t> shelfInt;
std::unordered_map<std::string, double> shelfDouble;
std::unordered_map<std::string, std::string> shelfString;
std::map<std::string, Valve> shelfValve;
std::map<std::string, Sensor> shelfSensor;
Pump pump;
HardwareComm* hwComm = NULL;
 
public:
    Warehouse();
    ~Warehouse();
    HardwareComm& getHardwareComm();
    Valve& getValve(std::string label);
    std::map<std::string, Valve>::iterator getFirstValve();
    std::map<std::string, Valve>::iterator getLastValve();
    Pump& getPump();
    const bool putIn(std::string label, const bool& ware);
    const bool putIn(std::string label, const uint16_t& ware);
    const bool putIn(std::string label, const double& ware);
    const bool putIn(std::string label, const std::string& ware);
    const bool takeOut(std::string label, bool& ware) const;
    const bool takeOut(std::string label, uint16_t& ware) const;
    const bool takeOut(std::string label, double& ware) const;
    const bool takeOut(std::string label, std::string& ware) const;
    bool fill();

    pthread_cond_t waterWait;
    pthread_mutex_t waterLock;
    std::atomic<bool> waterNow;

    
};
 
#endif //WAREHOUSE_H