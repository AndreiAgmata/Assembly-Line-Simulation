// Name: Andrei Agmata
// Seneca Student ID: 103696209
// Seneca email: aagmata@myseneca.ca
// Date of completion: Nov 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef CustomerOrder_h
#define CustomerOrder_h
#include <string>
#include "Station.h"
namespace sdds
{

struct Item
{
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder
{
    std::string m_name;
    std::string m_product;
    size_t m_cntItem;
    Item** m_listItem;
    static size_t m_widthfield;
public:
    CustomerOrder();
    CustomerOrder(const std::string& input);
    CustomerOrder(const CustomerOrder& incoming);
    CustomerOrder& operator=(CustomerOrder& incoming)=delete;
    CustomerOrder(CustomerOrder&& incoming) noexcept;
    CustomerOrder& operator=(CustomerOrder&& incoming) noexcept;
    ~CustomerOrder();
    bool isFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
};

}

#endif /* CustomerOrder_h */
