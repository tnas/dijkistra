project(dijkistra)

add_executable(dijkistra my_prim.cpp my_dijkstra.cpp dijkstra_boost.cpp kruskal_boost.cpp union_find_kruskal.cpp main.cpp)

install(TARGETS dijkistra RUNTIME DESTINATION bin)

list(APPEND CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -03")

set(CMAKE_C_COMPILER "/usr/bin/gcc")

add_subdirectory(instances)
add_subdirectory(prim)