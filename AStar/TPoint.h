#ifndef _TPOINT_H_H_
#define _TPOINT_H_H_

#include <type_traits>
#include <cmath>

template<typename T>
using CIsDoubleConvertible = std::enable_if_t<std::is_convertible_v<T, double>, int>;

template<typename T, CIsDoubleConvertible<T> = 0>
class TPoint;

using TIPoint = TPoint<int>;
using TUPoint = TPoint<unsigned>;

template<typename T, CIsDoubleConvertible<T>>
class TPoint {
	public:
	T x = 0;
	T y = 0;
		
	public:
	TPoint()=default;
	TPoint(T x1, T y1) { Set(x1, y1); }

	public:
	bool operator==(const TPoint& p) const { return IsEqual(p); }
	bool operator!=(const TPoint& p) const { return !IsEqual(p); }
	bool operator<(const TPoint& p) const { return x!=p.x?x<p.x:y<p.y; }
	TPoint operator+(const TPoint& p) const { return TPoint(x+p.x, y+p.y); }
	TPoint operator-(const TPoint& p) const { return TPoint(x-p.x, y-p.y); }
	void operator+=(const TPoint& p) { x += p.x; y += p.y; }
	void operator*=(const TPoint& p) { x *= p.x; y *= p.y; }

	const int& operator[](unsigned idx) const { return ((int*)this)[idx]; }
	int& operator[](unsigned idx) { return ((int*)this)[idx]; }

	public:
	void Set(T x1, T y1) { x = x1; y = y1; }
	void Set(const TPoint& p);

	public:
	bool IsEqual(const TPoint& p) const { return x==p.x && y==p.y; }

	public:
	template<typename DistanceType, CIsDoubleConvertible<DistanceType> = 0>
	DistanceType Distance(const TPoint& p) const {
		int xx = p.x - x;
		int yy = p.y - y;
		return DistanceType(std::sqrt( xx*xx + yy*yy ));
	}

	public:
	T Distance2(const TPoint& p) const {
		int xx = p.x - x;
		int yy = p.y - y;
		return xx*xx + yy*yy;
	}

	public:
	template<typename Other, CIsDoubleConvertible<T> = 0>
	TPoint<Other> CastTo() const {
		return TPoint(Other(x), Other(y));
	}
};

#endif