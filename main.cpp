#include <QString>
#include "iconfiguration.h"
#include "inifileconfiguration.h"
#include "ilinearfeedbackshiftregister.h"
#include "linearfeedbackshiftregister.h"
#include "isignal.h"
#include "sawtoothsignal.h"
#include "trianglesignal.h"
#include "isampler.h"
#include "csvwritter.h"
#include "triangledistrrandomsignal.h"

#include "samplerfactory.h"
#include "signalfactory.h"

#include <iostream>
#include <fstream>



int main(int argc, char *argv[])
{
    std::string configFileCStr = argv[1];
    std::string outputFileName = argv[2];

    QString configFile = QString::fromStdString(configFileCStr);
    //QString outputFileName = QString::fromStdString(outputFileNameCStr);

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



    std::unique_ptr<ISignal> ssignal;

    ssignal = SignalFactory::Get()->CreateSignal(configuration->getSourceType(),
                                                 configuration->getSourceSignalValueRange(),
                                                 configuration->getSourceSignalPeriod(),
                                                 configuration->getSourceSignalMeanValue());




    std::unique_ptr<ISignal> jsignal;

    jsignal = SignalFactory::Get()->CreateSignal(configuration->getJitterType(),
                                                 2.0,
                                                 configuration->getJitterPeriod());




    std::unique_ptr<ILinearFeedbackShiftRegister> lfsr(new LinearFeedbackShiftRegister(
                    configuration->getLSFRLength(),
                    configuration->getLSFRSeed(),
                    configuration->getFeedbackType(),
                    configuration->getFeedbackMask(),
                    configuration->getResultMask()));


    std::unique_ptr<ISampler> realSampler;

    realSampler = SamplerFactory::Get()->CreateSampler(configuration->getCalculationType(), lfsr, ssignal, jsignal,
                                                       configuration->getSourceSignalPeriod(),
                                                       configuration->getSamplingSignalRatio(),
                                                       configuration->getJitterModulationIndex());


    std::list<unsigned> sampleNoList;

    configuration->getStepsCountList(sampleNoList);

    OutputType outType = configuration->getOutputType();
    BinaryCoding binCodeType = configuration->getBinaryCoding();


    for (auto listIt = sampleNoList.begin(); listIt != sampleNoList.end(); listIt++)
    {
        std::unique_ptr<IWritter> writter
                (new CSVWritter(outputFileName + "_" + std::to_string(*listIt) + ".csv",
                 outType, binCodeType));

       std::cout<<std::endl<<std::to_string(*listIt/1000) + "_k: sampling started... ";

       realSampler->produceSamples(*listIt, *writter);

       std::cout<<"sample finished."<<std::endl;

    }
    std::cout<<"finished."<<std::endl<<std::endl;


    delete configuration;    

    return 0;
}
