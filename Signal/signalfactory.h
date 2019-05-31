#ifndef SIGNALFACTORY_H
#define SIGNALFACTORY_H

#include <map>
#include <memory>
#include "isignal.h"

typedef std::unique_ptr<ISignal> (*CreateSignalFn)(double valueRange, double period, double meanValue);


class SignalFactory
{
public:
    SignalFactory();

    typedef std::map<unsigned, CreateSignalFn> FactoryMap;

    FactoryMap m_FactoryMap;

public:
    ~SignalFactory(){m_FactoryMap.clear();}

    static SignalFactory* Get()
    {
        static SignalFactory instance;
        return &instance;
    }

    void Register(const unsigned signalNo, CreateSignalFn signalCreate);
    std::unique_ptr<ISignal> CreateSignal(const unsigned signalNo, double valueRange, double period, double meanValue = 0);
};

#endif // SIGNALFACTORY_H
