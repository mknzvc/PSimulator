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

};

#endif // ICONFIGURATION_H
