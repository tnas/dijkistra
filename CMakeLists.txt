cmake_minimum_required(VERSION 3.5)

set(CMAKE_VERBOSE_MAKEFILE OFF)

if (WIN32)
	message("-- Windows Operational System")
	set(MinGW_HOME "C:/MinGW")
	set(Boost_MinGW_ROOT "${MinGW_HOME}/msys/1.0/home/140688330213/boost_1_68_0")
	set(Boost_INCLUDE_DIR ${Boost_MinGW_ROOT})
	set(CMAKE_CXX_COMPILER "${MinGW_HOME}/bin/g++.exe")
elseif (LINUX)
	message("-- Linux Operational System")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

project(dijkistra)

add_executable(dijkistra main.cpp
                         my_dijkstra.cpp 
                         dijkstra_boost.cpp 
                         kruskal_boost.cpp 
                         union_find_kruskal.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(dijkistra ${Boost_LIBRARIES})
  
install(TARGETS dijkistra RUNTIME DESTINATION bin)

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

add_subdirectory(instances)
