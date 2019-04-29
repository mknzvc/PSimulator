#ifndef ILOGGER_H
#define ILOGGER_H

#include <ostream>

class IWritter
{
public:
    IWritter(std::ostream *stream);
    virtual ~IWritter() = 0;


    virtual void writeDecimal(double number) const = 0;
    virtual void writeBinary(double number) = 0;

protected:
    std::ostream* m_stream;
};

#endif // ILOGGER_H
