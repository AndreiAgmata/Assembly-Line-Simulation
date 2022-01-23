#include <stdio.h>
#include <iostream>
#include "Workstation.h"
namespace sdds
{

std::deque<CustomerOrder> pending{};
std::deque<CustomerOrder> completed{};
std::deque<CustomerOrder> incomplete{};

Workstation::Workstation(const std::string& input) : Station(input)
{
    m_pNextStation = nullptr;
};

void Workstation::fill(std::ostream& os)
{
    if(!m_orders.empty())
    {
        m_orders.front().fillItem(*this, os);
    }
}

bool Workstation::attemptToMoveOrder()
{

    bool moved = false;
    if(!m_orders.empty())
    {
        if(m_orders.front().isItemFilled(getItemName()) || !getQuantity())
        {
            if(m_pNextStation)
            {
                *m_pNextStation += std::move(m_orders.front());
                m_orders.pop_front();
                moved=true;
            }
            else
            {
                if(m_orders.front().isFilled())
                {
                    completed.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                    moved =true;
                }
                else if(!m_orders.front().isFilled())
                {
                    incomplete.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                    moved = true;
                }
            }
        }
    }
    return moved;

}

void Workstation::setNextStation(Workstation* station)
{
    
    m_pNextStation=station;
}

Workstation* Workstation::getNextStation() const
{
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const
{
    os << getItemName() << " --> " << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << "\n";
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
{
    m_orders.push_back(std::move(newOrder));
    return *this;
}



}

