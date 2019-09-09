#include <iostream>
#include "bgeometry.h"
#include "planningMap.h"
#include "stadfx.h"
#include "boost/graph/astar_search.hpp"
#include "boost/graph/random.hpp"
#include <random>
#include "aplan.h"
#include "ssconfig.hpp"


void main()
{
	pm::Map3D mainMap;

	char* fileName = "D:\\VScode\\3D_pathPlanning\\debugMsg\\xx_h_debug.txt";
	sscfg::ConfigFile co_list = sscfg::ConfigFile::load(fileName);
	vector<double> _data;

	double _jGridSize = 1;
	size_t _jColNum;

	co_list.get("_data", _data);
	co_list.get("_jGridSize", _jGridSize);
	co_list.get("_jColNum", _jColNum);

	mainMap.setOriginData(_data, _jGridSize, _jColNum);


	double _aGridSize = 1;
	double _sGridSize = 1;
	co_list.get("_aGridSize", _aGridSize);
	co_list.get("_sGridSize", _sGridSize);

	mainMap.setGridSize(_aGridSize, _sGridSize);


	char* fileName2 = "D:\\VScode\\3D_pathPlanning\\debugMsg\\xx_ob_debug.txt";
	sscfg::ConfigFile co_list2 = sscfg::ConfigFile::load(fileName2);
	vector<double> _vRobCrossAbi;

	size_t _obRingNum;
	co_list2.get("_vRobCrossAbi", _vRobCrossAbi);	
	mainMap.setCrossAbi(_vRobCrossAbi);

	co_list2.get("_obRingNum", _obRingNum);
	
	for (size_t i = 0; i < _obRingNum; i++)
	{
		std::string name_x = "vx";
		std::string name_y = "vy";
		name_x += std::to_string(i);
		name_y += std::to_string(i);
		vector<double> vx, vy;
		co_list2.get(name_x, vx);
		co_list2.get(name_x, vy);
		mainMap.addObRing(vx, vy);
	}
	mainMap.createMapGraph();




	//for (size_t i = 0; i < 9; i++)
	//{
	//	cout << " ," << test_data[i] << endl;
	//	_data.push_back(test_data[i]);
	//}
	//mainMap.setOriginData(_data, _jGridSize, _jColNum);
	




	_vRobCrossAbi.push_back(1);
	_vRobCrossAbi.push_back(2);
	_vRobCrossAbi.push_back(3);
	_vRobCrossAbi.push_back(4);
	
	

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