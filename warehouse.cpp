#include "warehouse.h"
 
Warehouse::Warehouse()
{
    shelfBool = std::unordered_map<std::string, bool>();
    shelfInt = std::unordered_map<std::string, uint16_t>();
    shelfDouble = std::unordered_map<std::string , double>();
    shelfString = std::unordered_map<std::string , std::string>();
    fill();
}

Warehouse::~Warehouse()
{

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
    /*Insert default values*/
    putIn("waterOnTime", true);
    putIn("wateredToday", false);
    putIn("lastWateringDate:month", static_cast<uint16_t>(0));
    putIn("lastWateringDate:day", static_cast<uint16_t>(0));
    putIn("lastWateringDate:year", static_cast<uint16_t>(0));
    return true;
}



