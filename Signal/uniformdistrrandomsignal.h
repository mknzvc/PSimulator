#ifndef UNIFORMDISTRRANDOMSIGNAL_H
#define UNIFORMDISTRRANDOMSIGNAL_H

#include "isignal.h"
#include <memory>

class UniformDistrRandomSignal : public ISignal
{
public:
    UniformDistrRandomSignal(double valueRange, double period, double meanValue);


public:

    static std::unique_ptr<ISignal> Create(double valueRange, double period, double meanValue = 0)
    {
        return std::unique_ptr<ISignal>(new UniformDistrRandomSignal(valueRange, period, meanValue));
    }

public:
    virtual double value(double time) const;
};

#endif // UNIFORMDISTRRANDOMSIGNAL_H
