
#include "planningMap.h"



namespace pm {
	Map3D::Map3D()
	{
		std::cout << "map begin to init" << endl;
	}
	Map3D::~Map3D()
	{
	}
	void Map3D::setGridRange(double const& min_x, double const min_y, double const& max_x, double const& max_y)
	{
		this->mWsPoint1.x(min_x);
		this->mWsPoint1.y(min_y);
		this->mWsPoint3.x(max_x);
		this->mWsPoint3.y(max_y);
	}

	void Map3D::setGridSize(double const& aSize, double const& sSize)
	{
		//如果不能整除怎么办？
			this->AgridStep = aSize; 
			this->gridStep = sSize;
	}

	bool Map3D::getOriginData(vector<double> const& _data, double const& _originGridSize, size_t const& _originColSize)
	{
		this->_m_originData = _data;
		this->_m_originGridSize = _originGridSize;
		
		this->_m_originColSize = _originColSize;
		this->_m_originRowSize = _data.size() / _originColSize;
		
		
		this->_m_vOriginData.clear();
		_m_vOriginData.assign(_m_originRowSize, std::vector<double>());
			
		for (size_t i = 0; i < _data.size(); i++)
		{
			size_t row = std::floor(i / _m_originColSize);
			//size_t col = i % _m_originColSize;
			//cout << "row = " << row << endl;
			_m_vOriginData[row].push_back(_data[i]);
		}



		// set range
		this->mWsPoint1.set<0>(0);
		this->mWsPoint1.set<1>(0);

		this->mWsPoint3.x(_originGridSize* _m_originColSize);
		this->mWsPoint3.y(_originGridSize* _m_originRowSize);
		return true;
	}

	void Map3D::addObRing(std::vector<double> const& vx, std::vector<double> const& vy)
	{
		auto ringUnit = bgeo::v2Ring(vx, vy);
		_m_vDRing.push_back(ringUnit);
	}

	void Map3D::map2AGrid()
	{


		auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
		auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

		//the max col and the max row
		this->_m_maxRow = ceil(bais_x / this->gridStep);
		this->_m_maxCol = ceil(bais_y / this->gridStep);

		//car1
		for (size_t i = 0; i < _m_maxCol; i++)
		{
			bgeo::DPoint3D pnt3D;
			pnt3D.set<Cartesian::X>(this->AgridStep * i + this->mWsPoint1.x() + this->AgridStep / 2);
			for (size_t j = 0; j < _m_maxRow; j++)
			{
				pnt3D.set<Cartesian::Y>(this->AgridStep * j + this->mWsPoint1.y() + this->AgridStep / 2);
				size_t pntType = VertType::WayVert;

				for (auto & it : this->_m_vDRing)
				{
					bgeo::DPoint pnt(pnt3D.get<Cartesian::X>(),pnt3D.get<Cartesian::Y>());
					auto _BWithIn = bg::within(pnt, it);
					if (_BWithIn)
					{
						pntType = VertType::Obstacle;
						goto insertPnt;
					}
				}


			insertPnt:

				GridIndex pntInd(i, j);
				double _z = this->getHeight(pnt3D.get<Cartesian::X>(), pnt3D.get<Cartesian::Y>());
				pnt3D.set<Cartesian::Z>(_z);
				PointVert3D pntVert3d;
				pntVert3d.pnt = pnt3D;
				pntVert3d.type = pntType;
				pntVert3d.PntIndex = GridIndex(i, j);
				_m_AGridMap.insert(GridMapUnit(pntVert3d.PntIndex, pntVert3d));
				
			}
		}
		

	}

	double Map3D::getHeight(double const& x, double const& y) const
	{
		return 0.0;
	}



	PointVert3D::PointVert3D()
	{
	}

	PointVert3D::~PointVert3D()
	{
	}

}