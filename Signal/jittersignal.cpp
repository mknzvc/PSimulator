#include "jittersignal.h"

JitterSignal::JitterSignal(double period) : BasePeriodicSignal(period)
{

}

double JitterSignal::func(double x) const
{
    return 0*x;
}
