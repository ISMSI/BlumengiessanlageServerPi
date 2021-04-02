#include "warehouse.h"
 
Warehouse::Warehouse()
{
    shelfInt = std::unordered_map<std::string, uint16_t>();
    shelfDouble = std::unordered_map<std::string , double>();
    shelfString = std::unordered_map<std::string , std::string>();
    fill();
}

Warehouse::~Warehouse()
{

}

const bool Warehouse::putIn(std::string label, const uint16_t& ware)
{
    shelfInt.insert(std::pair<std::string, uint16_t>(label, ware));
    return true;
}

const bool Warehouse::putIn(std::string label, const double& ware)
{
    shelfDouble.insert(std::pair<std::string, double>(label, ware));
    return true;
}

const bool Warehouse::putIn(std::string label, const std::string& ware)
{
    shelfString.insert(std::pair<std::string, std::string>(label, ware));
    return true;
}

const bool Warehouse::takeOut(std::string label, uint16_t& ware) const
{
    return true;
}
const bool Warehouse::takeOut(std::string label, double& ware) const
{
    return true;
}
const bool Warehouse::takeOut(std::string label, std::string& ware) const
{
    return true;
}

bool Warehouse::fill()
{
    putIn("test1",static_cast<uint16_t>(3));
    putIn("sweety","Ich liebe dich, Sweety");
    putIn("sensor", 3.314);
    return true;
}



