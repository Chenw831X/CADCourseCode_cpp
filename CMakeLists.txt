cmake_minimum_required(VERSION 3.9)
project(CADCourseCode_cpp LANGUAGES CXX)

include_directories(/usr/local/include)

include_directories(
    src/HalfEdgeDS
    src/EulerOp
    src/Sweep
)

add_executable(CADCourseCode
    src/main.cpp
    src/HalfEdgeDS/HalfEdgeDS.cpp
    src/EulerOp/EulerOp.cpp
    src/Sweep/Sweep.cpp
)