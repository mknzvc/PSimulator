#ifndef SAMPLERFACTORY_H
#define SAMPLERFACTORY_H

#include "isampler.h"
#include <map>

//typedef ISampler* (*CreateSamplerFn)(void);

class SamplerFactory
{

//private:
    SamplerFactory();

//    typedef std::map<ISampler, int> FactoryMap;

//    FactoryMap m_FactoryMap;

//public:
//    ~SamplerFactory(){m_FactoryMap.clear();}

//    static SamplerFactory* Get()
//    {
//        static SamplerFactory instance;
//        return &instance;
//    }

//    void Register(const std::string& samplerName, CreateSamplerFn samplerCreate);
//    ISampler* CreateSampler(const std::string& samplerName);
};

#endif // SAMPLERFACTORY_H
