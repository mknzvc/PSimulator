#include "inifileconfiguration.h"
#include <QList>
#include <cmath>

#include <QDebug>

IniFileConfiguration::IniFileConfiguration(const QString &fileName)
    :m_settings(fileName, QSettings::IniFormat)
{
}

char IniFileConfiguration::getLSFRLength()
{
    return static_cast<char>(m_settings.value("maximum_length").toUInt());
}

unsigned IniFileConfiguration::getLSFRSeed()
{
    auto seed = m_settings.value("seed").toString();
    bool ok;
    return seed.toUInt(&ok, 16);
}

unsigned IniFileConfiguration::getResultMask()
{
    uint mask = 0;
    getMaskValue("result_bits", mask);
    return mask;
}

FeedbackType IniFileConfiguration::getFeedbackType()
{
    auto feedbackTypeValue = m_settings.value("feedback_type").toInt();

    FeedbackType feedbackType = FeedbackType::XOR;

    if(feedbackTypeValue == 0)
    {
        feedbackType = FeedbackType::XOR;
    }

    if(feedbackTypeValue == 1)
    {
        feedbackType = FeedbackType::XNOR;
    }

    return feedbackType;

}

unsigned IniFileConfiguration::getStepsCount()
{
    return m_settings.value("steps_count").toUInt();
}

unsigned IniFileConfiguration::getFeedbackMask()
{
   uint mask = 0;
   getMaskValue("feedback_bits", mask);
   return mask;
}

void IniFileConfiguration::getMaskValue(const QString& value_name, uint& out)
{
    auto list = m_settings.value(value_name).toList();

    auto length = m_settings.value("maximum_length").toUInt();


    QList<QVariant>::iterator it;

    for (it = list.begin(); it < list.end(); ++it)
    {
        utils::setBit(out, static_cast<char>((length - (*it).toUInt()) ));
    }
}

double IniFileConfiguration::getSourceSignalPeriode()
{
    return m_settings.value("T").toDouble();
}

double IniFileConfiguration::getSourceSignalSlope()
{
    return m_settings.value("slope").toDouble();
}

double IniFileConfiguration::getSourceSignalYIntercept()
{
    return m_settings.value("y_intercept").toDouble();
}

double IniFileConfiguration::getSamplingSignalRatio()
{
    auto ratioCoefs = m_settings.value("ratio").toList();

    if(ratioCoefs.empty())
    {
        return m_settings.value("ratio").toDouble();
    }

    QList<QVariant>::iterator it = ratioCoefs.begin();

    double ratio = (*it).toDouble();

    double n = 1.0;

    for (it = ratioCoefs.begin()+1; it < ratioCoefs.end(); ++it)
    {
        ratio +=  ( 1.0/(std::pow(2.0, n++)) ) * (*it).toDouble();
    }

    return ratio;
}

double IniFileConfiguration::getJitterPeriod()
{
    return m_settings.value("jitter_period").toDouble();
}

double IniFileConfiguration::getJitterSlope()
{
    return m_settings.value("jitter_slope").toDouble();
}

double IniFileConfiguration::getJitterYIntercept()
{
    return m_settings.value("jitter_y_intercept").toDouble();
}
