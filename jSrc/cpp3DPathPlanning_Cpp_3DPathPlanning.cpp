#include "cpp3DPathPlanning_Cpp_3DPathPlanning.h"
#include "planningMap.h"
#include "APlan.h"
#include <time.h>


JNIEXPORT jint JNICALL Java_cpp3DPathPlanning_Cpp_13DPathPlanning_MapUpdate
(JNIEnv* env, jclass, jdoubleArray jHeight, jdouble jGridSize, jint jColNum, jdouble aGridSize, jdouble sGridSize)
{
	jdouble* jdouble_hPtr = env->GetDoubleArrayElements(jHeight, NULL);
	int len_h = env->GetArrayLength(jHeight);
	vector<double> _data;
	for (size_t i = 0; i < len_h; i++)
		_data.push_back(jdouble_hPtr[i]);
	
	double _jGridSize = jGridSize;
	int _jColNum = jColNum;
	pm::ex_mainMap.setOriginData(_data, _jGridSize, _jColNum);

	double _aGridSize = aGridSize;
	double _sGridSize = sGridSize;
	pm::ex_mainMap.setGridSize(_aGridSize, _sGridSize);
	//jdouble* jdouble_xptr = env->GetDoubleArrayElements(jx, NULL);	
	//int len_x = env->GetArrayLength(jx);
	return 2;
}

JNIEXPORT jint JNICALL Java_cpp3DPathPlanning_Cpp_13DPathPlanning_mapSetOb
(JNIEnv* env, jclass, jdoubleArray jx, jdoubleArray jy)
{
	jdouble* jdouble_xptr = env->GetDoubleArrayElements(jx, NULL);
	int len_x = env->GetArrayLength(jx);

	jdouble* jdouble_yptr = env->GetDoubleArrayElements(jy, NULL);
	int len_y = env->GetArrayLength(jy);
	vector<double> vx, vy;
	for (size_t i = 0; i < len_x; i++)
	{
		vx.push_back(jdouble_xptr[i]);
		vy.push_back(jdouble_yptr[i]);
	}
	pm::ex_mainMap.addObRing(vx, vy);
	return -1;
}

JNIEXPORT jint JNICALL Java_cpp3DPathPlanning_Cpp_13DPathPlanning_setRobAbi
(JNIEnv*env , jclass, jdoubleArray jAbi)
{

	jdouble* jdouble_abiPtr = env->GetDoubleArrayElements(jAbi, NULL);
	int len_rob = env->GetArrayLength(jAbi);

	vector<double> _vRobCrossAbi;
	for (size_t i = 0; i < len_rob; i++)
		_vRobCrossAbi.push_back(jdouble_abiPtr[i]);
	pm::ex_mainMap.setCrossAbi(_vRobCrossAbi);
	pm::ex_mainMap.createMapGraph();
	return 1;
}

JNIEXPORT jdoubleArray JNICALL Java_cpp3DPathPlanning_Cpp_13DPathPlanning_MotionPlanning
(JNIEnv* env, jclass, jdouble start_x, jdouble start_y, jdouble target_x, jdouble target_y, jint robType)
{
	std::clock_t startTime, endTime;
	int _robType = robType;
	double _start_x = start_x;
	double _start_y = start_y;
	double _target_x = target_x;
	double _target_y = target_y;
	pl::APlan aplan;
	startTime = clock();

	aplan.loadMap(pm::ex_mainMap);
	aplan.setStartAndTargetPnt(_start_x, _start_y, _target_x, _target_y);
	aplan.AstarPlan();
	auto _path = aplan.get2DPath();

	endTime = clock();

	cout << " total Time " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	jdoubleArray output = env->NewDoubleArray(_path.size() * 2 + 1);
	jboolean isCopy2 = JNI_FALSE;
	jdouble* destArrayElems = env->GetDoubleArrayElements(output, &isCopy2);
	destArrayElems[0] = _path.size();
	for (size_t i = 0; i < _path.size(); i++)
	{
		destArrayElems[2 * i + 1] = _path.at(i).x();
		destArrayElems[2 * i + 2] = _path.at(i).y();
	}
	env->SetDoubleArrayRegion(output, 0, _path.size() * 2 + 1, destArrayElems);
	return output;
}
