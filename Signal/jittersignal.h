#ifndef JITTERSIGNAL_H
#define JITTERSIGNAL_H

#include "baseperiodicsignal.h"


class JitterSignal : public BasePeriodicSignal
{
public:
    JitterSignal(double period);

    // ISignal interface
private:
    virtual double func(double x) const;
};

#endif // JITTERSIGNAL_H
