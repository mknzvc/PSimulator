#include "inifileconfiguration.h"
#include <QList>

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
