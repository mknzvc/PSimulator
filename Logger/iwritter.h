#ifndef ILOGGER_H
#define ILOGGER_H

#include <ostream>

class IWritter
{
public:
    IWritter(std::ostream *stream);
    virtual ~IWritter();


    virtual void writeDecimal(double number) const;
    virtual void writeLine(std::string line) const;

protected:
    std::ostream* m_stream;
};

#endif // ILOGGER_H
