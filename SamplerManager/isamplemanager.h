#ifndef ISAMPLEMANAGER_H
#define ISAMPLEMANAGER_H

#include "isignalmodel.h"
#include "iwritter.h"

class ISampleManager
{
public:
    ISampleManager(double samplingInterval);
    virtual ~ISampleManager();

    virtual void produceSamples(unsigned numberOfSamples, const IWritter& writter) = 0;

protected:
    double m_curent_time;
    double m_samplingInterval;
};

#endif // ISAMPLEMANAGER_H
