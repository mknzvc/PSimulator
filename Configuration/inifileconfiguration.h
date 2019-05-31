#ifndef INIFILECONFIGURATION_H
#define INIFILECONFIGURATION_H

#include "iconfiguration.h"

#include <QSettings>


class IniFileConfiguration : public IConfiguration
{
public:
    //IniFileConfiguration();
    IniFileConfiguration(const QString& fileName);

    virtual char getLSFRLength();
    virtual unsigned getLSFRSeed();
    virtual unsigned getFeedbackMask();
    virtual unsigned getResultMask();
    virtual FeedbackType getFeedbackType();

    virtual void getStepsCountList(std::list<unsigned>& countsList);


    virtual double getSourceSignalPeriod();
    virtual double getSourceSignalMeanValue();
    virtual double getSourceSignalValueRange();
    virtual unsigned getSourceType();

    virtual double getSamplingSignalRatio();

    virtual double getJitterPeriod();
    virtual double getJitterModulationIndex();

    virtual unsigned getCalculationType();

    virtual unsigned getJitterType();


    virtual OutputType getOutputType();

    virtual BinaryCoding getBinaryCoding();

private:

    QSettings m_settings;

    void getMaskValue(const QString& value_name, uint& out);

};



#endif // INIFILECONFIGURATION_H
