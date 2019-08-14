#pragma once
#include "stadfx.h"
#include "bgeometry.h"

namespace pm {

	enum MapType { SearchMap, AggregationMap };
	enum AgentType { car1, car2, car3 };
	enum Cartesian {X,Y,Z};
	enum VertType {WayVert,Obstacle};
	typedef std::pair<int, int> GridIndex;

	class PointVert3D
	{
	public:
		PointVert3D();
		~PointVert3D();
		bgeo::DPoint3D _pnt;
		int _type;
		std::pair<size_t, size_t> _pntInd;
	};

	typedef std::map <std::pair<int, int>, PointVert3D> GridMap;
	typedef std::pair <std::pair<int, int>, PointVert3D> GridMapUnit;
	typedef std::map<size_t, GridMap> AllGridMap;

	
	class Map3D
	{
	public:
		Map3D();
		~Map3D();

		void setGridRange(double const& min_x, double const min_y, double const& max_x, double const& max_y);
		void setGridSize(double const& aSize, double const& sSize);
		bool getOriginData(vector<double> const& _data, double const& _originGridSize, size_t const& _originColSize);
		void setCrossAbi(vector<double> const& _v_crossAbi) {
			this->_m_vCrossAbi = _v_crossAbi
				;
		}

		void addObRing(bgeo::DRing const& obring) { _m_vDRing.push_back(obring); }
		void addObRing(std::vector<double> const& vx, std::vector<double> const& vy);

		bool createMapGraph();
		//void 
		bgeo::Graph& getGraph(size_t const& ind) { return this->_m_vAllGraph[ind]; }
		GridMap& getGridMap() { return this->_m_AGridMap; }
	

		/// debug function 
		bool empty(int const& t);


		// for planning function 
		GridIndex pnt2Index(bgeo::DPoint const& pnt, size_t const& _type);
				
		double getGridSize(size_t const& _type) const {
			if (_type == MapType::AggregationMap)
				return this->AgridStep;
			else
				return this->SgridStep;
		};
		double getCrossAbi(size_t const& ind) const
		{
			return this->_m_vCrossAbi[ind];
		}

	private:


		void map2AGrid();
		void grid2Graph();


		std::vector<GridIndex> getSearchNeighbor(GridIndex const &mindex);

		//每一个搜索栅格的距离
		double SgridStep = 2;
		//每一个集结栅格的距离
		double AgridStep = 0.5;

		
		//
		vector<double> _m_vCrossAbi;
		vector<bgeo::Graph> _m_vAllGraph;
		vector<map<GridIndex, int>> _m_vAllMap2Graph;
		vector<map<int, GridIndex>> _m_vAllGraph2Map;

		bgeo::DPoint mWsPoint1;
		bgeo::DPoint mWsPoint3;


		GridMap _m_AGridMap;
		AllGridMap _m_a_allGridMap;


		//Amap 最大行
		size_t _m_a_maxRow;
		//Amap 最大列
		size_t _m_a_maxCol;



		//Amap 最大行
		size_t _m_s_maxRow;
		//Amap 最大列
		size_t _m_s_maxCol;


		//障碍物的信息
		std::vector<bgeo::DRing> _m_vDRing; 


		// anyLogic 输入的数据
		std::vector<double> _m_originData;
		double _m_originGridSize;
		size_t _m_originColSize;
		size_t _m_originRowSize;
		std::vector<vector<double>> _m_vOriginData;
		double getHeight(double const& x, double const &y) const;

	};

	class Map2D
	{
	public:
		Map2D();
		~Map2D();
	private:

	};

}

