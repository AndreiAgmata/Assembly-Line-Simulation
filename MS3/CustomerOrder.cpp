
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
namespace sdds
{

size_t CustomerOrder::m_widthfield=0;

CustomerOrder::CustomerOrder()
{
    m_listItem=nullptr;
}

CustomerOrder::CustomerOrder(const std::string& input)
{
    Utilities util;
    size_t nextPos = 0u;
    bool more = true;
    
    m_name = util.extractToken(input, nextPos, more);
    m_product = util.extractToken(input, nextPos, more);
    
    m_cntItem = std::count(input.begin(), input.end(), util.getDelimiter()) - 1;
    
    
    m_listItem = new Item*[m_cntItem];
    
    for(size_t i =0; i <m_cntItem;i++)
    {
        m_listItem[i]= new Item(util.extractToken(input, nextPos, more));
    }
    
    if(m_widthfield<util.getFieldWidth())
    {
        m_widthfield=util.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(const CustomerOrder& incoming)
{
    throw std::string("Copy Operator not allowed on CustomerOrder");
}

CustomerOrder::CustomerOrder(CustomerOrder&& incoming) noexcept
{
    m_listItem=nullptr;
    *this = std::move(incoming);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& incoming) noexcept
{
    
    if(this!=&incoming)
    {
        if(m_listItem!=nullptr)
        {
            for(size_t i=0;i<m_cntItem;i++)
            {
                delete m_listItem[i];
            }
            
            delete [] m_listItem;
        }
        m_listItem=incoming.m_listItem;
        m_name=incoming.m_name;
        m_product=incoming.m_product;
        m_cntItem=incoming.m_cntItem;
        
        
        incoming.m_listItem=nullptr;
        incoming.m_cntItem=0;

        m_widthfield=incoming.m_widthfield;
    }
    
    return *this;
}

CustomerOrder::~CustomerOrder()
{
    for(size_t i =0; i < m_cntItem; i++)
    {
        delete m_listItem[i];
    }
    
    delete [] m_listItem;
    m_listItem=nullptr;
    
}

bool CustomerOrder::isFilled() const
{
    return std::all_of(m_listItem, m_listItem + m_cntItem,[=](Item* item)
    {
    return item->m_isFilled;
    });
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
    bool isFilled = true;
    std::for_each(m_listItem, m_listItem + m_cntItem,[&](const Item* item)
    {
        if (item->m_itemName == itemName) isFilled = item ->
            m_isFilled;
    });
    
    return isFilled;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{

    for(size_t i =0; i <m_cntItem;i++)
    {
        if(m_listItem[i]->m_itemName==station.getItemName())
        {
            if(station.getQuantity()>0)
            {
                m_listItem[i]->m_isFilled=true;
                m_listItem[i]->m_serialNumber=station.getNextSerialNumber();
                station.updateQuantity();
                os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << "\n";
            }
            
            else if(station.getQuantity()<=0)
            {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << "\n";
            }
            
        }
    }
}

void CustomerOrder::display(std::ostream& os) const
{
    os << m_name << " - " << m_product << "\n";
    
    for(size_t i =0; i <m_cntItem;i++)
    {
        os << "[" <<std::setw(6) << std::setfill('0') <<std::right << m_listItem[i]->m_serialNumber << std::setfill(' ') << "] ";
        os << std::setw(m_widthfield) << std::left << m_listItem[i]->m_itemName << " - ";
        
        if(isItemFilled(m_listItem[i]->m_itemName))
        {
            os << "FILLED\n";
        }
        else
        {
            os << "TO BE FILLED\n";
        }
    }
}

}
