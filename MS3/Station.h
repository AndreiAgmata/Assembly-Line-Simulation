#ifndef Station_h
#define Station_h
#include <string>
#include <iostream>
namespace sdds
{
class Station
{
    int m_id;
    std::string m_itemName;
    std::string m_stationDesc;
    unsigned int m_serialNum;
    unsigned int m_numItemsInStock;
    static size_t m_widthfield;
    static unsigned int id_generator;
public:
    Station(const std::string str);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};

}


#endif /* Station_h */
