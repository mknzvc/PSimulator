#ifndef SAMPLERMANAGER_H
#define SAMPLERMANAGER_H

#include <memory>
#include "iconfiguration.h"
#include "basesampler.h"

class Sampler : public BaseSampler
{
public:
    Sampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                   const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                   const std::unique_ptr<BasePeriodicSignal>& timeJitterSignal,
                   double periodRatio);
    virtual ~Sampler();

private:

    const std::unique_ptr<BasePeriodicSignal>& m_timeJitterSignal;

    bool m_include_jitter;

    void initialize();




// ISampler interface
private:
    virtual void incrementDiscreteTime();

    virtual void printOutputLine(const IWritter &writter) const;
    virtual void printHeaderLine(const IWritter &writter) const;
};

#endif // SAMPLERMANAGER_H
