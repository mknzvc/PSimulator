#include "csvwritter.h"
#include <fstream>
#include <iostream>

void formatNaturalOutput(double time, double sample, double jitter, std::stringstream& ssOut)
{
    ssOut<<std::to_string(time)<<", "<<std::to_string(sample)<<", "<<std::to_string(jitter);
}

void formatNatAndBinOutput(double time, double sample, double jitter, std::stringstream& ssOut)
{
    ssOut<<std::to_string(time)<<", "<<std::to_string(sample)<<", "<<std::to_string(jitter) << ", "<< ((sample > 0) ? std::to_string(1) : std::to_string(0));
}

void formatBinaryOutput(double time, double sample, double jitter, std::stringstream& ssOut)
{
    ssOut << ((sample > 0) ? std::to_string(1) : std::to_string(0));
}


CSVWritter::CSVWritter(std::string outFileName, types::OutputType outputType) : IWritter()
{
    m_stream = new std::fstream;
    m_ss = new std::stringstream;

    static_cast<std::fstream*>(m_stream)->open(outFileName, std::ios::out | std::ios::trunc);
    static_cast<std::fstream*>(m_stream)->precision(6);

    m_outputFormatVector.emplace_back(&formatNaturalOutput);
    m_outputFormatVector.emplace_back(&formatNatAndBinOutput);
    m_outputFormatVector.emplace_back(&formatBinaryOutput);

    m_formatOutputFunction = m_outputFormatVector.at(static_cast<unsigned>(outputType));
}

CSVWritter::~CSVWritter()
{
    static_cast<std::ofstream*>(m_stream)->close();

    m_outputFormatVector.clear();
}

void CSVWritter::writeSamples(double time, double sampleVal, double jitterVal) const
{
    m_ss->str("");
    m_formatOutputFunction(time, sampleVal, jitterVal, *m_ss);
    this->writeLine(m_ss->str());
}
