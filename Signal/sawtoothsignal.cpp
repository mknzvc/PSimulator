#include "sawtoothsignal.h"
#include <cmath>

SawToothSignal::SawToothSignal(double slope, double yIntercept, double period)
    :BasePeriodicSignal (period),
     m_slope(slope),
     m_yIntercept(yIntercept)
{
}

double SawToothSignal::func(double x) const
{
    return m_slope * x + m_yIntercept;
}
