#ifndef ILOGGER_H
#define ILOGGER_H

#include <ostream>

class IWritter
{
public:
    IWritter();
    virtual ~IWritter();

protected:
    void writeDecimal(double number) const;


    std::ostream* m_stream;
public:
    virtual void writeSamples(double time, double sampleVal, double jitterVal = 0) const = 0;
    void writeLine(std::string line) const;

};

#endif // ILOGGER_H
