#pragma once


#include "stadfx.h"
#include "bgeometry.h"
#include "planningMap.h"

namespace pl {

	enum AnchorIndex { aiBottomLeft, aiBottom, aiBottomRight, aiLeft, aicentre, aiRight, aiTopLeft, aiTop, aiTopRight };
	using pm::Cartesian;
	using pm::GridIndex;
	using pm::MapType;
	
	double calDisHInPnt(bgeo::DPoint3D const& pnt, bgeo::DPoint3D const& _target);

	class ANode
	{
	public:
		ANode();
		ANode& operator =(const ANode& a);
		ANode(bgeo::DPoint3D pnt, double disg, int dir, 
			GridIndex ind,GridIndex par, bgeo::DPoint3D  _target);

		~ANode();
		bgeo::DPoint3D _pnt;
		GridIndex _pntInd;
		GridIndex _parentInd;
		//direction 
		size_t _dir;
		double disH = 0;
		double disG = 0;
		double disF = 0;
		GridIndex parent;
	private:

	};
	using MNode = pair<GridIndex, ANode>;


	class APlan
	{

	public:
		APlan();
		~APlan();

		bool setStartPnt(double const& x, double const& y);
		bool setTargetPnt(double const& x, double const& y);

		bool setStartPnt(double const& x, double const& y, double const& z);
		bool setTargetPnt(double const& x, double const& y, double const& z);

		bool setStartAndTargetPnt(double const& s_x, double const& s_y, double const& t_x, double const& t_y);

		void setAgentType(size_t const& _type) { _m_agentType = _type; }


		bool loadMap(pm::Map3D& _map);


		int failIndex = 1;
		void setMaxSearchTimes(const size_t& st) { this->_m_maxSearhTimes = st; }


		bool target2Grid();
		bool start2Grid();
		bool AstarPlan();

		vector<bgeo::DPoint3D> get3DPath() const { return this->m_path3D; }
		vector<bgeo::DPoint> get2DPath() const { return this->m_path2D; }

		pm::Map3D _m_map;
		pm::GridMap _m_AGridMap;
	private:

		bgeo::DPoint3D m_targetPnt3D;
		bgeo::DPoint3D m_startPnt3D;

		bgeo::DPoint m_startPnt;
		bgeo::DPoint m_targetPnt;

		pm::GridIndex m_Tindex;
		pm::GridIndex m_Sindex;


		vector<bgeo::DPoint3D> m_path3D;
		vector<bgeo::DPoint> m_path2D;
		double gridSize;

		std::list<ANode> m_openList;
		std::list<pm::GridIndex> m_openSet;
		std::map<pm::GridIndex, ANode> m_closeList;
		std::set<pm::GridIndex> m_closeSet;
		std::vector<ANode> m_closeVect;

		bool AstarSearch();
		bool AstarPathFinder();

		size_t _m_agentType = 0;
		double _m_crossAbi;

		// max search time
		size_t _m_maxSearhTimes = 20000;



		void SortedAddToOpenList(ANode const& mNode);
		std::vector<GridIndex> getNeighbor(GridIndex const& mindex, std::vector<size_t>& vdirIndex);

		double calDisH(ANode const& a_node) const;

		double calDistance(GridIndex const& aInd, GridIndex const& bInd) 
		{
			return boost::geometry::distance(this->_m_AGridMap[aInd]._pnt, this->_m_AGridMap[bInd]._pnt);
		}
	};
}


