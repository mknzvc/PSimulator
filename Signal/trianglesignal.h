#ifndef JITTERSIGNAL_H
#define JITTERSIGNAL_H

#include "baseperiodicsignal.h"


class TriangleSignal : public BasePeriodicSignal
{
public:
    TriangleSignal(double valueRange, double period, double meanValue = 0);

    // ISignal interface
private:

    double m_meanValue;

    double m_slope_halfperiod1;
    double m_slope_halfperiod2;
    double m_yIntercep_halfperiod1;
    double m_yIntercep_halfperiod2;

    virtual double func(double x) const;
};

#endif // JITTERSIGNAL_H
