#include "sampler.h"
#include <sstream>


Sampler::Sampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                               const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                               const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                               double periodRatio, double modulationIndex)
    :BaseSampler(lfsr, periodicSignal, periodRatio),
     m_timeJitterSignal(timeJitterSignal),
     m_modulationIndex(modulationIndex)
{
    initialize();
}

Sampler::~Sampler()
{
    m_help_fstream->close();
    delete m_help_fstream;
}

void Sampler::initialize()
{
    m_Ts_0 = m_sourceSignal->getPeriod() / m_periodRatio;
    m_include_jitter = static_cast<bool>(m_timeJitterSignal->getPeriod());



    m_help_fstream = new std::fstream;
    m_help_fstream->open("sampleTimes.csv", std::ios::out | std::ios::trunc);
    m_help_fstream->precision(6);
}

void Sampler::incrementDiscreteTime()
{
    m_t += m_Ts_0;

    if(m_include_jitter)
    {
        m_t += m_modulationIndex * m_timeJitterSignal->value(m_t);
    }
}

void Sampler::printOutputLine(const IWritter &writter) const
{
    writter.writeSamples(m_t, m_sourceSignal->value(m_t), m_timeJitterSignal->value(m_t));
}

void Sampler::printHeaderLine(const IWritter &writter) const
{
    writter.writeLine("time, sample, jitter");
}
