cmake_minimum_required(VERSION 3.10)

project(opencv_practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/opencv-4.9.0/include/opencv4)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/opencv-4.9.0/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/capture_start)

add_subdirectory(${PROJECT_SOURCE_DIR}/intersection)
