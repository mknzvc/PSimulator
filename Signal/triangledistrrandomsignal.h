#ifndef RANDOMSIGNAL_H
#define RANDOMSIGNAL_H

#include "isignal.h"
#include <memory>

class TriangleDistrRandomSignal : public ISignal
{
public:
    TriangleDistrRandomSignal(double valueRange, double period, double meanValue);


public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new TriangleDistrRandomSignal(valueRange, period, meanValue));
    }


public:
    virtual double value(double time) const;
};

#endif // RANDOMSIGNAL_H
