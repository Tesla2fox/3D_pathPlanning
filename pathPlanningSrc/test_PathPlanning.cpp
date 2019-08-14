//#include "centralizedMRTA.h"
//#include
#include <iostream>
#include "bgeometry.h"
//#include "centralizedMRTA.h"


#include "planningMap.h"
#include "stadfx.h"
#include "boost/graph/astar_search.hpp"
#include "boost/graph/random.hpp"
#include <random>


// auxiliary types
struct location
{
	float y, x; // lat, long
};
typedef float cost;

struct found_goal {}; // exception for termination

					  // visitor that terminates when we find the goal
template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
public:
	astar_goal_visitor(Vertex goal) : m_goal(goal) {}
	template <class Graph>
	void examine_vertex(Vertex u, Graph& g) {
		if (u == m_goal)
			throw found_goal();
	}
private:
	Vertex m_goal;
};


template <class Graph, class CostType, class LocMap>
class distance_heuristic : public boost::astar_heuristic<Graph, CostType>
{
public:
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	distance_heuristic(LocMap l, Vertex goal)
		: m_location(l), m_goal(goal) {}
	CostType operator()(Vertex u){
		CostType dx = m_location[m_goal]._pnt.get<pm::Cartesian::X>() - m_location[u]._pnt.get<pm::Cartesian::X>();
		CostType dy = m_location[m_goal]._pnt.get<pm::Cartesian::Y>() - m_location[u]._pnt.get<pm::Cartesian::Y>();
		CostType dz = m_location[m_goal]._pnt.get<pm::Cartesian::Z>() - m_location[u]._pnt.get<pm::Cartesian::Z>();
		return ::sqrt(dx * dx + dy * dy + dz * dz);}
private:
	LocMap m_location;
	Vertex m_goal;
};





void main()
{

	double test_data[10] = { 1, 2, 3, 4, -1, 6, 7, 8, 9 };

	vector<double> _data;
	for (size_t i = 0; i < 9; i++)
	{
		cout << " ," << test_data[i] << endl;
		_data.push_back(test_data[i]);
	}

	double test_data_gridSize = 30;
	double test_data_colNum = 3;


	pm::Map3D mainMap;

	mainMap.getOriginData(_data, test_data_gridSize, test_data_colNum);
	
	double gridSize = 5;
	mainMap.setGridSize(5, 5);
	vector<double> _vRobCrossAbi;
	
	_vRobCrossAbi.push_back(1);
	_vRobCrossAbi.push_back(2);
	_vRobCrossAbi.push_back(3);
	_vRobCrossAbi.push_back(4);
	
	mainMap.setCrossAbi(_vRobCrossAbi);
	
	mainMap.createMapGraph();
	auto &graph = mainMap.getGraph(0);

	std::mt19937 gen;

	auto start = boost::random_vertex(graph, gen);
	auto goal = boost::random_vertex(graph, gen);

	cout << " start = " << start << endl;
	cout << " goal = " << goal << endl;


	vector<bgeo::Graph::vertex_descriptor> p(boost::num_vertices(graph));
	vector<cost> d(boost::num_vertices(graph));
	distance_heuristic<bgeo::Graph, cost, bgeo::Graph> 	wtf(graph, goal);

	cout << " dis = " << wtf(42) << endl;
		boost::astar_search
		(graph, start,distance_heuristic<bgeo::Graph, cost, bgeo::Graph>(graph, goal),
			boost::predecessor_map(&p[0]).distance_map(&d[0]).
			visitor(astar_goal_visitor<bgeo::VertexDescriptor>(goal)));



	//try {
	//	// call astar named parameter interface		
	//	boost::astar_search
	//	(graph, start,
	//		distance_heuristic<bgeo::Graph, cost, bgeo::Graph>
	//		(graph, goal),
	//		boost::predecessor_map(&p[0]).distance_map(&d[0]).
	//		visitor(astar_goal_visitor<bgeo::VertexDescriptor>(goal)));
	//}
	//catch (found_goal fg) { // found a path to the goal
	//	list<bgeo::VertexDescriptor> shortest_path;
	//	for (bgeo::VertexDescriptor v = goal;; v = p[v]) {
	//		shortest_path.push_front(v);
	//		if (p[v] == v)
	//			break;
	//	}
	//	//cout << "Shortest path from " << name[start] << " to "
	//	//	<< name[goal] << ": ";
	//	//list<vertex>::iterator spi = shortest_path.begin();
	//	//cout << name[start];
	//	//for (++spi; spi != shortest_path.end(); ++spi)
	//	//	cout << " -> " << name[*spi];
	//	//cout << endl << "Total travel time: " << d[goal] << endl;
	//}
	//boost::astar_search(graph,start, boost::astar_heuristic<bgeo::Graph,double>()
	//)
	//mainMap.map2AGrid();

	//mainMap.addObRing()

//	mainMap.setGridRange(0, 0, 90, 90);
//	bgeo::DPoint pnt1(2, 3);
//	bgeo::DPoint pnt2(3, 4);
//	bgeo::DPoint pnt3(2, 3);
//	bgeo::DPoint pnt4(3, 4);
//
//	std::vector<bgeo::DPoint> vRobPostion;
//
//	vRobPostion.push_back(pnt1);
//	vRobPostion.push_back(pnt2);
//	vRobPostion.push_back(pnt3);
//	vRobPostion.push_back(pnt4);
////	vRobPostion.push_back(pnt1);
//
//
//	bgeo::DRing myRing;
//
//	myRing.push_back(pnt1);
//	myRing.push_back(pnt2);
//	myRing.push_back(pnt3);
//	myRing.push_back(pnt4);
//	myRing.push_back(pnt1);

	//std::vector<bgeo::DRing> vTaskArea;
	//vTaskArea.push_back(myRing);

	//auto taskAllocationRes = ns_ta::cenTaskAllocation(vRobPostion, vTaskArea);
	//for (size_t i = 0; i < taskAllocationRes.size(); i++)
	//{
	//	std::cout << "area" << taskAllocationRes[i] << std::endl;
	//}
	int i;
	std::cin >> i;
}