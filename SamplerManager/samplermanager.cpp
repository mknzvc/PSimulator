#include "samplermanager.h"
#include <sstream>

Sampler::Sampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                               const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                               const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                               double periodRatio)
    :BaseSampler(lfsr, periodicSignal, periodRatio),
     m_timeJitterSignal(timeJitterSignal)

{
    initialize();
}

Sampler::~Sampler()
{
}

void Sampler::initialize()
{
    m_Ts_0 = m_sourceSignal->getPeriod() / m_periodRatio;
    m_include_jitter = static_cast<bool>(m_timeJitterSignal->getPeriod());
}

void Sampler::incrementDiscreteTime()
{
    m_t += m_Ts_0;

    if(m_include_jitter)
    {
        m_t += m_timeJitterSignal->value(m_t);
    }
}

void Sampler::printOutputLine(const IWritter &writter) const
{
    std::stringstream sstream;

    sstream << std::to_string(m_t) << "," << std::to_string(m_sourceSignal->value(m_t));

    if(m_include_jitter)
    {
        sstream << "," << std::to_string(m_timeJitterSignal->value(m_t));
    }

    writter.writeLine(sstream.str());
}

void Sampler::printHeaderLine(const IWritter &writter) const
{
    writter.writeLine("time, sample, jitter");
}
