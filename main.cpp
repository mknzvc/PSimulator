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

    IConfiguration* configuration = new IniFileConfiguration(configFile);

    //qDebug()<<configuration->getSamplingSignalRatio();

    std::unique_ptr<BasePeriodicSignal> stsignal (new SawToothSignal(configuration->getSourceSignalSlope(),
                                        configuration->getSourceSignalYIntercept(),
                                        configuration->getSourceSignalPeriode()));

    std::unique_ptr<BasePeriodicSignal> jsignal (new JitterSignal(200));

    std::unique_ptr<ILinearFeedbackShiftRegister> lfsr(new LinearFeedbackShiftRegister(
                    configuration->getLSFRLength(),
                    configuration->getLSFRSeed(),
                    configuration->getFeedbackType(),
                    configuration->getFeedbackMask(),
                    configuration->getResultMask()));


    ISampleManager *sampler = new SamplerManager
            (lfsr, stsignal, jsignal, configuration->getSamplingSignalRatio());

    std::fstream outputStream;
    std::unique_ptr<IWritter> writter ( new CSVWritter(&outputStream, "output.csv"));

    sampler->produceSamples(configuration->getStepsCount(), *writter);

/*



    for (unsigned i = 0; i < configuration->getStepsCount(); i++)
    {

        lfsr->next();
        std::cout << QString("%1").arg(lfsr->getMaxSequence(), 16, 2, QChar('0')).toStdString()<<std::endl;
    }

*/

    return 0;
}
