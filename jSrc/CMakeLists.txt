#生成JavaPathPlanning的lib


#添加文件
set(PP_file_list 
	${PROJECT_SOURCE_DIR}/bgeoSrc/bgeometry.h
	${PROJECT_SOURCE_DIR}/bgeoSrc/bgeometry.cpp
	#iostream
	${PROJECT_SOURCE_DIR}/ioSrc/ssconfig.hpp
	${PROJECT_SOURCE_DIR}/ioSrc/Gwrite.hpp
	${PROJECT_SOURCE_DIR}/ioSrc/Gwrite.cpp
	#
	${PROJECT_SOURCE_DIR}/pathPlanningSrc/stadfx.h
	${PROJECT_SOURCE_DIR}/pathPlanningSrc/planningMap.h
	${PROJECT_SOURCE_DIR}/pathPlanningSrc/planningMap.cpp
	${PROJECT_SOURCE_DIR}/pathPlanningSrc/APlan.h
	${PROJECT_SOURCE_DIR}/pathPlanningSrc/APlan.cpp
	
	
	#
	${PROJECT_SOURCE_DIR}/jSrc/cpp3DPathPlanning_Cpp_3DPathPlanning.h
	${PROJECT_SOURCE_DIR}/jSrc/cpp3DPathPlanning_Cpp_3DPathPlanning.cpp
	

	#test_exe
	)
	
include_directories (${PROJECT_SOURCE_DIR}/bgeoSrc)	
include_directories (${PROJECT_SOURCE_DIR}/taskAllocationSrc)
include_directories (${PROJECT_SOURCE_DIR}/pathPlanningSrc)
include_directories(../include)
find_package(Boost)


if(Boost_FOUND)

include_directories(${Boost_INCLUDE_DIRS})

message(${Boost_INCLUDE_DIRS})

endif()


add_library(lib3DPathPlanning  SHARED ${PP_file_list})


#设置输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#设置输出名称
set_target_properties(lib3DPathPlanning PROPERTIES OUTPUT_NAME "lib3DJavaPlanning")

