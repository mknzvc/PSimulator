#ifndef ILINEARFEEDBACKSHIFTREGISTER_H
#define ILINEARFEEDBACKSHIFTREGISTER_H


class ILinearFeedbackShiftRegister
{
public:
    ILinearFeedbackShiftRegister();
    virtual ~ILinearFeedbackShiftRegister();

    virtual void next() = 0;

    virtual unsigned getCurentResultValue() = 0;

    virtual unsigned getMaxSequence() = 0;
};

#endif // ILINEARFEEDBACKSHIFTREGISTER_H
