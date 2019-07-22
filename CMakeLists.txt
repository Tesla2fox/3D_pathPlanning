
#最小版本的要求
cmake_minimum_required(VERSION 3.0)

#项目名称
project(PathPlanning3DSynthesis)

message("PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})
#添加外部dll
#add_library(libGPS SHARED IMPORTED)
#set_target_properties(libGPS PROPERTIES
#	IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/libgps2local.dll 
#	IMPORTED_IMPLIB   ${PROJECT_SOURCE_DIR}/lib/libgps2local.lib 
#)
#测试主函数的文件夹
#add_subdirectory(src)

#任务分配
#add_subdirectory(taskAllocationSrc)
#GGQ和鲁赛的路径规划
add_subdirectory(pathPlanningSrc)
#生成anylogic的dll
#add_subdirectory(anyLogicLibSrc)