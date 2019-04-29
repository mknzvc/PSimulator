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

    unsigned getStepsCount();    

    virtual double getSourceSignalPeriode();
    virtual double getSourceSignalSlope();
    virtual double getSourceSignalYIntercept();
    virtual double getSamplingSignalRatio();

private:

    QSettings m_settings;

    void getMaskValue(const QString& value_name, uint& out);







};



#endif // INIFILECONFIGURATION_H
