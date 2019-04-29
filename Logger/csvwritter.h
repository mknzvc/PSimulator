#ifndef CSVWRITTER_H
#define CSVWRITTER_H

#include "iwritter.h"


class CSVWritter : public IWritter
{
public:
    CSVWritter(std::fstream *stream, std::string fileName);

    ~CSVWritter();

    // IWritter interface
public:
    virtual void writeDecimal(double number) const;
    virtual void writeBinary(double number);

};

#endif // CSVWRITTER_H
