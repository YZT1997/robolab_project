cmake_minimum_required(VERSION 3.0.2)
project(pcl_test)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
        cv_bridge
        image_transport
        pcl_ros
        roscpp
        sensor_msgs
        std_msgs
        )
catkin_package(
        CATKIN_DEPENDS
)

find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
find_package(Eigen3 REQUIRED)
include_directories( ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})

add_executable(pcl_test_node src/depth_to_cloud.cpp)
target_link_libraries(pcl_test_node ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS})
