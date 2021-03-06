#include "inifileconfiguration.h"
#include <QList>
#include <cmath>

IniFileConfiguration::IniFileConfiguration(const QString& fileName)
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

    return static_cast<FeedbackType>(feedbackTypeValue);
}

void IniFileConfiguration::getStepsCountList(std::list<unsigned>& countsList)
{
    auto qlist = m_settings.value("steps_count").toList();

    if(qlist.empty())
    {
        countsList.push_back(m_settings.value("steps_count").toUInt());
    }
    else
    {
        foreach (auto item, qlist)
        {
            countsList.push_back(item.toUInt());
        }
    }
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

double IniFileConfiguration::getSourceSignalValueRange()
{
    return m_settings.value("source_value_range").toDouble();
}

unsigned IniFileConfiguration::getSourceType()
{
    return m_settings.value("source_signal_type").toUInt();
}

double IniFileConfiguration::getSourceSignalPeriod()
{
    return m_settings.value("source_period").toDouble();
}

double IniFileConfiguration::getSourceSignalMeanValue()
{
    return m_settings.value("source_mean_value").toDouble();
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

double IniFileConfiguration::getJitterModulationIndex()
{
    return m_settings.value("jitter_modulation_index").toDouble();
}

unsigned IniFileConfiguration::getCalculationType()
{
    return m_settings.value("sample_interval_calculation").toUInt();
}

unsigned IniFileConfiguration::getJitterType()
{
    return m_settings.value("jitter_type").toUInt();
}

OutputType IniFileConfiguration::getOutputType()
{
    unsigned type =  m_settings.value("output_type").toUInt();

    return static_cast<OutputType>(type);
}

BinaryCoding IniFileConfiguration::getBinaryCoding()
{
    unsigned code =  m_settings.value("binary_code").toUInt();

    return static_cast<BinaryCoding>(code);
}
