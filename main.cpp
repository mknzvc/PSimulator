#include <QString>
#include <QDebug>
#include "iconfiguration.h"
#include "inifileconfiguration.h"
#include "ilinearfeedbackshiftregister.h"
#include "linearfeedbackshiftregister.h"
#include "isignalmodel.h"
#include "sawtoothsignal.h"
#include "trianglesignal.h"
#include "isampler.h"
#include "samplermanager.h"
#include "realsampler.h"
#include "csvwritter.h"

#include <iostream>
#include <fstream>



int main(int argc, char *argv[])
{
    QString configFile = argv[1];
    QString outputFileName = argv[2];

    IConfiguration* configuration = new IniFileConfiguration(configFile);

    std::cout<<std::endl<<"PSimulator"<<std::endl<<std::endl;

    std::cout<<(unsigned)configuration->getLSFRLength()<<"bit LFSR"<<std::endl;
    std::cout<<"initial value  : "<<configuration->getLSFRSeed()<<std::endl;
    std::cout<<"feedback bits  : "<<configuration->getFeedbackMask()<<std::endl;
    std::cout<<"result bits    : "<<configuration->getResultMask()<<std::endl<<std::endl;

    std::cout<<"source signal periode : "<<configuration->getSourceSignalPeriod()<<std::endl<<std::endl;

    std::cout<<"T/Ts = "<<configuration->getSamplingSignalRatio()<<std::endl;

    if(configuration->getJitterPeriod() != 0)
    {
        std::cout<<std::endl;
        std::cout<<"jitter max     : " <<configuration->getJitterMaxValue()<<std::endl;
        std::cout<<"jitter periode : " <<configuration->getJitterPeriod()<<std::endl;
    }

    //qDebug()<<configuration->getSamplingSignalRatio();

    std::unique_ptr<BasePeriodicSignal> ssignal;

    if(configuration->getSourceType() == 0)
    {
        ssignal = std::unique_ptr<BasePeriodicSignal>(new TriangleSignal(configuration->getSourceSignalValueRange(),
                                                                         configuration->getSourceSignalPeriod(),
                                                                         configuration->getSourceSignalMeanValue()));
    }else if(configuration->getSourceType() == 1)
    {
        ssignal = std::unique_ptr<BasePeriodicSignal>(new SawToothSignal(configuration->getSourceSignalValueRange(),
                                                                         configuration->getSourceSignalPeriod(),
                                                                         configuration->getSourceSignalMeanValue()));
    }else {}

    std::unique_ptr<BasePeriodicSignal> jsignal (new TriangleSignal(configuration->getJitterMaxValue(),
                                                                    configuration->getJitterPeriod()));

    std::unique_ptr<ILinearFeedbackShiftRegister> lfsr(new LinearFeedbackShiftRegister(
                    configuration->getLSFRLength(),
                    configuration->getLSFRSeed(),
                    configuration->getFeedbackType(),
                    configuration->getFeedbackMask(),
                    configuration->getResultMask()));


    ISampler *realSampler = new RealSampler
            (lfsr, ssignal, jsignal,
             configuration->getSamplingSignalRatio(),
             configuration->getJitterModulationIndex());


    std::fstream outputStream;
    std::unique_ptr<IWritter> writter ( new CSVWritter(&outputStream, (outputFileName+".csv").toStdString()));


    std::cout<<std::endl<<"sampling started..."<<std::endl;

    realSampler->produceSamples(configuration->getStepsCount(), *writter);


    std::cout<<"finished."<<" "<<configuration->getStepsCount()<<" samples taken."<<std::endl;

    delete configuration;
    delete realSampler;

    return 0;
}
