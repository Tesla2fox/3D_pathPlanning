#ifndef BGEOMETRY_H
#define BGEOMETRY_H
//#include "boos


//几何head——files
#include "boost/geometry/geometry.hpp"
#include "boost/geometry/geometries/point_xy.hpp"
#include "boost/geometry/geometries/linestring.hpp"
#include "boost/geometry/geometries/linestring.hpp"
#include "boost/geometry/geometries/box.hpp"
#include "boost/geometry/geometries/ring.hpp"
#include "boost/geometry/geometries/polygon.hpp"

//graph  head files
#include "boost/graph/graph_traits.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include "boost/graph/kruskal_min_spanning_tree.hpp"


//std
#include <vector>
#include <map>
#include <iostream>

namespace bg = boost::geometry;
namespace bt = boost;

namespace bgeo {

	/*geometry lib */
	//点
	typedef bg::model::d2::point_xy<double> DPoint;

	typedef bg::model::point<double, 3, bg::cs::cartesian> DPoint3D;

	//线段
	typedef bg::model::segment<DPoint> DSegment;
	//折线段
	typedef bg::model::linestring<DPoint> DLineString;
	//
	typedef bg::model::ring<DPoint, false> DRing;
	

	typedef bg::model::polygon<DPoint, false> DPolygon;


	std::vector<DPoint> segment2VDPoint(DSegment const &seg, double const step);

	DPoint DPointStep(DPoint const & pnt, double const step, DPoint const & pntB);

	//DPoint 


	DSegment v2Segment(std::vector<double> &vx, std::vector<double> &vy);

	DLineString v2LineString(std::vector<double> const &vx, std::vector<double> const &vy);

	DRing v2Ring(std::vector<double> const &vx, std::vector<double> const &vy);

	bool DPointEqual(DPoint const &a, DPoint const &b);

	bool pointEqual(DPoint3D const& a, DPoint3D const& b);

	//enum   vertType { ObVert, WayVert,EdgeObVert,ShoulderVert,NearVert };
	class PointVert
	{
	public:
		PointVert();
		~PointVert();

		DPoint pnt;
		int type;
		std::pair<size_t, size_t> PntIndex;
		
	private:

	};


	///*图库*/
    class VertexProperty { // 图节点中保存的信息
	public:
		VertexProperty();
		VertexProperty(DPoint3D const &pnt, int const & type, std::pair<int, int> const & ind) :
			_pnt(pnt), _type(type), _pntInd(ind)
		{};
        int _type;
        bgeo::DPoint3D  _pnt;
        std::pair<size_t, size_t> _pntInd;
    };

    class EdgeProperty {  // 图边中保存的信息
    public:
        unsigned int index;
        float  weight;
        size_t dir;
    };

    // 图的定义。后面两个参数分别是节点属性和边属性
    ///
    /// bidirectionalS	表示一个既有出边也有入边的有向图
    /// directedS	表示一个只能存取出边的有向图
    /// undirectedS	表示一个无向图
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty> Graph;


    // 节点描述符
    typedef boost::graph_traits<Graph>::vertex_descriptor   VertexDescriptor;
    // 边描述符
    typedef boost::graph_traits<Graph>::edge_descriptor     EdgeDescriptor;

    // 下面是邻接链表的一些遍历器
    typedef boost::graph_traits<Graph>::vertex_iterator     VertexIterator;
    typedef boost::graph_traits<Graph>::edge_iterator      EdgeIterator;
    typedef boost::graph_traits<Graph>::adjacency_iterator  AdjacencyIterator;
    typedef boost::graph_traits<Graph>::out_edge_iterator   OutEdgeIterator;

    //几何到图的转换

    VertexProperty PointVert2PointVert(const PointVert & pntVert);

}

std::ostream &  operator<< (std::ostream &out, bgeo::DPoint & pnt);

std::ostream &  operator<< (std::ostream &out, bgeo::DRing & ring);



#endif // BGEOMETRY_H
