#include "fsampler.h"
#include <sstream>

FSampler::FSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                   const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                   const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                   double periodRatio,
                   double modulationIndex)
    :BaseSampler(lfsr, periodicSignal, periodRatio),
    m_timeJitterSignal(timeJitterSignal),
    m_modulationIndex(modulationIndex),
    m_tn_prev(0)
{
    initialize();
}

FSampler::~FSampler()
{
    m_help_fstream->close();
    delete m_help_fstream;
}

void FSampler::initialize()
{
    m_include_jitter = static_cast<bool>(m_timeJitterSignal->getPeriod());
    m_Ts_0 = m_sourceSignal->getPeriod() / m_periodRatio;

    m_help_fstream = new std::fstream;
    m_help_fstream->open("sampleTimes.csv", std::ios::out | std::ios::trunc);
    m_help_fstream->precision(6);
}


void FSampler::incrementDiscreteTime()
{
    if(m_include_jitter)
    {
        m_t = m_tn_prev + 1 / ( (1/m_Ts_0) + m_modulationIndex * m_timeJitterSignal->value(m_tn_prev) );
    }
    else
    {
        m_t += m_Ts_0;
    }
    *m_help_fstream<<std::to_string(m_t)<<std::endl;

    m_tn_prev = m_t;
}

void FSampler::printOutputLine(const IWritter &writter) const
{
    writter.writeSamples(m_t, m_sourceSignal->value(m_t), m_timeJitterSignal->value(m_t));
}

void FSampler::printHeaderLine(const IWritter &writter) const
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
