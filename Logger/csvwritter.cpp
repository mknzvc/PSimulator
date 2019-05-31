#include "csvwritter.h"
#include <fstream>
#include <iostream>
#include <bitset>

void formatNaturalOutput(double time, double sample, double jitter, std::stringstream& ssOut, FormatBinaryFn bcFunc)
{
    ssOut<<std::to_string(time)<<", "<<std::to_string(sample)<<", "<<std::to_string(jitter);
}

void formatNatAndBinOutput(double time, double sample, double jitter, std::stringstream& ssOut, FormatBinaryFn bcFunc)
{    
    ssOut<<std::to_string(time)<<", "<<std::to_string(sample)<<", "<<std::to_string(jitter) << ", ";
    bcFunc(sample, ssOut);
}

void formatBinaryOutput(double time, double sample, double jitter, std::stringstream& ssOut, FormatBinaryFn bcFunc)
{
    bcFunc(sample, ssOut);
}

void formatSignedBinary(double value, std::stringstream& ss)
{
    ss << ((value > 0) ? std::to_string(1) : std::to_string(0));
}

void formatValueBinary(double value, std::stringstream& ss)
{
    ss <<  std::bitset<32>(static_cast<unsigned>(value*4)).to_string();
}

CSVWritter::CSVWritter(const std::string& outFileName, const types::OutputType& outputType, const types::BinaryCoding &coding) : IWritter()
{
    m_stream = new std::fstream;
    m_ss = new std::stringstream;

    static_cast<std::fstream*>(m_stream)->open(outFileName, std::ios::out | std::ios::trunc);
    static_cast<std::fstream*>(m_stream)->precision(6);

    m_outputFormatVector.emplace_back(&formatNaturalOutput);
    m_outputFormatVector.emplace_back(&formatNatAndBinOutput);
    m_outputFormatVector.emplace_back(&formatBinaryOutput);

    m_binaryFormatVector.emplace_back(&formatSignedBinary);
    m_binaryFormatVector.emplace_back(&formatValueBinary);

    m_formatOutputFunction = m_outputFormatVector.at(static_cast<unsigned>(outputType));
    m_formatBinaryFunction = m_binaryFormatVector.at(static_cast<unsigned>(coding));
}

CSVWritter::~CSVWritter()
{
    static_cast<std::fstream*>(m_stream)->close();

    delete m_stream;

    m_outputFormatVector.clear();
}

void CSVWritter::writeSamples(double time, double sampleVal, double jitterVal) const
{
    m_ss->str("");
    m_formatOutputFunction(time, sampleVal, jitterVal, *m_ss, m_formatBinaryFunction);
    this->writeLine(m_ss->str());
}
