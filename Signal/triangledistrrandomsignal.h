#ifndef RANDOMSIGNAL_H
#define RANDOMSIGNAL_H

#include "baseperiodicsignal.h"
#include <memory>

class TriangleDistrRandomSignal : public BasePeriodicSignal
{
public:
    TriangleDistrRandomSignal(double valueRange, double period, double meanValue);


private:
    virtual double func(double x) const;

public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new TriangleDistrRandomSignal(valueRange, period, meanValue));
    }

};

#endif // RANDOMSIGNAL_H
