# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "cv_bridge;image_transport;roscpp;rospy;sensor_msgs;std_msgs;darknet_ros_msgs;ti_mmwave_rospkg".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lobstacle_detect".split(';') if "-lobstacle_detect" != "" else []
PROJECT_NAME = "obstacle_detect"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
