#include "iwritter.h"
#include <fstream>


IWritter::IWritter()
{
}

IWritter::~IWritter()
{
}

void IWritter::writeDecimal(double number) const
{
    *m_stream<<number<<std::endl;
}

void IWritter::writeLine(std::string line) const
{
    *m_stream<<line<<std::endl;
}
