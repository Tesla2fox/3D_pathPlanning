#include <iostream>
#include "bgeometry.h"
#include "planningMap.h"
#include "stadfx.h"
#include "boost/graph/astar_search.hpp"
#include "boost/graph/random.hpp"
#include <random>
#include "aplan.h"
#include "splan.h"
#include "ssconfig.hpp"
#include "Gwrite.hpp"


#define _DEBUGMSG 1

int main()
{

	cout << "<cPlan> begin to test" << endl;
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
	cout << _vRobCrossAbi << endl;
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
		co_list2.get(name_y, vy);
		mainMap.addObRing(vx, vy);
	}
	mainMap.createMapGraph();

#ifdef _DEBUGMSG
	mainMap.writeGrid("D:\\VScode\\3D_pathPlanning\\debugMsg\\grid.dat");
#endif // DEBUGMSG
	


	char* aplan_fileName = "D:\\VScode\\3D_pathPlanning\\debugMsg\\xx_plan_debug.txt";
	sscfg::ConfigFile aplanCfg = sscfg::ConfigFile::load(aplan_fileName);



	double _start_x = 1;
	double _start_y = 1;
	double _target_x = 500;
	double _target_y = 500;
	size_t _robType;

	aplanCfg.get("_start_x", _start_x);
	aplanCfg.get("_start_y", _start_y);
	aplanCfg.get("_target_x", _target_x);
	aplanCfg.get("_target_y", _target_y);
	aplanCfg.get("_robType", _robType);



	pl::APlan a_plan;
	a_plan.setAgentType(_robType);
	a_plan.loadMap(mainMap);
	a_plan.setStartAndTargetPnt(_start_x, _start_y, _target_x, _target_y);
	a_plan.setMaxSearchTimes();
	std::clock_t a_startTime, a_endTime;
	a_startTime = clock();
	a_plan.AstarPlan();
	a_endTime = clock();
	cout << "cPlan the planning Time is  " << (double)(a_endTime - a_startTime) / CLOCKS_PER_SEC << "s" << endl;

#ifdef _DEBUGMSG
	a_plan.saveMsg("D:\\VScode\\3D_pathPlanning\\debugMsg\\a_plan.dat");
#endif // DEBUGMSG


	
	/*
	测试coverage path planning 
	*/

	cout << "begin the s_plan" << endl;
	pl::SPlan s_plan;

	s_plan.setPosition(20, 20);
	s_plan.setAgentType(0);
	s_plan.loadMap(mainMap);
	cout << "begin the s_plan 2" << endl;
	bgeo::DRing ring;
	ring.push_back(bgeo::DPoint(0, 0));
	ring.push_back(bgeo::DPoint(100, 0));
	ring.push_back(bgeo::DPoint(0, 100));
	ring.push_back(bgeo::DPoint(0, 0));	
	s_plan.setRange(ring);
	s_plan.plan();
	
	size_t i_x;
	std::cin >> i_x;
	return 1;



//	s_plan.setRange()

	//_vRobCrossAbi.push_back(1);
	//_vRobCrossAbi.push_back(2);
	//_vRobCrossAbi.push_back(3);
	//_vRobCrossAbi.push_back(4);
	//
	//

	//auto &graph = mainMap.getGraph(0);

	//std::mt19937 gen;

	//auto start = boost::random_vertex(graph, gen);
	//auto goal = boost::random_vertex(graph, gen);

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