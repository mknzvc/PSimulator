#ifndef CSVWRITTER_H
#define CSVWRITTER_H

#include "iwritter.h"
#include "ps_utils.h"
#include <vector>
#include <sstream>

typedef void (*FormatOutput)(double, double, double, std::stringstream& ssOut);

class CSVWritter : public IWritter
{
public:
    CSVWritter(const std::string &outFileName, const types::OutputType &outputType);
    ~CSVWritter();

private:
    FormatOutput m_formatOutputFunction;

    std::stringstream* m_ss;



//    void formatNaturalOutput(double time, double sample, double jitter, std::stringstream& ssOut);
//    void formatNatAndBinOutput(double time, double sample, double jitter, std::stringstream& ssOut);
//    void formatBinaryOutput(double time, double sample, double jitter, std::stringstream& ssOut);

    std::vector<FormatOutput> m_outputFormatVector;

public:
    virtual void writeSamples(double time, double sampleVal, double jitterVal) const;
};

#endif // CSVWRITTER_H
