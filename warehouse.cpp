#include "warehouse.h"
 
Warehouse::Warehouse()
{
    shelfBool = std::unordered_map<std::string, bool>();
    shelfInt = std::unordered_map<std::string, uint16_t>();
    shelfDouble = std::unordered_map<std::string , double>();
    shelfString = std::unordered_map<std::string , std::string>();
    shelfValve = std::map<std::string, Valve>();
    shelfSensor = std::map<std::string, Sensor>();
    fill();
    hwComm = new HardwareComm(shelfValve,pump);
}

Warehouse::~Warehouse()
{

}

HardwareComm& Warehouse::getHardwareComm()
{
    return *hwComm;
}

Valve& Warehouse::getValve(std::string label)
{
    return shelfValve[label];
}

Pump& Warehouse::getPump()
{
    return pump;
}

const bool Warehouse::putIn(std::string label, const bool& ware)
{
    shelfBool[label] = ware;
    return true;
}

const bool Warehouse::putIn(std::string label, const uint16_t& ware)
{
    shelfInt[label] = ware;
    return true;
}

const bool Warehouse::putIn(std::string label, const double& ware)
{
    shelfDouble[label] = ware;
    return true;
}

const bool Warehouse::putIn(std::string label, const std::string& ware)
{
    shelfString[label] = ware;
    return true;
}

const bool Warehouse::takeOut(std::string label, bool& ware) const
{
    try 
    {
        ware = shelfBool.at(label);
    } 
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Item " << label << " not found!" << std::endl;
        return false;
    }
    return true;
}

const bool Warehouse::takeOut(std::string label, uint16_t& ware) const
{
    try 
    {
        ware = shelfInt.at(label);
    } 
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Item " << label << " not found!" << std::endl;
        return false;
    }
    return true;
}
const bool Warehouse::takeOut(std::string label, double& ware) const
{
    try 
    {
        ware = shelfDouble.at(label);
    } 
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Item " << label << " not found!" << std::endl;
        return false;
    }
    
    return true;
}
const bool Warehouse::takeOut(std::string label, std::string& ware) const
{
    try
    {
        ware = shelfString.at(label);
    } 
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Item " << label << " not found!" << std::endl;
        return false;
    }
    
    return true;
}

bool Warehouse::fill()
{
    bool waterOnTime = true;
    bool wateredToday = false;
    uint16_t time_hour = 19;
    uint16_t time_minute = 00;

    std::cout << "Fill warehouse" << std::endl;

    /*Insert default values*/
    putIn("waterOnTime", waterOnTime);
    putIn("wateredToday", wateredToday);
    putIn("Time:hour",time_hour);
    putIn("Time:minute",time_minute);
    putIn("lastWateringDate:month", static_cast<uint16_t>(0));
    putIn("lastWateringDate:day", static_cast<uint16_t>(0));
    putIn("lastWateringDate:year", static_cast<uint16_t>(0));
    shelfValve["Dist1:Valve1"] = Valve("D1V1",11,5,true);
    shelfValve["Dist1:Valve2"] = Valve("D1V2",13,5,true);
    shelfValve["Dist1:Valve3"] = Valve("D1V3",15,5,true);
    shelfValve["Dist1:Valve4"] = Valve("D1V4",16,5,true);
    shelfValve["Dist2:Valve1"] = Valve("D2V1",18,5,true);
    shelfValve["Dist2:Valve2"] = Valve("D2V2",19,5,true);
    shelfValve["Dist2:Valve3"] = Valve("D2V3",21,5,true);
    shelfValve["Dist2:Valve4"] = Valve("D2V4",23,5,true);
    shelfValve["Dist3:Valve1"] = Valve("D3V1",8,5,true);
    shelfValve["Dist3:Valve2"] = Valve("D3V2",10,5,true);
    shelfValve["Dist3:Valve3"] = Valve("D3V3",12,5,true);

    pump = Pump("Pumpe", 7);


    return true;
}



