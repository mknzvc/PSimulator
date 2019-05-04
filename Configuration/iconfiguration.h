#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include "ps_utils.h"
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

    virtual unsigned getStepsCount() = 0;

    //source signal
    virtual double getSourceSignalPeriode() = 0;

    virtual double getSourceSignalSlope() = 0;

    virtual double getSourceSignalYIntercept() = 0;

    //sampling
    virtual double getSamplingSignalRatio() = 0;

    virtual double getJitterPeriod() = 0;
    virtual double getJitterSlope() = 0;
    virtual double getJitterYIntercept() = 0;


};

#endif // ICONFIGURATION_H
