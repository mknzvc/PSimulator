#ifndef BASESAMPLER_H
#define BASESAMPLER_H

#include <memory>
#include "iwritter.h"
#include "ilinearfeedbackshiftregister.h"
#include "baseperiodicsignal.h"


class ISampler
{
public:
    ISampler(const std::unique_ptr<ILinearFeedbackShiftRegister>& lfsr,
             const std::unique_ptr<ISignal> &periodicSignal,
             const std::unique_ptr<ISignal> &timeJitterSignal,
             double periodRatio,
             double modulationIndex);

    virtual ~ISampler();

protected:
    double m_t;
    double m_Ts_0;
    const std::unique_ptr<ISignal>& m_sourceSignal;
    const std::unique_ptr<ISignal>& m_timeJitterSignal;
    const std::unique_ptr<ILinearFeedbackShiftRegister>& m_lfsr;

    bool m_include_jitter;

    double m_modulationIndex;

    std::fstream* m_help_fstream;


    double m_periodRatio;
private:
    void initialize();



    // ISampler interface
public:
    void produceSamples(unsigned numberOfSamples, const IWritter &writter);

private:
    virtual void incrementDiscreteTime() = 0;
    virtual void printOutputLine(const IWritter& writter) const;
    virtual void printHeaderLine(const IWritter& writter) const = 0;
};

#endif // BASESAMPLER_H
