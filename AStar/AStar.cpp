#include "TAlgorithMapFactory.h"
#include "TPathFinding.h"

int main(int argc, char* argv[]) {
    auto map = TAlgorithMapFactory::ReadMapFile("map.txt");
    //auto map = TAlgorithMapFactory::GenerateMap({10, 10});
    auto alg = TPathFinding();
    alg.Set({0, 0}, {9, 9}, map);
    auto path = alg.CreatePath();
    map->Print(path);
    return 0;
}
