#ifndef REALSAMPLER_H
#define REALSAMPLER_H

#include "basesampler.h"


class RealSampler : public BaseSampler
{
public:
    RealSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                const std::unique_ptr<BasePeriodicSignal> &timeJitterSignal,
                double periodRatio,
                double modulationIndex);

private:
    const std::unique_ptr<BasePeriodicSignal>& m_timeJitterSignal;

    bool m_include_jitter;

    double m_modulationIndex;

    void initialize();

    // ISampleManager interface

private:
    virtual void incrementDiscreteTime();
    virtual void printOutputLine(const IWritter &writter) const;
    virtual void printHeaderLine(const IWritter &writter) const;
};

#endif // REALSAMPLER_H
