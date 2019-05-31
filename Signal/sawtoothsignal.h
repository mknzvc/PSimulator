#ifndef SAWTOOTHSIGNAL_H
#define SAWTOOTHSIGNAL_H

#include "baseperiodicsignal.h"

#include <memory>


class SawToothSignal : public BasePeriodicSignal
{
public:
    SawToothSignal(double valueRange, double period, double meanValue = 0);

private:

    double m_meanValue;

    double m_slope;
    double m_yIntercept;

    double func(double x) const;

public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new SawToothSignal(valueRange, period, meanValue));
    }

};

#endif // SAWTOOTHSIGNAL_H
