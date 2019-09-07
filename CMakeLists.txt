cmake_minimum_required(VERSION 3.13)
project(filter)

set(CMAKE_CXX_STANDARD 17)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "C:\\opencvclion\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(filter main.cpp without_opencv.cpp with_opencv.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(filter ${OpenCV_LIBS})