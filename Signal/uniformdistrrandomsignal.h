#ifndef UNIFORMDISTRRANDOMSIGNAL_H
#define UNIFORMDISTRRANDOMSIGNAL_H

#include "baseperiodicsignal.h"
#include <memory>

class UniformDistrRandomSignal : public BasePeriodicSignal
{
public:
    UniformDistrRandomSignal(double valueRange, double period, double meanValue);


private:
    virtual double func(double x) const;

public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new UniformDistrRandomSignal(valueRange, period, meanValue));
    }
};

#endif // UNIFORMDISTRRANDOMSIGNAL_H
