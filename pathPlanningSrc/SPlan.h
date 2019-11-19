#pragma once
#include "stadfx.h"
#include "SPlan.h"
#include "APlan.h"
#include "bgeometry.h"
#include "planningMap.h"
namespace pl {
	using pm::Cartesian;
	using pm::MapType;
	using pm::GridIndex;
	enum GraphType {localGraph, totalGraph};
	class SPlan
	{
	public:
		SPlan();
		~SPlan();
		bool setRange(bgeo::DRing const &range) { this->_m_range = range; return false; };
		bool setRange(std::vector<double> & vx, std::vector<double> &vy);

		bool setPosition(double const &x, double const &y)
		{
			this->_m_startPnt.x(x);
			this->_m_startPnt.y(y);
			
			return false;
		}
		bool setPosition(double const &x, double const &y, double const &z){
			this->_m_startPnt3D.set<Cartesian::X>(x);
			this->_m_startPnt3D.set<Cartesian::Y>(y);
			this->_m_startPnt3D.set<Cartesian::Z>(z);
			this->setPosition(x, y);
			return false;
		}

		bool loadMap(pm::Map3D& _map);

		bool plan();

		void setAgentType(size_t const& _type) { _m_agentType = _type; }
		vector<bgeo::DPoint3D> get3DPath() const { return this->m_path3D; }
		vector<bgeo::DPoint> get2DPath() const { return this->m_path2D; }

		bool saveMsg(std::string fileName);

	private:
		pm::Map3D _m_map;
		pm::GridMap _m_SGridMap;
		pm::GridMap _m_SLocalGridMap;

		bgeo::Graph _m_SGraph;

		vector<bgeo::DPoint3D> m_path3D;
		vector<bgeo::DPoint> m_path2D;

		
		vector<bgeo::DPoint3D> m_aplan_path3D;
		vector<bgeo::DPoint> m_aplan_path2D;

		double gridSize;
		int _m_agentType;
		double _m_crossAbi;
		bgeo::DRing _m_range;

		bgeo::DPoint _m_startPnt;
		bgeo::DPoint3D _m_startPnt3D;

		bool _tGraph2LocalGraph();
		bool _tGrid2LocalGrid();

		bool startPnt2Grid();
		GridIndex findInitGridIndex();
		//pl::APlan _m_aplan;

		bool insidePnt(bgeo::DPoint const &pnt);
	};
}
