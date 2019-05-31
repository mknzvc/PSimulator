#ifndef SAMPLERFACTORY_H
#define SAMPLERFACTORY_H

#include "isampler.h"
#include <map>

typedef std::unique_ptr<ISampler> (*CreateSamplerFn)(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                                     const std::unique_ptr<ISignal> &periodicSignal,
                                     const std::unique_ptr<ISignal>& timeJitterSignal,
                                     double periodRatio,
                                     double modulationIndex);

class SamplerFactory
{

private:
    SamplerFactory();

    typedef std::map<unsigned, CreateSamplerFn> FactoryMap;

    FactoryMap m_FactoryMap;

public:
    ~SamplerFactory(){m_FactoryMap.clear();}

    static SamplerFactory* Get()
    {
        static SamplerFactory instance;
        return &instance;
    }

    void Register(const unsigned samplerNo, CreateSamplerFn samplerCreate);
    std::unique_ptr<ISampler> CreateSampler(const unsigned samplerNo, const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                                                      const std::unique_ptr<ISignal> &periodicSignal,
                                                      const std::unique_ptr<ISignal>& timeJitterSignal,
                                                      double periodRatio,
                                                      double modulationIndex);
};

#endif // SAMPLERFACTORY_H
