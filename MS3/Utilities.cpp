#include <stdio.h>
#include <iostream>
#include <string>
#include "Utilities.h"
namespace sdds
{

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth)
{
    m_widthfield=newWidth;
}

size_t Utilities::getFieldWidth() const
{
    return m_widthfield;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
    
    const auto newPos = str.find(getDelimiter(),next_pos);
    auto token = str.substr(next_pos,newPos-next_pos);
    
    if(newPos==std::string::npos)
    {
        more=false;
    }
    else
        more=true;
    
    if(newPos==next_pos)
    {
        more=false;
        throw std::string("Delimiter found at next_pos");
    }
    
    if(token.size()>getFieldWidth())
    {
        setFieldWidth(token.length());
    }
           
    next_pos = newPos+1u;
    return token;
}

void Utilities::setDelimiter(char newDelimiter)
{
    m_delimiter=newDelimiter;
}

const char Utilities::getDelimiter() const
{
    return m_delimiter;
}

}
