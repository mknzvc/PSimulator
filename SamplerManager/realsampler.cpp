#include "realsampler.h"

RealSampler::RealSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                         const std::unique_ptr<ISignal> &periodicSignal,
                         const std::unique_ptr<ISignal> &timeJitterSignal,
                         double periodRatio,
                         double modulationIndex)
    :ISampler(lfsr, periodicSignal, timeJitterSignal, periodRatio, modulationIndex)
{
    initialize();
}

RealSampler::~RealSampler()
{
}

void RealSampler::initialize()
{
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
