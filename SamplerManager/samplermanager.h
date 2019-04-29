#ifndef SAMPLERMANAGER_H
#define SAMPLERMANAGER_H

#include <memory>
#include "iconfiguration.h"
#include "iwritter.h"
#include "ilinearfeedbackshiftregister.h"
#include "isamplemanager.h"
#include "baseperiodicsignal.h"

class SamplerManager : public ISampleManager
{
public:
    SamplerManager(const std::unique_ptr<ILinearFeedbackShiftRegister>& lfsr,
                   const std::unique_ptr<BasePeriodicSignal> &periodicSignal,
                   const std::unique_ptr<BasePeriodicSignal> &timeJitterSignal,
                   double periodRatio);
    virtual ~SamplerManager();

private:

    const std::unique_ptr<ILinearFeedbackShiftRegister>& m_lfsr;
    const std::unique_ptr<BasePeriodicSignal>& m_periodicSignal;
    const std::unique_ptr<BasePeriodicSignal>& m_timeJitterSignal;

    double m_periodRatio;



    void initialize();


public:
    virtual void produceSamples(unsigned numberOfSamples, const IWritter &writter);
};

#endif // SAMPLERMANAGER_H
