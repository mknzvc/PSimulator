#include "signalfactory.h"
#include "trianglesignal.h"
#include "sawtoothsignal.h"
#include "triangledistrrandomsignal.h"
#include "uniformdistrrandomsignal.h"
#include <memory>

SignalFactory::SignalFactory()
{
    Register(0, &TriangleSignal::Create);
    Register(1, &SawToothSignal::Create);
    Register(2, &TriangleDistrRandomSignal::Create);
    Register(3, &UniformDistrRandomSignal::Create);
}

void SignalFactory::Register(const unsigned int signalNo, CreateSignalFn signalCreate)
{
    m_FactoryMap.insert(std::pair<unsigned, CreateSignalFn>(signalNo, signalCreate));
}

std::unique_ptr<ISignal> SignalFactory::CreateSignal(const unsigned int signalNo, double valueRange, double period, double meanValue)
{
    FactoryMap::iterator it = m_FactoryMap.find(signalNo);

    return it->second(valueRange, period, meanValue);
}
