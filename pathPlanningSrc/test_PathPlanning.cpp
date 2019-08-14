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

#include "aplan.h"


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


		

	//boost::astar_search(graph,start, boost::astar_heuristic<bgeo::Graph,double>())
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