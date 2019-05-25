#include "linearfeedbackshiftregister.h"
#include <cmath>

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

LinearFeedbackShiftRegister::~LinearFeedbackShiftRegister()
{
}

void LinearFeedbackShiftRegister::next()
{
    unsigned pBit = calculateParityBit();

    //shift value
    m_value = m_value >> 1;

    //add calucated bit
    if(pBit) { utils::setBit(m_value, m_size-1); }
    else { utils::unsetBit(m_value, m_size-1); }
}

unsigned LinearFeedbackShiftRegister::getOutputValue()
{
    unsigned curentValue = 0;
    char resultPos = 0;

    for (char pos = 0; pos < m_size; ++pos)
    {
        if(utils::getNthBit(m_resultMask, pos) == 1u)
        {
            unsigned bit = utils::getNthBit(m_value, pos);
            if(bit)
            {
                utils::setBit(curentValue, resultPos);
            }
            resultPos++;
        }
    }

    return curentValue;
}

unsigned LinearFeedbackShiftRegister::getMaxOutput()
{
    return static_cast<unsigned>( std::pow(2, this->getOutputSize()) );
}

unsigned LinearFeedbackShiftRegister::getMaxSequence()
{
    return m_value;
}

char LinearFeedbackShiftRegister::getOutputSize()
{
    return utils::getOnesCount(m_resultMask);
}

unsigned LinearFeedbackShiftRegister::calculateParityBit()
{
    unsigned curentValue = m_neutralFeedbackElement;

    for (char pos = 0; pos < m_size; ++pos)
    {        
        if(utils::getNthBit(m_feedbackMask, pos) == 1u)
        {
            unsigned curentFeedbackBit = utils::getNthBit(m_value, pos);
            curentValue = m_feedbackFuncion(curentValue, curentFeedbackBit);
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

