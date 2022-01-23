#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"
namespace sdds
{
size_t Station::m_widthfield=0;
unsigned int Station::id_generator=0;

Station::Station(const std::string str)
{
    Utilities utilities;
    bool more = true;
    size_t nextPos=0u;
    
    m_id=++id_generator;
    m_itemName = utilities.extractToken(str, nextPos, more);
    
    if(m_widthfield<utilities.getFieldWidth())
    {
        m_widthfield=utilities.getFieldWidth();
    }
    
    m_serialNum=stoi(utilities.extractToken(str, nextPos, more));
    m_numItemsInStock=stoi(utilities.extractToken(str, nextPos, more));
    m_stationDesc=utilities.extractToken(str, nextPos, more);
    
}

const std::string& Station::getItemName() const
{
    return m_itemName;
}

size_t Station::getNextSerialNumber()
{
    return m_serialNum++;
}

size_t Station::getQuantity() const
{
    return m_numItemsInStock;
}

void Station::updateQuantity()
{
    m_numItemsInStock-=1;
    
    if(m_numItemsInStock<0)
    {
        
        m_numItemsInStock=0;
    }
}

void Station::display(std::ostream& os, bool full) const
{
    os << "[" << std::setw(3) << std::right <<std::setfill('0') << m_id << std::setfill(' ');
    os << "] Item: " << std::setw(m_widthfield) << std::left << getItemName();
    os << " [" << std::setw(6) << std::right <<std::setfill('0') << m_serialNum << "]" << std::setfill(' ');
    
    if(full)
    {
        os << " Quantity: " << std::setw(m_widthfield) << std::left << m_numItemsInStock;
        os << " Description: " << m_stationDesc;
    }
    
    os << std::endl;
}

}
