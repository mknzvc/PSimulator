#ifndef LINEARFEEDBACKSHIFTREGISTER_H
#define LINEARFEEDBACKSHIFTREGISTER_H

#include "ilinearfeedbackshiftregister.h"
#include "ps_utils.h"
using namespace types;

typedef unsigned (*FeedbackFunction)(unsigned, unsigned);

class LinearFeedbackShiftRegister : public ILinearFeedbackShiftRegister
{
public:
    LinearFeedbackShiftRegister(char size,
                                unsigned initial_value,
                                FeedbackType feedbackType,
                                unsigned feedbackMask,
                                unsigned resultMask);
    ~LinearFeedbackShiftRegister();


public:
    void next();
    unsigned getOutputValue();
    unsigned getMaxSequence();
    char getRegisterSize(){return m_size;}
    virtual char getOutputSize();

private:
    char m_size;
    unsigned m_value;
    FeedbackType m_feedbackType;
    unsigned m_feedbackMask;
    unsigned m_resultMask;

    FeedbackFunction m_feedbackFuncion;
    unsigned m_neutralFeedbackElement;

    unsigned calculateParityBit();

    void initialize();

};

#endif // LINEARFEEDBACKSHIFTREGISTER_H
