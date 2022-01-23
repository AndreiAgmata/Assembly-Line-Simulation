#ifndef Workstation_h
#define Workstation_h
#include "Station.h"
#include "CustomerOrder.h"
#include <string>
#include <iostream>
#include <deque>

#pragma once

namespace sdds
{

extern std::deque<CustomerOrder> pending;
extern std::deque<CustomerOrder> completed;
extern std::deque<CustomerOrder> incomplete;

class Workstation : public Station
{
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation;
public:
    Workstation(Workstation& incoming)=delete;
    Workstation& operator=(Workstation& incoming)=delete;
    Workstation(Workstation&& incoming)=delete;
    Workstation& operator=(Workstation&& incoming)=delete;
    
    Workstation(const std::string& input);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    Workstation& operator+=(CustomerOrder&& newOrder);
    void setNextStation(Workstation* station=nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
};

}



#endif /* Workstation_h */
