project(dijkistra)

add_executable(dijkistra main.cpp)

install(TARGETS dijkistra RUNTIME DESTINATION bin)

list(APPEND CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -03")

set(CMAKE_C_COMPILER "/usr/bin/gcc")

add_subdirectory(instances)