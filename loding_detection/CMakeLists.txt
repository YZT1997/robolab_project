cmake_minimum_required(VERSION 2.8.3)
project(loding_detection)
set(CMAKE_CXX_STANDARD 11)
find_package(catkin REQUIRED COMPONENTS
   roscpp
   message_filters
   sensor_msgs
   cv_bridge
   image_transport
)
catkin_package()

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})
add_executable(loding_detection wavelet.h wavelet.cpp main.cpp DBSCAN.h glcm.h glcm.cpp)
target_link_libraries(loding_detection ${OpenCV_LIBS} ${catkin_LIBRARIES})


