#include "triangledistrrandomsignal.h"
#include <random>

static std::random_device rd;  //Will be used to obtain a seed for the random number engine
static std::mt19937 gen1(rd()); //Standard mersenne_twister_engine seeded with rd()
static std::mt19937 gen2(rd()); //Standard mersenne_twister_engine seeded with rd()
static std::uniform_real_distribution<> dis1(-0.5, 0.5);
static std::uniform_real_distribution<> dis2(-0.5, 0.5);

TriangleDistrRandomSignal::TriangleDistrRandomSignal(double valueRange, double period, double meanValue) : BasePeriodicSignal (period)
{    
}

double TriangleDistrRandomSignal::func(double x) const
{
    if(static_cast<int>(m_period) != 0)
    {
        return (dis1(gen1) + dis2(gen2));
    }
    else
    {
        return 0;
    }
}
