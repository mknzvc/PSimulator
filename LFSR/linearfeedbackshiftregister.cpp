#include "linearfeedbackshiftregister.h"

#include <QDebug>

LinearFeedbackShiftRegister::LinearFeedbackShiftRegister(char size,
                                                         unsigned initialValue,
                                                         FeedbackType feedbackType,
                                                         unsigned feedbackMask,
                                                         unsigned resultMask)
    : m_size(size),
      m_value(initialValue),
      m_feedbackType(feedbackType),
      m_feedbackMask(feedbackMask),
      m_resultMask(resultMask)
{
    initialize();
}

void LinearFeedbackShiftRegister::next()
{
    unsigned pBit = calculateParityBit(m_feedbackFuncion, m_value, m_feedbackMask, m_size, m_neutralFeedbackElement);   

    //shift value
    m_value = m_value >> 1;

    //add calucated bit
    if(pBit) { utils::setBit(m_value, m_size-1); }
    else { utils::unsetBit(m_value, m_size-1); }
}

unsigned LinearFeedbackShiftRegister::getCurentResultValue()
{
    return m_value;
}

unsigned LinearFeedbackShiftRegister::getMaxSequence()
{
    return m_value;
}

unsigned LinearFeedbackShiftRegister::calculateParityBit(FeedbackFunction func, const unsigned regValue, unsigned feedbackMask, char size, unsigned neutralElement)
{
    unsigned curentValue = neutralElement;    

    for (char pos = 0; pos < size; ++pos)
    {        
        if(utils::getNthBit(feedbackMask, pos) == 1u)
        {
            unsigned curentFeedbackBit = utils::getNthBit(regValue, pos);
            curentValue = func(curentValue, curentFeedbackBit);
        }
    }

    return curentValue;
}

void LinearFeedbackShiftRegister::initialize()
{
    m_feedbackFuncion = utils::bitwiseXOR;

    if(m_feedbackType == types::FeedbackType::XOR)
    {
        m_feedbackFuncion = utils::bitwiseXOR;
        m_neutralFeedbackElement = 0;
    }
    else if (m_feedbackType == types::FeedbackType::XNOR)
    {
        m_feedbackFuncion = utils::bitwiseXNOR;
        m_neutralFeedbackElement = 1;
    }
}

