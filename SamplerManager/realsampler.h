#ifndef REALSAMPLER_H
#define REALSAMPLER_H

#include "isampler.h"
#include <fstream>

class RealSampler : public ISampler
{
public:
    RealSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                const std::unique_ptr<ISignal> &periodicSignal,
                const std::unique_ptr<ISignal> &timeJitterSignal,
                double sourcePeriod,
                double periodRatio,
                double modulationIndex);

    ~RealSampler();

protected:

    void initialize();


private:
    virtual void incrementDiscreteTime();
    //virtual void printOutputLine(const IWritter &writter) const;
    virtual void printHeaderLine(const IWritter &writter) const;

public:

    static std::unique_ptr<ISampler>  Create(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                                             const std::unique_ptr<ISignal> &periodicSignal,
                                             const std::unique_ptr<ISignal> &timeJitterSignal,
                                             double sourcePeriod,
                                             double periodRatio,
                                             double modulationIndex)
    {
        return std::unique_ptr<ISampler>(new RealSampler(lfsr, periodicSignal, timeJitterSignal, sourcePeriod, periodRatio, modulationIndex));
    }


};

#endif // REALSAMPLER_H
