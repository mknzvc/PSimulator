#include <QString>
#include <QDebug>
#include "iconfiguration.h"
#include "inifileconfiguration.h"
#include "ilinearfeedbackshiftregister.h"
#include "linearfeedbackshiftregister.h"
#include "isignalmodel.h"
#include "sawtoothsignal.h"
#include "jittersignal.h"
#include "isamplemanager.h"
#include "samplermanager.h"
#include "csvwritter.h"

#include <iostream>
#include <fstream>



int main(int argc, char *argv[])
{
    QString configFile = argv[1];
    QString outputFileName = argv[2];

    IConfiguration* configuration = new IniFileConfiguration(configFile);

    //qDebug()<<configuration->getSamplingSignalRatio();

    std::unique_ptr<BasePeriodicSignal> stsignal (new SawToothSignal(configuration->getSourceSignalSlope(),
                                        configuration->getSourceSignalYIntercept(),
                                        configuration->getSourceSignalPeriode()));

    std::unique_ptr<BasePeriodicSignal> jsignal (new JitterSignal(configuration->getJitterSlope(),
                                                                  configuration->getJitterYIntercept(),
                                                                  configuration->getJitterPeriod()));

    std::unique_ptr<ILinearFeedbackShiftRegister> lfsr(new LinearFeedbackShiftRegister(
                    configuration->getLSFRLength(),
                    configuration->getLSFRSeed(),
                    configuration->getFeedbackType(),
                    configuration->getFeedbackMask(),
                    configuration->getResultMask()));


    ISampleManager *sampler = new SamplerManager
            (lfsr, stsignal, jsignal, configuration->getSamplingSignalRatio());

    std::fstream outputStream;
    std::unique_ptr<IWritter> writter ( new CSVWritter(&outputStream, (outputFileName+".csv").toStdString()));

    sampler->produceSamples(configuration->getStepsCount(), *writter);

    return 0;
}
