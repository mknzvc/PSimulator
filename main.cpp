#include <QString>
#include <QDebug>
#include "iconfiguration.h"
#include "inifileconfiguration.h"
#include "ilinearfeedbackshiftregister.h"
#include "linearfeedbackshiftregister.h"

#include <iostream>



int main(int argc, char *argv[])
{
    QString configFile = argv[1];

    IConfiguration* configuration = new IniFileConfiguration(configFile);    

    ILinearFeedbackShiftRegister* lfsr = new LinearFeedbackShiftRegister(
                configuration->getLSFRLength(),
                configuration->getLSFRSeed(),
                configuration->getFeedbackType(),
                configuration->getFeedbackMask(),
                configuration->getResultMask());



    for (unsigned i = 0; i < configuration->getStepsCount(); i++)
    {

        lfsr->next();
        std::cout << QString("%1").arg(lfsr->getMaxSequence(), 16, 2, QChar('0')).toStdString()<<std::endl;
    }    

    return 0;
}
