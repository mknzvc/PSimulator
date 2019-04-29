#include "isamplemanager.h"

ISampleManager::ISampleManager(double samplingInterval)
    :m_curent_time(0),
     m_samplingInterval(samplingInterval)
{   
}

ISampleManager::~ISampleManager()
{
}
