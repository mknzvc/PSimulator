#include "samplermanager.h"
#include "linearfeedbackshiftregister.h"
#include "sawtoothsignal.h"

SamplerManager::SamplerManager(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                               const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                               const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                               double periodRatio)
    :ISampleManager (0),
      m_lfsr(lfsr),
      m_periodicSignal(periodicSignal),
      m_timeJitterSignal(timeJitterSignal),
      m_periodRatio(periodRatio)
{
    initialize();
}

SamplerManager::~SamplerManager()
{
}

void SamplerManager::initialize()
{
    m_samplingInterval = m_periodicSignal->getPeriod() / m_periodRatio;
}

void SamplerManager::produceSamples(unsigned numberOfSamples, const IWritter &writter)
{
    for (unsigned i = 0; i < numberOfSamples; ++i)
    {
        m_lfsr->next();
        auto lfsrOutput = m_lfsr->getOutputValue();

        for (unsigned j=0; j < lfsrOutput; ++j)
        {
            m_curent_time += m_samplingInterval;
            m_curent_time += m_timeJitterSignal->value(m_curent_time);
        }

        writter.writeDecimal(m_periodicSignal->value(m_curent_time));
    }
}
