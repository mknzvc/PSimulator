#ifndef ISIGNALMODEL_H
#define ISIGNALMODEL_H


class ISignal
{
public:
    ISignal();
    virtual ~ISignal();

    virtual double value(double time) const = 0;

    virtual double getPeriod() const = 0;

private:
    virtual double func(double x) const = 0;

};

#endif // ISIGNALMODEL_H
