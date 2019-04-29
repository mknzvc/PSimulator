#include "iwritter.h"


IWritter::IWritter(std::ostream* stream)
    :m_stream(stream)
{
}

IWritter::~IWritter()
{
}

void IWritter::writeBinary(double number)
{
    *m_stream<<number;
}

void IWritter::writeDecimal(double number) const
{
    *m_stream<<number;
}
