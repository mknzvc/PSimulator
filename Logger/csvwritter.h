#ifndef CSVWRITTER_H
#define CSVWRITTER_H

#include "iwritter.h"


class CSVWritter : public IWritter
{
public:
    CSVWritter(std::fstream *stream, std::string fileName);
    ~CSVWritter();

};

#endif // CSVWRITTER_H
