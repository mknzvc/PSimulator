#include "basesampler.h"

BaseSampler::BaseSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                         const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                         double periodRatio)
    //:ISampler(),
     :m_lfsr(lfsr),
     m_sourceSignal(periodicSignal),
     m_periodRatio(periodRatio)
{
    initialize();
}

BaseSampler::~BaseSampler()
{
}

void BaseSampler::initialize()
{
}

void BaseSampler::produceSamples(unsigned numberOfSamples, const IWritter &writter)
{
    auto maxSampleValue = m_lfsr->getMaxOutput();

    printHeaderLine(writter);

    for (unsigned i = 0; i < numberOfSamples; ++i, m_lfsr->next())
    {
        auto lfsrOutput = m_lfsr->getOutputValue();

        for (unsigned j=0; j < lfsrOutput; ++j)
        {
            incrementDiscreteTime();
        }

        printOutputLine(writter);

        for (unsigned j = lfsrOutput; j < maxSampleValue; ++j)
        {
            incrementDiscreteTime();
        }
    }
}
