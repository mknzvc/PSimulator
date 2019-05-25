#ifndef FSAMPLER_H
#define FSAMPLER_H

#include "basesampler.h"
#include <fstream>

class FSampler : public BaseSampler
{
public:
    FSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
             const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
             const std::unique_ptr<BasePeriodicSignal> &timeJitterSignal,
             double periodRatio,
             double modulationIndex);
    ~FSampler();

protected:
    const std::unique_ptr<BasePeriodicSignal>& m_timeJitterSignal;

    bool m_include_jitter;

    double m_modulationIndex;

    double m_tn_prev;

    std::fstream* m_help_fstream;

    void initialize();

    // ISampler interface
private:
    virtual void incrementDiscreteTime();
    virtual void printOutputLine(const IWritter &writter) const;
    virtual void printHeaderLine(const IWritter &writter) const;
};

#endif // FSAMPLER_H
