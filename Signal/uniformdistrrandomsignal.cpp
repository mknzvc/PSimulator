#include "uniformdistrrandomsignal.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
static std::uniform_real_distribution<> dis(-1.0, 1.0);

UniformDistrRandomSignal::UniformDistrRandomSignal(double valueRange, double period, double meanValue)
{
}

double UniformDistrRandomSignal::value(double x) const
{
        return dis(gen);
}
