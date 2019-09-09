#include "APlan.h"



namespace pl {
	ANode::ANode()
	{
	}
	ANode& ANode::operator=(const ANode& a)
	{
		this->disF = a.disF;
		this->disG = a.disG;
		this->disH = a.disH;
		//this->parent = a.parent;
		this->_parentInd = a._parentInd;
		this->_pnt = a._pnt;			
		this->_dir = a._dir;
		this->_pntInd = a._pntInd;
		return *this;
	}
	ANode::ANode(bgeo::DPoint3D pnt, double disg, int dir,
		GridIndex ind, GridIndex par, bgeo::DPoint3D  _target)
	{
		this->_pnt = pnt;
		this->disG = disg;
		this->_dir = dir;
		this->_pntInd = ind;
		this->_parentInd = par;
		this->disH = boost::geometry::distance(pnt, _target);
		this->disF = this->disG + this->disH;
	}

	ANode::~ANode()
	{

	}


	APlan::APlan()
	{

	}

	APlan::~APlan()
	{
	}
	bool APlan::setStartPnt(double const& x, double const& y)
	{
		this->m_startPnt.x(x);
		this->m_startPnt.y(y);
		return false;
	}
	bool APlan::setTargetPnt(double const& x, double const& y)
	{
		this->m_targetPnt.x(x);
		this->m_targetPnt.y(y);
		return false;
	}
	bool APlan::setStartPnt(double const& x, double const& y, double const& z)
	{
		this->m_startPnt3D.set<Cartesian::X>(x);
		this->m_startPnt3D.set<Cartesian::Y>(y);
		this->m_startPnt3D.set<Cartesian::Z>(z);
		//this->setStartPnt(x, y);
		return false;
	}
	bool APlan::setTargetPnt(double const& x, double const& y, double const& z)
	{
		this->m_targetPnt3D.set<Cartesian::X>(x);
		this->m_targetPnt3D.set<Cartesian::Y>(y);
		this->m_targetPnt3D.set<Cartesian::Z>(z);
		//this->setTargetPnt(x, y);
		return false;
	}

	bool APlan::setStartAndTargetPnt(double const& s_x, double const& s_y, double const& t_x, double const& t_y)
	{
		setStartPnt(s_x, s_y);
		setTargetPnt(t_x, t_y);
		if (target2Grid() && start2Grid())
		{
			this->setStartPnt(this->_m_AGridMap[this->m_Sindex]._pnt.get<Cartesian::X>(),
				this->_m_AGridMap[this->m_Sindex]._pnt.get<Cartesian::Y>(),
				this->_m_AGridMap[this->m_Sindex]._pnt.get<Cartesian::Z>());
			this->setTargetPnt(this->_m_AGridMap[this->m_Tindex]._pnt.get<Cartesian::X>(),
				this->_m_AGridMap[this->m_Tindex]._pnt.get<Cartesian::Y>(),
				this->_m_AGridMap[this->m_Tindex]._pnt.get<Cartesian::Z>());
			return true;
		}
		else
			return false;
	}

	bool APlan::loadMap(pm::Map3D& _map)
	{
		this->_m_map = _map;
		_m_AGridMap = _map.getGridMap();

		this->gridSize = _map.getGridSize(MapType::AggregationMap);
		this->_m_crossAbi = _map.getCrossAbi(this->_m_agentType);

		this->setMaxSearchTimes(this->gridSize);
		return false;
	}

	bool APlan::target2Grid()
	{
		this->m_Tindex = this->_m_map.pnt2Index(this->m_targetPnt, pm::MapType::AggregationMap);
		if ((m_Tindex.first == -1) && (m_Tindex.second == -1))
			//Target is in the obstacle
		{
			this->failIndex = -2;
			return false;
		}
		else
		{
			if (_m_AGridMap[m_Tindex]._type == pm::VertType::WayVert)
				return true;
			else
				return false;
		}
	}
	bool APlan::start2Grid()
	{
		this->m_Sindex = this->_m_map.pnt2Index(this->m_startPnt, pm::MapType::AggregationMap);
		if ((m_Sindex.first == -1) && (m_Sindex.second == -1))
			//Target is in the obstacle
		{
			this->failIndex = -2;
			return false;
		}
		else
		{
			if (_m_AGridMap[m_Sindex]._type == pm::VertType::WayVert)
				return true;
			else
				return false;
		}
	}

