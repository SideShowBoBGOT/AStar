#include "TAlgorithMapFactory.h"
#include <iostream>
#include <fstream>

std::shared_ptr<TAlgorithmMap> TAlgorithMapFactory::GenerateMap(const TUPoint& size) {
    auto map = std::make_shared<TAlgorithmMap>();
    map->Resize(size);
    for(unsigned y=0;y<size.y;++y) {
        for(unsigned x=0;x<size.x;++x) {
            map->Set({x, y}, rand() % 2);
        }
    }
    return map;
}

TUPoint TAlgorithMapFactory::GetMapSizeFromFile(const std::string& fileName) {
    auto y = 0u;
    {
        auto file = std::ifstream(fileName);
        y = std::count(std::istreambuf_iterator<char>(file), 
                   std::istreambuf_iterator<char>(), '\n');
    }
    auto x = 0u;
    {
        auto file = std::ifstream(fileName);
        auto line = std::string();
        std::getline(file, line);
        x = line.size();
    }
    return {x, y};
}

std::shared_ptr<TAlgorithmMap> TAlgorithMapFactory::ReadMapFile(const std::string& fileName) {
    auto size = GetMapSizeFromFile(fileName);
    auto map = std::make_shared<TAlgorithmMap>();
    map->Resize(size);

    auto file = std::ifstream(fileName);
    for(unsigned y=0;y<size.y;++y) {
        auto line = std::string();
        std::getline(file, line);
        for(unsigned x=0;x<size.x;++x) {
            map->Set({x, y}, line[x]==' ');
        }
    }
    return map;
}