#ifndef CSVWRITTER_H
#define CSVWRITTER_H

#include "iwritter.h"
#include "ps_utils.h"
#include <vector>
#include <sstream>

typedef void (*FormatBinaryFn)(double, std::stringstream& ssOut);
typedef void (*FormatOutputFn)(double, double, double, std::stringstream& ssOut, FormatBinaryFn bcFunc);


class CSVWritter : public IWritter
{
public:
    CSVWritter(const std::string &outFileName, const types::OutputType &outputType, const types::BinaryCoding& coding);
    ~CSVWritter();

private:
    FormatOutputFn m_formatOutputFunction;
    FormatBinaryFn m_formatBinaryFunction;

    std::stringstream* m_ss;



//    void formatNaturalOutput(double time, double sample, double jitter, std::stringstream& ssOut);
//    void formatNatAndBinOutput(double time, double sample, double jitter, std::stringstream& ssOut);
//    void formatBinaryOutput(double time, double sample, double jitter, std::stringstream& ssOut);

    std::vector<FormatOutputFn> m_outputFormatVector;
    std::vector<FormatBinaryFn> m_binaryFormatVector;

public:
    virtual void writeSamples(double time, double sampleVal, double jitterVal) const;
};

#endif // CSVWRITTER_H