	bool APlan::AstarPlan()
	{
		this->m_openSet.clear();
		this->m_openList.clear();
		this->m_closeList.clear();
		this->m_closeSet.clear();
		this->m_closeVect.clear();

		//此处验证没有必要
		if ((target2Grid()) && (start2Grid()))
		{
			std::cout << "spnt.x = " << this->m_startPnt.x() << "	spnt.y = " << this->m_startPnt.y() << endl;
			std::cout << "sgrid.x = " << this->_m_AGridMap[m_Sindex]._pnt.get<Cartesian::X>() <<
				" sgrid.y = " << this->_m_AGridMap[m_Sindex]._pnt.get<Cartesian::Y>() << endl;

			std::cout << "tpnt.x = " << this->m_targetPnt.x() << "	tpnt.y = " << this->m_targetPnt.y() << endl;
			std::cout << "tgrid.x = " << this->_m_AGridMap[m_Tindex]._pnt.get<Cartesian::X>() <<
				" tgrid.y = " << this->_m_AGridMap[m_Tindex]._pnt.get<Cartesian::Y>() << endl;

			clock_t aSearch_startTime, aSearch_endTime;
			aSearch_startTime = clock();
			if (AstarSearch())
			{
				aSearch_endTime = clock();
				cout << "aSearchTime  = " << (double)(aSearch_endTime - aSearch_startTime) / CLOCKS_PER_SEC
					<< endl;
				clock_t aFind_startTime, aFind_endTime;
				aFind_startTime = clock();
				if (AstarPathFinder())
				{
					aFind_endTime = clock();
					cout << "aFindTime  = " << (double)(aFind_endTime - aFind_startTime) / CLOCKS_PER_SEC
						<< endl;					
					return true;
				}
				else
				{
					this->failIndex = -4;
					return false;
				}
			}
			this->failIndex = -4;
			return false;
		}
		else
			return false;

		return false;
	}
	bool APlan::AstarSearch()
	{
		auto& grid = this->_m_AGridMap;
		
		ANode sNode(_m_AGridMap[this->m_Sindex]._pnt, 0, AnchorIndex::aicentre,
			m_Sindex, m_Sindex, this->m_targetPnt3D);
		m_openSet.push_back(m_Sindex);
		m_openList.push_back(sNode);


		size_t searchTimes = 0;

		while (!m_openList.empty())
		{
			std::vector<size_t> vdirIndex;
			auto aIndex = m_openList.front()._pntInd;
			auto preDir = m_openList.front()._dir;
			double currDis = m_openList.front().disG;


			// Move the first item of openList to closedList
			m_closeVect.push_back(m_openList.front());
			m_closeList.insert(MNode(m_openList.front()._pntInd, m_openList.front()));
			m_openSet.remove(aIndex);
			m_openList.pop_front();


			auto vIndex = getNeighbor(aIndex, vdirIndex);

			for (size_t dirIndex = 0; dirIndex < vIndex.size(); ++dirIndex)
			{
				auto& it = vIndex[dirIndex];

				bool notInOpenSet = std::find(m_openSet.begin(), m_openSet.end(), it) == m_openSet.end();
				bool notInClosedList = (m_closeList.count(it) == 0);


				double disg = currDis + this->calDistance(aIndex,it);
				if (preDir != vdirIndex.at(dirIndex)) {
					disg += 0.15 * this->gridSize;
				}
				if (notInOpenSet && notInClosedList)
				{
					ANode u_node(grid[it]._pnt, disg, vdirIndex.at(dirIndex), it, aIndex, this->m_targetPnt3D);
					SortedAddToOpenList(u_node);
					//m_openSet.insert(it);
					m_openSet.push_back(it);
				}
				else
				{
					if (!notInOpenSet) {
						auto existed = std::find_if(m_openList.begin(), m_openList.end(), [&](const ANode & xx) {
							return xx._pntInd.first == it.first &&
								xx._pntInd.second == it.second;
							});
						if (disg < existed->disG) {
							m_openList.erase(existed);
							ANode u_node(grid[it]._pnt, disg, vdirIndex.at(dirIndex), it, aIndex, this->m_targetPnt3D);
							SortedAddToOpenList(u_node);
						}
					}
					else {
						auto existed = m_closeList.find(it);
						if (disg < existed->second.disG) {
							m_closeList.erase(existed);
							ANode u_node(grid[it]._pnt, disg, vdirIndex.at(dirIndex), it, aIndex, this->m_targetPnt3D);
							SortedAddToOpenList(u_node);
							m_openSet.push_back(it);
						}
					}
				}
			}

			searchTimes++;
			if (searchTimes > this->_m_maxSearhTimes)
			{
				//qDebug()<<"over the maxSearchTimes";
				std::cout << "over the maxmaxSearchTimes" << std::endl;
				goto Fcase;
			}
		}
	Fcase:
		return false;
	}

