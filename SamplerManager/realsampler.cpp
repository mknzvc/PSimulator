#include "realsampler.h"
#include <sstream>

RealSampler::RealSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                         const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                         const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                         double periodRatio,
                         double modulationIndex)
    :BaseSampler(lfsr, periodicSignal, periodRatio),
     m_timeJitterSignal(timeJitterSignal),
     m_modulationIndex(modulationIndex)
{
    initialize();
}

RealSampler::~RealSampler()
{
    m_help_fstream->close();
    delete m_help_fstream;
}

void RealSampler::initialize()
{
    m_include_jitter = static_cast<bool>(m_timeJitterSignal->getPeriod());
    m_Ts_0 = m_sourceSignal->getPeriod() / m_periodRatio;

    m_help_fstream = new std::fstream;
    m_help_fstream->open("sampleTimes.csv", std::ios::out | std::ios::trunc);
    m_help_fstream->precision(6);
}

void RealSampler::incrementDiscreteTime()
{
    if(m_include_jitter)
    {
        m_t += m_Ts_0/(1.0 + m_modulationIndex * m_timeJitterSignal->value(m_t));
    }
    else
    {
        m_t += m_Ts_0;
    }
    *m_help_fstream<<std::to_string(m_t)<<std::endl;
}

void RealSampler::printOutputLine(const IWritter &writter) const
{
    writter.writeSamples(m_t, m_sourceSignal->value(m_t), m_timeJitterSignal->value(m_t));
}

void RealSampler::printHeaderLine(const IWritter &writter) const
{
    if(m_include_jitter)
    {
        writter.writeLine("time, sample, jitter");
    }
    else
    {
        writter.writeLine("time, sample");
    }
}
