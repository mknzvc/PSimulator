#include "sampler.h"

Sampler::Sampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                 const std::unique_ptr<ISignal> &periodicSignal,
                 const std::unique_ptr<ISignal> &timeJitterSignal,
                 double sourcePeriod,
                 double periodRatio, double modulationIndex)
    :ISampler(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex)

{
    initialize();
}

Sampler::~Sampler()
{
}

void Sampler::initialize()
{
}

void Sampler::incrementDiscreteTime()
{    
    m_t += m_Ts_0 * (1 + m_modulationIndex * m_timeJitterSignal->value(m_t));

    m_t += m_Ts_0;

    *m_help_fstream<<std::to_string(m_t)<<std::endl;
}

void Sampler::printHeaderLine(const IWritter &writter) const
{
    writter.writeLine("time, sample, jitter");
}
