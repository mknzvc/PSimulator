#ifndef FSAMPLER_H
#define FSAMPLER_H

#include "isampler.h"
#include <fstream>
#include <memory>

class SamplerFMod : public ISampler
{
public:
    SamplerFMod(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
             const std::unique_ptr<ISignal> &periodicSignal,
             const std::unique_ptr<ISignal> &timeJitterSignal,
             double sourcePeriod,
             double periodRatio,
             double modulationIndex);
    ~SamplerFMod();

protected:

    void initialize();

    // ISampler interface
private:
    virtual void incrementDiscreteTime();    
    virtual void printHeaderLine(const IWritter &writter) const;


public:

    static std::unique_ptr<ISampler> Create(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                                            const std::unique_ptr<ISignal> &periodicSignal,
                                            const std::unique_ptr<ISignal> &timeJitterSignal,
                                            double sourcePeriod,
                                            double periodRatio,
                                            double modulationIndex)
    {
        return std::unique_ptr<ISampler>(new SamplerFMod(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex));
    }
};

#endif // FSAMPLER_H
