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

void RealSampler::initialize()
{
    m_include_jitter = static_cast<bool>(m_timeJitterSignal->getPeriod());
    m_Ts_0 = m_sourceSignal->getPeriod() / m_periodRatio;
}

void RealSampler::incrementDiscreteTime()
{
    double dT = m_Ts_0;

    if(m_include_jitter)
    {
        dT = m_Ts_0/(1 + m_modulationIndex * m_timeJitterSignal->value(m_t));
    }

    m_t += dT;
}

void RealSampler::printOutputLine(const IWritter &writter) const
{
    std::stringstream sstream;

    sstream << std::to_string(m_t) << "," << std::to_string(m_sourceSignal->value(m_t));

    if(m_include_jitter)
    {
        sstream << "," << std::to_string(m_timeJitterSignal->value(m_t));
    }

    writter.writeLine(sstream.str());
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
