#ifndef JITTERSIGNAL_H
#define JITTERSIGNAL_H

#include "baseperiodicsignal.h"


class JitterSignal : public BasePeriodicSignal
{
public:
    JitterSignal(double slope, double yIntercept, double period);

    // ISignal interface
private:

    double m_slope;
    double m_yIntercept;

    virtual double func(double x) const;
};

#endif // JITTERSIGNAL_H
