//#include "SPlan.h"
//#include "Gwrite.hpp"
//namespace pl {
//
//	SPlan::SPlan()
//	{
//	}
//	SPlan::~SPlan()
//	{
//	}
//	bool SPlan::setRange(std::vector<double>& vx, std::vector<double>& vy)
//	{
//		this->_m_range.clear();
//		for (size_t i = 0; i < vx.size(); i++)
//			this->_m_range.push_back(bgeo::DPoint(vx[i], vy[i]));
//		return false;
//	}
//
//	bool SPlan::loadMap(pm::Map3D & _map)
//	{
//		/* must after the process of setting robots' abilities */
//		this->_m_map = _map;
//		_m_SGridMap = _map.getSGridMap();
//		this->gridSize = _map.getGridSize(pm::MapType::SearchMap);
//		this->_m_crossAbi = _map.getCrossAbi(this->_m_agentType);
//
//		//Astar算法的地图load
//		this->_m_aplan.loadMap(this->_m_map);
//		this->_m_aplan.setMaxSearchTimes();
//		return false;
//		return false;
//	}
//
//	bool SPlan::plan()
//	{
//		this->m_path2D.clear();
//		this->m_path3D.clear();
//
//		if (!this->startPnt2Grid())
//			return false;
//
//		if (this->_tGrid2LocalGrid())
//		{
//			auto grid_ind = findInitGridIndex();
//			if (grid_ind.first == -1 && grid_ind.second == -1)
//			{
//				cout << " can't find the initial vertex" << endl;
//			}
//			else
//			{
//
//			}
//		}
//		else
//		{
//			cout << " can't convert to the local grid" << endl;
//		}
//		return false;
//	}
//
//	bool SPlan::saveMsg(std::string fileName)
//	{
//		std::ofstream conf_debug(fileName, std::ios::trunc);
//		conf_debug.precision(12);
//		vector<double> vx, vy;
//		for (auto & it : this->m_path2D)
//		{
//			vx.push_back(it.x());
//			vy.push_back(it.y());
//		}
//		writeDebug(conf_debug, "path_x", vx);
//		writeDebug(conf_debug, "path_y", vy);
//
//
//		vx.clear();
//		vy.clear();
//		for (auto &it : this->_m_range)
//		{
//			vx.push_back(it.x());
//			vy.push_back(it.y());
//		}
//		writeDebug(conf_debug, "range_x", vx);
//		writeDebug(conf_debug, "range_y", vy);
//
//		return false;
//		//return false;
//	}
//
//	bool SPlan::_tGraph2LocalGraph()
//	{
//		return false;
//	}
//
//	bool SPlan::_tGrid2LocalGrid()
//	{
//		_m_SLocalGridMap.clear();
//		for (auto & it : this->_m_SGridMap)
//		{
//			bgeo::DPoint pnt;
//			pnt.x(it.second._pnt.get<Cartesian::X>());
//			pnt.y(it.second._pnt.get<Cartesian::Y>());
//			if (this->insidePnt(pnt))
//			{
//				if (it.second._type == pm::VertType::WayVert)
//				{
//					_m_SLocalGridMap.insert(it);
//				}
//			}
//		}
//		if (_m_SLocalGridMap.empty())
//			return false;
//		else
//			return true;
//	}
//	bool SPlan::startPnt2Grid()
//	{
//		auto m_Sindex = this->_m_map.pnt2Index(this->_m_startPnt, pm::MapType::AggregationMap);
//		if ((m_Sindex.first == -1) && (m_Sindex.second == -1))
//			//Target is in the obstacle
//		{
//			cout << "<CPlan> the startPos is out of scope" << endl;
//			return false;
//		}
//		else
//		{
//			if (_m_SGridMap[m_Sindex]._type == pm::VertType::WayVert)
//			{
//				this->setPosition(this->_m_SGridMap[m_Sindex]._pnt.get<Cartesian::X>(),
//					_m_SGridMap[m_Sindex]._pnt.get<Cartesian::Y>(),
//					_m_SGridMap[m_Sindex]._pnt.get<Cartesian::Z>());
//				return true;
//			}
//			else
//			{
//				cout << "<CPlan> the startPos is obstacle" << endl;
//				return false;
//			}
//		}
//	}
//	GridIndex SPlan::findInitGridIndex()
//	{
//		m_aplan_path2D.clear();
//		m_aplan_path3D.clear();
//
//		GridIndex res;
//		res.first = -1;
//		res.second = -1;
//		vector<pair<GridIndex, double>> _v_dis;
//		for (auto &it : this->_m_SLocalGridMap)
//		{
//			auto dis = boost::geometry::distance(_m_startPnt3D, it.second._pnt);
//			pair<GridIndex, double> indAndDis(it.first, dis);
//			_v_dis.push_back(indAndDis);
//		}
//		std::function<bool(pair<GridIndex, double>, pair<GridIndex, double>)> compFunc;
//		compFunc = [=](pair<GridIndex, double> a, pair<GridIndex, double> b)
//		{if (a.second < b.second) { return true; }
//		else { return false; }};
//		std::sort(_v_dis.begin(), _v_dis.end(), compFunc);
//		for (auto & it : _v_dis)
//		{
//			GridIndex &_ind = it.first;
//			double const &_s_x = this->_m_startPnt.x();
//			double const &_s_y = this->_m_startPnt.y();
//			double const &_t_x = this->_m_SLocalGridMap[_ind]._pnt.get<Cartesian::X>();
//			double const &_t_y = this->_m_SLocalGridMap[_ind]._pnt.get<Cartesian::Y>();
//			this->_m_aplan.setStartAndTargetPnt(_s_x, _s_y, _t_x, _t_y);
//			this->_m_aplan.setAgentType(_m_agentType);
//			if (this->_m_aplan.AstarPlan())
//			{
//				m_aplan_path2D = this->_m_aplan.get2DPath();
//				m_aplan_path3D = this->_m_aplan.get3DPath();
//				res = _ind;
//				break;
//			}
//		}
//		return res;
//	}
//
//	bool SPlan::insidePnt(bgeo::DPoint const & pnt)
//	{
//		return boost::geometry::within(pnt, this->_m_range);
//	}
//
//}