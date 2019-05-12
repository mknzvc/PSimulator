#include "csvwritter.h"
#include <fstream>
#include <iostream>

CSVWritter::CSVWritter(std::fstream *stream,
                       std::string fileName) : IWritter(stream)
{
    stream->open(fileName, std::ios::out | std::ios::trunc);
    m_stream->precision(6);
}

CSVWritter::~CSVWritter()
{
    static_cast<std::ofstream*>(m_stream)->close();
}
