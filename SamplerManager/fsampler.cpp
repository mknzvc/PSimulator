#include "fsampler.h"

FSampler::FSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                   const std::unique_ptr<ISignal> &periodicSignal,
                   const std::unique_ptr<ISignal> &timeJitterSignal,
                   double sourcePeriod,
                   double periodRatio,
                   double modulationIndex)
    :ISampler(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex),
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

    m_t = m_tn_prev + 1 / ( (1/m_Ts_0) + m_modulationIndex * m_timeJitterSignal->value(m_tn_prev) );

    *m_help_fstream<<std::to_string(m_t)<<std::endl;

    m_tn_prev = m_t;
}

void FSampler::printHeaderLine(const IWritter &writter) const
{
    if(m_modulationIndex > 0)
    {
        writter.writeLine("time, sample, jitter");
    }
    else
    {
        writter.writeLine("time, sample");
    }
}
