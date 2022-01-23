#ifndef Utilities_h
#define Utilities_h
#include <string>
namespace sdds
{
class Utilities
{
    size_t m_widthfield =1;
    static char m_delimiter;
public:
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    static void setDelimiter(char newDelimiter);
    const char getDelimiter() const;
};

}

#endif /* Utilities_h */