	bool APlan::AstarPathFinder()
	{
		m_path3D.clear();
		m_path2D.clear();
		std::stack<bgeo::DPoint3D> sDPoint;
		std::stack<int> sDirIndex;
		auto u_node = m_closeList[m_Tindex];
		sDPoint.push(u_node._pnt);
		sDirIndex.push(u_node._dir);

		//		qDebug() << "u_first= " << u_node.vertPnt.PntIndex.first << " u_second " << u_node.vertPnt.PntIndex.second;
		//		qDebug() << " u_x " << u_node.vertPnt.pnt.x() << " u_y " << u_node.vertPnt.pnt.y();

		auto spnt = this->_m_AGridMap[m_Sindex]._pnt;

		size_t successIndex = 0;
		do
		{
			successIndex++;
			if (successIndex > this->_m_maxSearhTimes)
			{
				return false;
			}
			//qDebug() << "u_first= " << u_node.vertPnt.PntIndex.first<< " u_second " << u_node.vertPnt.PntIndex.second;
			//qDebug() << "p_first= " << u_node.parent.first << " p_second " << u_node.parent.second;
			//qDebug() << "s_first" << m_Sindex.first << "s_second" << m_Sindex.second;
			u_node = m_closeList[u_node._parentInd];
			sDPoint.push(u_node._pnt);
			sDirIndex.push(u_node._dir);
		} while (!bgeo::pointEqual(u_node._pnt,spnt));


		std::vector<bgeo::DPoint3D> vpathTem;
		std::vector<int> vdirIndex;
		do
		{
			vpathTem.push_back(sDPoint.top());
			sDPoint.pop();
			vdirIndex.push_back(sDirIndex.top());
			sDirIndex.pop();
		} while (!sDPoint.empty());

		//m_path.push_back(m_startPnt);
		//std::list<bgeo::DPoint> l_path;		
		//m_path.push_back(m_startPnt);
		
		for (size_t i = 1; i < (vdirIndex.size() - 1); i++)
		{
			if (vdirIndex.at(i) != vdirIndex.at(i + 1))
				m_path3D.push_back(vpathTem.at(i));
		}
		m_path3D.push_back(vpathTem.back());
		for (auto& it : this->m_path3D)
			this->m_path2D.push_back(bgeo::DPoint(it.get<Cartesian::X>(), it.get<Cartesian::Y>()));
		
		return true;
	}

	void APlan::SortedAddToOpenList(ANode const& mNode)
	{
		if (!m_openList.empty())
		{
			if (mNode.disF < m_openList.front().disF)
			{
				m_openList.push_front(mNode);
				return;
			}
			if (mNode.disF >= m_openList.back().disF)
			{
				m_openList.push_back(mNode);
				return;
			}
			for (auto it = m_openList.begin(); it != m_openList.end(); it++)
			{
				if (mNode.disF < it->disF)
				{
					auto p = it;
					//p--;
					m_openList.insert(p, mNode);
					return;
				}
			}
		}
		m_openList.push_back(mNode);
	}

	std::vector<GridIndex> APlan::getNeighbor(GridIndex const& mindex, std::vector<size_t> & vdirIndex)
	{
		auto& grid = this->_m_AGridMap;
		auto m_z = grid[mindex]._pnt.get<Cartesian::Z>();
		vdirIndex.clear();
		std::vector<GridIndex> vIndex;
		size_t dirIndex = 0;
		for (auto i = mindex.first - 1; i <= (mindex.first + 1); i++)
		{
			for (auto j = mindex.second - 1; j <= (mindex.second + 1); j++)
			{

				if (grid.count(GridIndex(i, j)) == 1)
				{
					if ((i == mindex.first) && (j == mindex.second))
					{
					}
					else
					{
						if (grid[GridIndex(i, j)]._type == pm::VertType::WayVert)
						{
							if (grid[GridIndex(i, j)]._pnt.get<Cartesian::Z>() <= m_z + this->_m_crossAbi)
							{
								vdirIndex.push_back(dirIndex);
								vIndex.push_back(GridIndex(i, j));
							}
						}
					}
				}
				dirIndex++;
			}
		}
		return vIndex;
	}

	double APlan::calDisH(ANode const& a_node) const
	{
		return boost::geometry::distance(this->m_targetPnt3D, a_node._pnt);
	}

	double calDisHInPnt(bgeo::DPoint3D const& pnt, bgeo::DPoint3D const& _target)
	{
			return boost::geometry::distance(pnt, _target);
	}

}
