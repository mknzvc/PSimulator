#include "csvwritter.h"
#include <fstream>
#include <iostream>

CSVWritter::CSVWritter(std::fstream *stream,
                       std::string fileName) : IWritter(stream)
{
    stream->open(fileName, std::ios::out | std::ios::trunc);
    m_stream->precision(5);
}

CSVWritter::~CSVWritter()
{
    static_cast<std::ofstream*>(m_stream)->close();
}

void CSVWritter::writeDecimal(double number) const
{

    *m_stream<<number<<std::endl;
}

void CSVWritter::writeBinary(double number)
{
}
