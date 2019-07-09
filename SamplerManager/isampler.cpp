#include "isampler.h"
#include <fstream>
#include <memory>
#include <cmath>
#include <baseperiodicsignal.h>

ISampler::ISampler(const std::unique_ptr<ILinearFeedbackShiftRegister>& lfsr,
                   const std::unique_ptr<ISignal>& periodicSignal,
                   const std::unique_ptr<ISignal>& timeJitterSignal,
                   double sourcePeriod,
                   double periodRatio,
                   double modulationIndex)

    :m_sourceSignal(periodicSignal),
      m_timeJitterSignal(timeJitterSignal),
      m_lfsr(lfsr),
      m_modulationIndex(modulationIndex),
      m_sourcePeriod(sourcePeriod),
      m_periodRatio(periodRatio)
{
    initialize();
}

ISampler::~ISampler()
{
    m_help_fstream->close();
    delete m_help_fstream;
}

void ISampler::initialize()
{    
    m_Ts_0 = m_sourcePeriod / m_periodRatio;

    m_help_fstream = new std::fstream;
    m_help_fstream->open("sampleTimes.csv", std::ios::out | std::ios::trunc);
    m_help_fstream->precision(6);
}

void ISampler::produceSamples(unsigned numberOfSamples, const IWritter &writter)
{
    auto maxSampleValue = static_cast<unsigned>(std::pow(2, m_lfsr->getOutputSize())) ;

    printHeaderLine(writter);

    for (unsigned i = 0; i < numberOfSamples; ++i, m_lfsr->next())
    {
        auto lfsrOutput = m_lfsr->getOutputValue();

        for (unsigned j=0; j < lfsrOutput; ++j)
        {
            incrementDiscreteTime();
        }

        printOutputLine(writter);

        for (unsigned j = lfsrOutput; j < maxSampleValue; ++j)
        {
            incrementDiscreteTime();
        }
    }
}

void ISampler::printOutputLine(const IWritter &writter) const
{
    writter.writeSamples(m_t, m_sourceSignal->value(m_t), m_timeJitterSignal->value(m_t));

}
