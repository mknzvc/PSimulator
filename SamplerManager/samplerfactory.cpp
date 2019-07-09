#include "samplerfactory.h"
#include "realsampler.h"
#include "fsampler.h"
#include "sampler.h"

SamplerFactory::SamplerFactory()
{
    Register(0, &Sampler::Create);
    Register(1, &RealSampler::Create);
    Register(2, &FSampler::Create);
}

void SamplerFactory::Register(const unsigned int samplerNo, CreateSamplerFn samplerCreate)
{
    m_FactoryMap.insert(std::pair<unsigned, CreateSamplerFn>(samplerNo, samplerCreate));
}


std::unique_ptr<ISampler> SamplerFactory::CreateSampler(const unsigned samplerNo,
                                                        const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                                                        const std::unique_ptr<ISignal> &periodicSignal,
                                                        const std::unique_ptr<ISignal> &timeJitterSignal,
                                                        double sourcePeriod,
                                                        double periodRatio,
                                                        double modulationIndex)
{
    FactoryMap::iterator it = m_FactoryMap.find(samplerNo);

    return it->second(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex);
}
