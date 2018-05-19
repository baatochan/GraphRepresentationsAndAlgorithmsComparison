# cmake_minimum_required(VERSION <specify CMake version here>)
project(GraphRepresentationsAndAlgorithmsComparison)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif (CMAKE_BUILD_TYPE MATCHES RELEASE)

set(SOURCE_FILES main.cpp Program.cpp Graph.cpp DirectedGraph.cpp UndirectedGraph.cpp)
add_executable(GraphRepresentationsAndAlgorithmsComparison ${SOURCE_FILES})
