#ifndef SAWTOOTHSIGNAL_H
#define SAWTOOTHSIGNAL_H

#include "baseperiodicsignal.h"


class SawToothSignal : public BasePeriodicSignal
{
public:
    SawToothSignal(double slope, double yIntercept, double getPeriod);

private:
    double m_slope;
    double m_yIntercept;

    double func(double x) const;

};

#endif // SAWTOOTHSIGNAL_H
