#ifndef SAWTOOTHSIGNAL_H
#define SAWTOOTHSIGNAL_H

#include "baseperiodicsignal.h"


class SawToothSignal : public BasePeriodicSignal
{
public:
    SawToothSignal(double valueRange, double period, double meanValue = 0);

private:

    double m_meanValue;

    double m_slope;
    double m_yIntercept;

    double func(double x) const;

};

#endif // SAWTOOTHSIGNAL_H
