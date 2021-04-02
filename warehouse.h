#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <unordered_map>
 
class Warehouse
{
private:
std::unordered_map<std::string, uint16_t> shelfInt;
std::unordered_map<std::string, double> shelfDouble;
std::unordered_map<std::string, std::string> shelfString;

 
public:
    Warehouse();
    ~Warehouse();
    const bool putIn(std::string label, const uint16_t& ware);
    const bool putIn(std::string label, const double& ware);
    const bool putIn(std::string label, const std::string& ware);
    const bool takeOut(std::string label, uint16_t& ware) const;
    const bool takeOut(std::string label, double& ware) const;
    const bool takeOut(std::string label, std::string& ware) const;
    bool fill();
};
 
#endif //WAREHOUSE_H