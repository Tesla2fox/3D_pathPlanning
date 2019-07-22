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
		bgeo::DPoint3D pnt;
		int type;
		std::pair<size_t, size_t> PntIndex;
	private:

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
		
		void map2AGrid();
		//void 

	private:

		//每一个搜索栅格的距离
		double gridStep = 2;
		//每一个集结栅格的距离
		double AgridStep = 0.5;

		
		//
		vector<double> _m_vCrossAbi;
		

		bgeo::DPoint mWsPoint1;
		bgeo::DPoint mWsPoint3;


		GridMap _m_AGridMap;
		AllGridMap _m_a_allGridMap;


		//最大行
		size_t _m_maxRow;
		//最大列
		size_t _m_maxCol;



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

