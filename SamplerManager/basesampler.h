#ifndef BASESAMPLER_H
#define BASESAMPLER_H

#include "isampler.h"
#include <memory>
#include "iwritter.h"
#include "ilinearfeedbackshiftregister.h"
#include "isampler.h"
#include "baseperiodicsignal.h"


class BaseSampler : public ISampler
{
public:
    BaseSampler(const std::unique_ptr<ILinearFeedbackShiftRegister>& lfsr,
                const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                double periodRatio);
    virtual ~BaseSampler();

protected:

    const std::unique_ptr<ILinearFeedbackShiftRegister>& m_lfsr;
    const std::unique_ptr<BasePeriodicSignal>& m_sourceSignal;

    double m_periodRatio;
private:
    void initialize();



    // ISampler interface
public:
    void produceSamples(unsigned numberOfSamples, const IWritter &writter);

private:
    virtual void incrementDiscreteTime() = 0;
    virtual void printOutputLine(const IWritter& writter) const = 0;
    virtual void printHeaderLine(const IWritter& writter) const = 0;
};

#endif // BASESAMPLER_H
