#ifndef _TALGORITHMMAP_H_H_
#define _TALGORITHMMAP_H_H_

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <list>

#include "TPoint.h"

class TAlgorithmMap {
    public:
    TAlgorithmMap()=default;
    TAlgorithmMap(const TUPoint& size);
    virtual ~TAlgorithmMap()=default;

    public:
    void Resize(const TUPoint& size);
    TUPoint Size() const;

    public:
    void Set(const TUPoint& index, bool isWalkable);
    bool Get(const TUPoint& index) const;

    public:
    // Just calculates possible index base on point and size of the map and does not trow
    unsigned CalcIndex(const TUPoint& index) const noexcept;
    void CheckIndex(const TUPoint& index) const;
	
    bool IsIndexValid(unsigned index) const;
    bool IsIndexValid(const TUPoint& index) const;

	public:
	void Print();
	void Print(const std::list<TUPoint>& path);
	
    protected:
    TUPoint m_xSize = {0, 0};
    std::vector<bool> m_vMap;

    protected:
    static const std::string s_sInvalidIndexError;
};

#endif