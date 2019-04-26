#include "iconfiguration.h"

IConfiguration::IConfiguration()
{
}

IConfiguration::~IConfiguration()
{
}

unsigned IConfiguration::getStepsCount()
{
    return 0;
}

FeedbackType IConfiguration::getFeedbackType()
{
    return FeedbackType::XOR;
}

char IConfiguration::getLSFRLength()
{
    return 0;
}

unsigned IConfiguration::getLSFRSeed()
{
    return 0;
}

unsigned IConfiguration::getResultMask()
{
    return 0;
}

unsigned IConfiguration::getFeedbackMask()
{
    return 0;
}


