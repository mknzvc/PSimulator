#include "sawtoothsignal.h"
#include <cmath>

SawToothSignal::SawToothSignal(double valueRange, double period, double meanValue)
    : BasePeriodicSignal(period),
      m_meanValue(meanValue)
{
    m_slope = valueRange/period;
    m_yIntercept = -valueRange/2;

    if(std::round(period) == 0)
    {
        m_slope = 0;
        m_yIntercept = 0;
        m_meanValue = 0;
    }
}

double SawToothSignal::func(double x) const
{
    return m_slope * x + m_yIntercept + m_meanValue;
}
