#ifndef BASEPERIODICSIGNAL_H
#define BASEPERIODICSIGNAL_H

#include "isignalmodel.h"

class BasePeriodicSignal : public ISignal
{
public:
    BasePeriodicSignal(double getPeriod);



private:
    double m_period;

    double normalizeTimeToBasicPeriodRange(double time) const;


    // ISignal interface
public:
    virtual double value(double time) const;

    // ISignal interface
    double getPeriod() const;

private:
    virtual double func(double x) const = 0;
};

#endif // BASEPERIODICSIGNAL_H
