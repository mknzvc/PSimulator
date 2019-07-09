#include "realsampler.h"

RealSampler::RealSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                         const std::unique_ptr<ISignal> &periodicSignal,
                         const std::unique_ptr<ISignal> &timeJitterSignal,
                         double sourcePeriod,
                         double periodRatio,
                         double modulationIndex)
    :ISampler(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex)
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
    m_t += m_Ts_0/(1.0 + m_modulationIndex * m_timeJitterSignal->value(m_t));
    *m_help_fstream<<std::to_string(m_t)<<std::endl;
}

void RealSampler::printHeaderLine(const IWritter &writter) const
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
