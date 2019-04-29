#include "baseperiodicsignal.h"
#include <cmath>

BasePeriodicSignal::BasePeriodicSignal(double period)
    :ISignal(),
     m_period(period)
{

}

double BasePeriodicSignal::getPeriod() const
{
    return m_period;
}

double BasePeriodicSignal::normalizeTimeToBasicPeriodRange(double time) const
{
    return std::fmod(time, m_period);
}

double BasePeriodicSignal::value(double time) const
{
    return func(normalizeTimeToBasicPeriodRange(time));
}
