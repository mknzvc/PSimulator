#ifndef ILINEARFEEDBACKSHIFTREGISTER_H
#define ILINEARFEEDBACKSHIFTREGISTER_H


class ILinearFeedbackShiftRegister
{
public:
    ILinearFeedbackShiftRegister();
    virtual ~ILinearFeedbackShiftRegister();

    virtual void next() = 0;

    virtual char getRegisterSize() = 0;

    virtual char getOutputSize() = 0;

    virtual unsigned getMaxOutput() = 0;

    virtual unsigned getOutputValue() = 0;

    virtual unsigned getMaxSequence() = 0;
};

#endif // ILINEARFEEDBACKSHIFTREGISTER_H
