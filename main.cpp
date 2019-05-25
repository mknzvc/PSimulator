#include <QString>
#include <QDebug>
#include "iconfiguration.h"
#include "inifileconfiguration.h"
#include "ilinearfeedbackshiftregister.h"
#include "linearfeedbackshiftregister.h"
#include "isignal.h"
#include "sawtoothsignal.h"
#include "trianglesignal.h"
#include "isampler.h"
#include "realsampler.h"
#include "fsampler.h"
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
        std::cout<<"modulation index : " <<configuration->getJitterModulationIndex()<<std::endl;
        std::cout<<"jitter periode   : " <<configuration->getJitterPeriod()<<std::endl;
    }



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

    std::unique_ptr<BasePeriodicSignal> jsignal (new TriangleSignal(2.0,
                                                                    configuration->getJitterPeriod()));

    std::unique_ptr<ILinearFeedbackShiftRegister> lfsr(new LinearFeedbackShiftRegister(
                    configuration->getLSFRLength(),
                    configuration->getLSFRSeed(),
                    configuration->getFeedbackType(),
                    configuration->getFeedbackMask(),
                    configuration->getResultMask()));


    ISampler *realSampler;

    if(configuration->getCalculationType() == 0)
    {
        realSampler = new RealSampler
                (lfsr, ssignal, jsignal,
                 configuration->getSamplingSignalRatio(),
                 configuration->getJitterModulationIndex());
    }
    else if (configuration->getCalculationType() == 1)
    {
        realSampler = new FSampler
                (lfsr, ssignal, jsignal,
                 configuration->getSamplingSignalRatio(),
                 configuration->getJitterModulationIndex());
    }





    std::list<unsigned> sampleNoList;
    configuration->getStepsCountList(sampleNoList);

    OutputType outType = configuration->getOutputType();


    for (auto listIt = sampleNoList.begin(); listIt != sampleNoList.end(); listIt++)
    {
        std::unique_ptr<IWritter> writter
                (new CSVWritter(outputFileName.toStdString() + "_" + std::to_string(*listIt) + ".csv",
                 outType));

       std::cout<<std::endl<<std::to_string(*listIt/1000) + "_k: sampling started... ";

       realSampler->produceSamples(*listIt, *writter);

       std::cout<<"sample finished."<<std::endl;

    }
    std::cout<<"finished."<<std::endl<<std::endl;


    delete configuration;
    delete realSampler;

    return 0;
}
