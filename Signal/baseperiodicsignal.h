#ifndef BASEPERIODICSIGNAL_H
#define BASEPERIODICSIGNAL_H

#include "isignal.h"

class BasePeriodicSignal : public ISignal
{
public:
    BasePeriodicSignal(double getPeriod);



protected:
    double m_period;
private:
    double normalizeTimeToBasicPeriodRange(double time) const;


public:
    virtual double value(double time) const;

    double getPeriod() const;

private:
    virtual double func(double x) const = 0;
};

#endif // BASEPERIODICSIGNAL_H
