#ifndef JITTERSIGNAL_H
#define JITTERSIGNAL_H

#include "baseperiodicsignal.h"

#include <memory>


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

public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new TriangleSignal(valueRange, period, meanValue));
    }
};

#endif // JITTERSIGNAL_H
