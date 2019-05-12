#include "trianglesignal.h"

TriangleSignal::TriangleSignal(double valueRange, double period, double meanValue)
    : BasePeriodicSignal(period),
      m_meanValue(meanValue)
{
    double yMax = valueRange/2;

    m_slope_halfperiod1 = 4*yMax/m_period;
    m_slope_halfperiod2 = -m_slope_halfperiod1;

    m_yIntercep_halfperiod1 = -yMax;
    m_yIntercep_halfperiod2 = 3*yMax;
}

double TriangleSignal::func(double x) const
{
    bool halfPeriode = x < m_period/2;

    double slope = (halfPeriode) ? m_slope_halfperiod1 : m_slope_halfperiod2;
    double yIntercept = (halfPeriode) ? m_yIntercep_halfperiod1 : m_yIntercep_halfperiod2;

    return slope * x + yIntercept + m_meanValue;
}
