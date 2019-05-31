#ifndef FSAMPLER_H
#define FSAMPLER_H

#include "isampler.h"
#include <fstream>
#include <memory>

class FSampler : public ISampler
{
public:
    FSampler(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
             const std::unique_ptr<ISignal> &periodicSignal,
             const std::unique_ptr<ISignal> &timeJitterSignal,
             double periodRatio,
             double modulationIndex);
    ~FSampler();

protected:

    double m_tn_prev;



    void initialize();

    // ISampler interface
private:
    virtual void incrementDiscreteTime();
    //virtual void printOutputLine(const IWritter &writter) const;
    virtual void printHeaderLine(const IWritter &writter) const;


public:

    static std::unique_ptr<ISampler> Create(const std::unique_ptr<ILinearFeedbackShiftRegister> &lfsr,
                              const std::unique_ptr<ISignal> &periodicSignal,
                              const std::unique_ptr<ISignal> &timeJitterSignal,
                              double periodRatio,
                              double modulationIndex)
    {
        return std::unique_ptr<ISampler>(new FSampler(lfsr, periodicSignal, timeJitterSignal, periodRatio, modulationIndex));
    }
};

#endif // FSAMPLER_H
