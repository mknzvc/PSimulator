#include "uniformdistrrandomsignal.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
static std::uniform_real_distribution<> dis(-1.0, 1.0);

UniformDistrRandomSignal::UniformDistrRandomSignal(double valueRange, double period, double meanValue)
    :BasePeriodicSignal (period)
{
}

double UniformDistrRandomSignal::func(double x) const
{
    if(static_cast<int>(m_period) != 0)
    {
        return dis(gen);
    }
    else
    {
        return 0;
    }

}
