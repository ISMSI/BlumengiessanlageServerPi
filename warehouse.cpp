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

std::map<std::string, Valve>::iterator Warehouse::getFirstValve()
{
    return shelfValve.begin();
}

std::map<std::string, Valve>::iterator Warehouse::getLastValve()
{
    return shelfValve.end();
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
    bool wateredToday = true;
    uint16_t time_hour = 19;
    uint16_t time_minute = 30;
    uint16_t weekDay = 0b000000001111111;//0b0000 0000 0000 0000 = 0b0000 0000 0SoMoDi MiDoFrSa

    std::cout << "Fill warehouse" << std::endl;

    /*Insert default values*/
    putIn("waterOnTime", waterOnTime);
    putIn("wateredToday", wateredToday);
    putIn("Time:hour",time_hour);
    putIn("Time:minute",time_minute);
    putIn("lastWateringDate:month", static_cast<uint16_t>(5)); //mon -1
    putIn("lastWateringDate:day", static_cast<uint16_t>(4)); //actual day
    putIn("lastWateringDate:year", static_cast<uint16_t>(121)); // 2021-1900
    putIn("Time:weekday",weekDay);

    shelfValve["Dist2:Valve4"] = Valve("Blumenkasten1",23,12,false);
    shelfValve["Dist1:Valve1"] = Valve("Blumenkasten2",11,11,true);
    shelfValve["Dist1:Valve2"] = Valve("Blumenkasten3",13,10,true);
    shelfValve["Dist1:Valve3"] = Valve("Blumenkasten4",15,10,false);
    shelfValve["Dist1:Valve4"] = Valve("Blumenkasten5",16,10,true);
    shelfValve["Dist2:Valve2"] = Valve("KübelRundKlein",19,10,true);
    shelfValve["Dist2:Valve1"] = Valve("KübelViereckig",18,3,true);
    shelfValve["Dist2:Valve3"] = Valve("KübelRundGross",21,10,true);
    shelfValve["Dist3:Valve1"] = Valve("D3V1",8,5,false);
    shelfValve["Dist3:Valve2"] = Valve("D3V2",10,5,false);
    shelfValve["Dist3:Valve3"] = Valve("D3V3",12,5,false);

    pump = Pump("Pumpe", 7);

    

    //waterNow.store(false);


    return true;
}



