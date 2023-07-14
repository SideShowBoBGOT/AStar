#include "TAlgorithmMap.h"

const std::string TAlgorithmMap::s_sInvalidIndexError = "Invalid index";

TAlgorithmMap::TAlgorithmMap(const TUPoint& size) {
    Resize(size);
}

void TAlgorithmMap::Resize(const TUPoint& size) {
    m_xSize = size;
    m_vMap.resize(m_xSize.x * m_xSize.y);
}

void TAlgorithmMap::Set(const TUPoint& index, bool isWalkable) {
    CheckIndex(index);
    m_vMap[CalcIndex(index)] = isWalkable;
}

bool TAlgorithmMap::Get(const TUPoint& index) const {
    CheckIndex(index);
    return m_vMap[CalcIndex(index)];
}

unsigned TAlgorithmMap::CalcIndex(const TUPoint& index) const noexcept{
    return index.y * m_xSize.x + index.x;
}

TUPoint TAlgorithmMap::Size() const {
    return m_xSize;
}

bool TAlgorithmMap::IsIndexValid(unsigned index) const {
    return index < m_vMap.size();
}

bool TAlgorithmMap::IsIndexValid(const TUPoint& index) const {
    return CalcIndex(index) < m_vMap.size();
}

void TAlgorithmMap::CheckIndex(const TUPoint& index) const {
    if(IsIndexValid(index)) return;
    throw std::invalid_argument(s_sInvalidIndexError);
}

void TAlgorithmMap::Print() {
    for(unsigned y=0;y<m_xSize.y;++y) {
        for(unsigned x=0;x<m_xSize.x;++x) {
            std::cout << (Get({x, y}) ? " " : "#");
        }
        std::cout << "\n";
    }
}

void TAlgorithmMap::Print(const std::list<TUPoint>& path) {
    for(unsigned y=0;y<m_xSize.y;++y) {
        for(unsigned x=0;x<m_xSize.x;++x) {
            if(std::find(path.begin(), path.end(), TUPoint(x, y))!=path.end()) {
                std::cout << '*';
            } else {
                std::cout << (Get({x, y}) ? ' ' : '#');
            }
        }
        std::cout << "\n";
    }
}
