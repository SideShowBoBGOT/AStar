#include "TPathFinding.h"

static const float s_fSqrtTwo = std::sqrtf(2);

void TPathFinding::Set(const TUPoint& origin, const TUPoint& destination, const std::shared_ptr<TAlgorithmMap>& map) {
	m_xOrigin = origin;
	m_xDestination = destination;
	m_pMap = map;
}

bool TPathFinding::IsCanCreatePath() {
	if(!m_pMap->Get(m_xOrigin)) return false;
	if(!m_pMap->Get(m_xDestination)) return false;
	if(m_xOrigin==m_xDestination) return false;
	return true;
}

TPathFinding::TPathNodeList TPathFinding::FindWalkableAdjacentNodes(const std::shared_ptr<TPathNode>& pathNode) const {
	auto pathList = TPathNodeList();
	auto pos = pathNode->Location;
	for(auto y=-1;y<=1;++y) {
		for(auto x=-1;x<=1;++x) {
			auto cell = TUPoint(pos.x + x, pos.y + y);
			if(m_pMap->IsIndexValid(cell) && m_pMap->Get(cell)) {
				pathList.emplace_back(std::make_shared<TPathNode>(cell, m_xDestination, pathNode, x!=0 && y!=0));
			}
		}
	}
	return pathList;
}

std::list<TUPoint> TPathFinding::CreatePath() {
	auto path = std::list<TUPoint>();
	if(!IsCanCreatePath()) return path;
	
	auto open = TPathNodeList();
	auto close = TPathNodeList();
	
	open.emplace_back(std::make_shared<TPathNode>(m_xOrigin, m_xDestination, nullptr, false));
	
	// Iterate while we have tile in the open list
	while(!open.empty()) {
		// Move the lowest score cell from open list to the closed list
		auto curr = GetNodeLowestScore(open.begin(), open.end());
		close.emplace_back(std::move(*curr));
		open.erase(curr);

		// If we just added the m_xDestination, we are done!
		// Backtrack to create the final path
		if(close.back()->Location==m_xDestination) {
			auto it = --close.end();
			while((*it)->parent!=nullptr) {
				path.emplace_back((*it)->Location);
				it = FindPathNode(close.begin(), close.end(), (*it)->parent->Location);
			}

			path.emplace_back(close.front()->Location);
			std::reverse(path.begin(), path.end());
			return path;
		}
		
		// Fill a list of all adjancent nodes
		for(auto&& node : FindWalkableAdjacentNodes(close.back())) {
			if(FindPathNode(close.begin(), close.end(), node->Location)!=close.end()) {
				continue;
			}
			// If it is already in the open list, check if it is a better path (compare G)
			auto findIt = FindPathNode(open.begin(), open.end(), node->Location);
			if(findIt!=open.end()) {
				const auto& findNode =  *findIt;
				if(node->GeneralScore<(*findIt)->GeneralScore) {
					findNode->parent = node->parent;
				}
			} else {
				open.emplace_back(std::move(node));
			}
		}
	}
	return path;
}



TPathFinding::TPathNode::TPathNode(const TUPoint& pos, const TUPoint& m_xDestination, const std::shared_ptr<TPathNode>& parent, bool isDiagonal)
: Location{pos}, parent{parent}, IsDiagonal{isDiagonal} {
	if(!parent) return; 
	GeneralScore = parent->GeneralScore + (IsDiagonal ? s_fSqrtTwo : 1);
	HeuristicScore = Location.Distance<float>(m_xDestination);
}

float TPathFinding::TPathNode::Score() const {
	return GeneralScore + HeuristicScore;
}