#ifndef LineManager_h
#define LineManager_h
#include <vector>
#include "Workstation.h"
namespace sdds
{

class LineManager
{
    std::vector<Workstation*> activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void linkStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};

}



#endif /* LineManager_h */
