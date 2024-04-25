cmake_minimum_required(VERSION 3.5.0)
project(DataStructureSortFunctions)

add_library(SortLibrary student.cpp)

add_executable(DataStructureSortFunctions main.cpp)

target_link_libraries(DataStructureSortFunctions PRIVATE SortLibrary) 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/students.txt ${CMAKE_CURRENT_BINARY_DIR}/students.txt COPYONLY)