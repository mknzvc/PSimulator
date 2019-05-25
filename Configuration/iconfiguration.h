#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include "ps_utils.h"
#include <list>
using namespace types;

class IConfiguration
{
public:
    IConfiguration();
    virtual ~IConfiguration();

    //lsfr
    virtual char getLSFRLength() = 0;

    virtual unsigned getLSFRSeed() = 0;

    virtual unsigned getFeedbackMask() = 0;

    virtual unsigned getResultMask() = 0;

    virtual FeedbackType getFeedbackType() = 0;

    virtual void getStepsCountList(std::list<unsigned>& countsList) = 0;

    //source signal
    virtual double getSourceSignalPeriod() = 0;

    virtual double getSourceSignalValueRange() = 0;

    virtual double getSourceSignalMeanValue() = 0;

    virtual int getSourceType() = 0;

    //sampling
    virtual double getSamplingSignalRatio() = 0;

    virtual double getJitterPeriod() = 0;

    virtual double getJitterModulationIndex() = 0;

    virtual unsigned getCalculationType() = 0;

    //output

    virtual OutputType getOutputType() = 0;


};

#endif // ICONFIGURATION_H
