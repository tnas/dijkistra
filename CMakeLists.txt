cmake_minimum_required(VERSION 3.5)

project(dijkistra)

add_executable(dijkistra prim/prim2.cpp
                         prim/DHeap.cpp
                         prim/io.cpp
                         my_prim.cpp
                         my_dijkstra.cpp 
                         dijkstra_boost.cpp 
                         kruskal_boost.cpp 
                         union_find_kruskal.cpp 
                         main.cpp)

install(TARGETS dijkistra RUNTIME DESTINATION bin)

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_subdirectory(instances)
add_subdirectory(prim)