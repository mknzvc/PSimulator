#include "fsampler.h"

FSampler::FSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                   const std::unique_ptr<ISignal> &periodicSignal,
                   const std::unique_ptr<ISignal> &timeJitterSignal,
                   double periodRatio,
                   double modulationIndex)
    :ISampler(lfsr, periodicSignal, timeJitterSignal, periodRatio, modulationIndex),
     m_tn_prev(0)
{
    initialize();
}

FSampler::~FSampler()
{
}

void FSampler::initialize()
{
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
