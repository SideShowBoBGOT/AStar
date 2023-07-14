#ifndef _TALGORITHMMAPFACTORY_H_H_
#define _TALGORITHMMAPFACTORY_H_H_

#include "TPoint.h"
#include "TAlgorithmMap.h"

class TAlgorithmMap;

class TAlgorithMapFactory {
    public:
    TAlgorithMapFactory()=default;
    virtual ~TAlgorithMapFactory()=default;

    public:
    static std::shared_ptr<TAlgorithmMap> GenerateMap(const TUPoint& size);
    static std::shared_ptr<TAlgorithmMap> ReadMapFile(const std::string& fileName);
    static TUPoint GetMapSizeFromFile(const std::string& fileName);
};

#endif
