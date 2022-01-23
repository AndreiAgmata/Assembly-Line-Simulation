#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds
{

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
{
    
    try {
        m_cntCustomerOrder=pending.size();
        m_firstStation=nullptr;
        
        std::fstream fileName(file);
        
        if(fileName)
        {
            std::string tempName;
            Utilities util;
            
            while(std::getline(fileName, tempName))
            {
                size_t nextPos=0u;
                bool more = true;
                std::string first, second="";
                first=util.extractToken(tempName, nextPos, more);
                if(more)
                {
                    second=util.extractToken(tempName, nextPos, more);
                }
                
                std::for_each(stations.begin(), stations.end(), [&](Workstation* station){
                    if(station->getItemName() == first)
                    {
                        std::for_each(stations.begin(), stations.end(), [&](Workstation* nextStation){
                            if(nextStation->getItemName()==second)
                            {
                                station->setNextStation(nextStation);
                            }
                        });
                        
                        activeLine.push_back(station);
                    }
                });
            }
            
            m_firstStation=activeLine.front();
        }
        else
        {
            throw "Cannot open file";
        }
    } catch (const char* err) {
        std::cout << err << "\n";
    }
}

void LineManager::linkStations()
{
    std::vector<Workstation*> sorted{m_firstStation};
    size_t idx=0u;
    std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* current){
        std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* next){
            if(sorted[idx]->getNextStation())
                if(sorted[idx]->getNextStation()->getItemName()==next->getItemName())
                {
                    sorted.push_back(next);
                    idx++;
                }
        });
    });
    
    activeLine=sorted;
    
}

bool LineManager::run(std::ostream& os)
{
    
    static size_t iterationCnt=0u;
    size_t numOrdersFinished = completed.size() + incomplete.size();
    
    os << "Line Manager Iteration: "<< ++iterationCnt << "\n";
    
    if(!pending.empty())
    {
        *m_firstStation += std::move(pending.front());
        pending.pop_front();
    }
    
    std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workstation){
        workstation->fill(os);
    });
    
    std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workstation){
        workstation->attemptToMoveOrder();
    });
    
    size_t numOrdersFinishedAfterFill = completed.size()+incomplete.size();
    
    m_cntCustomerOrder-= (numOrdersFinishedAfterFill - numOrdersFinished);
    
    if(m_cntCustomerOrder<= 0)
    {
        return true;
    }
    else
        return false;
}

void LineManager::display(std::ostream& os) const
{
    std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workstation){
        workstation->display(os);
    });
}

}
 

