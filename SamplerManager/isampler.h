#ifndef ISAMPLEMANAGER_H
#define ISAMPLEMANAGER_H

#include "isignalmodel.h"
#include "iwritter.h"

class ISampler
{
public:
    ISampler();
    virtual ~ISampler();

    virtual void produceSamples(unsigned numberOfSamples, const IWritter& writter) = 0;


protected:
    double m_t;
    double m_Ts_0;

private:
    virtual void incrementDiscreteTime() = 0;
    virtual void printOutputLine(const IWritter& writter) const = 0;
    virtual void printHeaderLine(const IWritter& writter) const = 0;
};

#endif // ISAMPLEMANAGER_H
