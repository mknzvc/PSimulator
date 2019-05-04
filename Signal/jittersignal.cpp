#include "jittersignal.h"

JitterSignal::JitterSignal(double slope, double yIntercept, double period)
    : BasePeriodicSignal(period),
      m_slope(slope),
      m_yIntercept(yIntercept)
{
}

double JitterSignal::func(double x) const
{
    bool halfPeriode = x < m_period/2;

    double slope = (halfPeriode) ? m_slope : -m_slope;
    double yIntenrecp = halfPeriode ? m_yIntercept : -m_yIntercept;

    return slope * x + yIntenrecp;
}
