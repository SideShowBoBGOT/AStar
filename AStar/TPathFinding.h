#pragma once

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cmath>

#include "TAlgorithmMap.h"

class TPathFinding {
	public:
	TPathFinding()=default;
	virtual ~TPathFinding()=default;

	public:
	void Set(const TUPoint& origin, const TUPoint& destination, const std::shared_ptr<TAlgorithmMap>& map);
	std::list<TUPoint> CreatePath();
	
	protected:
	bool IsCanCreatePath();

	protected:
	struct TPathNode {
		TPathNode(const TUPoint& origin, const TUPoint& destination, const std::shared_ptr<TPathNode>& parent, bool diagonal);
		float Score() const;

		float GeneralScore = 0;
		float HeuristicScore = 0;
	
		TUPoint Location;
		std::shared_ptr<TPathNode> parent = nullptr;
		bool IsDiagonal;
	};
	
	protected:
	using TPathNodeList = std::list<std::shared_ptr<TPathNode>>;
	TPathNodeList FindWalkableAdjacentNodes(const std::shared_ptr<TPathNode>& pathNode) const; 
	
	protected:
	template<typename InIterator>
	static InIterator FindPathNode(const InIterator& begin, const InIterator& end, const TUPoint& point) {
		return std::find_if(begin, end,[point](const auto& node) { return node->Location==point; });
	}

	template<typename InIterator>
	static InIterator GetNodeLowestScore(const InIterator& begin, const InIterator& end) {
		return std::min_element(begin, end, [](const auto& lhs, const auto& rhs) {
			return lhs->Score()<rhs->Score();
		});
	}

	protected:
	TUPoint m_xOrigin = {0, 0};
	TUPoint m_xDestination = {0, 0};
	std::shared_ptr<TAlgorithmMap> m_pMap = nullptr;
};
