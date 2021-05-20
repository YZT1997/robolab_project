//
// Created by yangzt on 2021/3/8.
//
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
// ros
#include "ros/ros.h"
#include "std_msgs/Bool.h"


// openCV
#include "opencv2/opencv.hpp"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"

// Eigen
#include "Eigen/Core"
#include "Eigen/Dense"

// pcl
#include <pcl/io/pcd_io.h>

// TI radar
#include "ti_mmwave_rospkg/RadarScan.h"

// darknet_msgs
#include <darknet_ros_msgs/BoundingBox.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/CheckForObjectsAction.h>
#include <darknet_ros_msgs/ObjectCount.h>

class ObstacleDetect{
private:
    // obstacle
    std::vector<darknet_ros_msgs::BoundingBoxes> obstacleYoloList;
    std::vector<ti_mmwave_rospkg::RadarScan> obstacleRadarList;
    float minRange = 1.0;       // n range of obstacle
    float maxGap = 0;         // max gap of cloud filtering
    bool obstacleState;

    // matrix of Camera
//    cv::Mat img_;
    Eigen::Matrix4f matCamGround_;      // he transform matrix between cam and ground(radar)
    Eigen::Matrix<float,3 , 4> matCam_;
    float heightCam_ = 1.0, heightMan_ = 1.8;

    // ros node, sub and pub
    ros::NodeHandle nh_;

    image_transport::Subscriber subCameraImg_;
    ros::Subscriber subRadar_;
    ros::Subscriber subYolo_;

    ros::Publisher pubObstacle_;
    ros::Publisher pubObstacleState_;

    void cameraImg_cb(const sensor_msgs::ImageConstPtr &msg);
    void radar_cb(const  ti_mmwave_rospkg::RadarScan msg);
    void yolo_cb(const darknet_ros_msgs::BoundingBoxes msg);

public:
    explicit ObstacleDetect(ros::NodeHandle &nh);
    ~ObstacleDetect(){}
    void pubObstacleDetect();
};

ObstacleDetect::ObstacleDetect(ros::NodeHandle &nh) : nh_(nh){
    nh_ = nh;
    pubObstacle_ = nh_.advertise<sensor_msgs::Image>("/obstacle_monitor", 1000);
    pubObstacleState_ = nh_.advertise<std_msgs::Bool>("is_obstacle", 1000);

    image_transport::ImageTransport it_(nh_);
    subCameraImg_ = it_.subscribe("/darknet_ros/detection_image",1, &ObstacleDetect::cameraImg_cb, this);
    subRadar_ = nh_.subscribe<ti_mmwave_rospkg::RadarScan>("/ti_mmwave/radar_scan", 1, &ObstacleDetect::radar_cb, this);
    subYolo_ = nh_.subscribe<darknet_ros_msgs::BoundingBoxes>("/darknet_ros/bounding_boxes", 1, &ObstacleDetect::yolo_cb, this);

    // camera Mat Init
    matCam_ << 394.04628, 0., 333.37834, 0,
            0., 392.58608, 236.22664, 0,
            0., 0., 1., 0;

    matCamGround_ << 0, 1, 0, 0,
                    0, 0, 1, 0,
                    1, 0, 0, 0,
                    0, 0, 0, 1;
}

void ObstacleDetect::cameraImg_cb(const sensor_msgs::ImageConstPtr &msg) {
    try{
        cv_bridge::CvImageConstPtr ptrImg;
        cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;

        // If obstacle, process
        if(!obstacleYoloList.empty() && !obstacleRadarList.empty()){
            Eigen::Vector4f posObstacle;
            Eigen::Vector3f posObstacleCam;
            posObstacle << obstacleRadarList.back().x, - obstacleRadarList.back().y, heightMan_ / 2.0 - heightCam_, 1;

            // Transform the pos in radar to pos in cam
            float z_c = obstacleRadarList.back().x;
            posObstacleCam = (1/z_c) * matCam_ * (matCamGround_ *  posObstacle);

            // Mark the radar pos
            cv::Point ptObjRadar(posObstacleCam(0), posObstacleCam(1));
            cv::circle(img, ptObjRadar, 10, cv::Scalar(0, 255, 255), -1, cv::LINE_8, 0);

            // print the objRange
            float tmpRange = sqrt(pow(obstacleRadarList.back().x, 2) + pow(obstacleRadarList.back().y, 2));
            // Transform to string
            std::ostringstream oss;
            oss<<tmpRange;
            std::string tmpStrRange(oss.str());
            std::string strRange = "d = " + tmpStrRange + " m";

            cv::Point ptRange(obstacleYoloList.back().bounding_boxes.back().xmax,
                         obstacleYoloList.back().bounding_boxes.back().ymax);
            cv::putText(img, strRange, ptRange, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255), 2, 8, 0);

        }
        cv::imshow("Obstacle Monitor", img);
        cv::waitKey(1);


    }
    catch (cv_bridge::Exception& e){
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void ObstacleDetect::radar_cb(const ti_mmwave_rospkg::RadarScan msg) {
    // print

    // filter with range gap
    float objRange = sqrt(msg.x * msg.x + msg.y * msg.y);
    bool tmpStateObstacle = false;
    if (objRange >= minRange){
       if (!obstacleRadarList.empty()){
            int prevSize = obstacleRadarList.size();
            for (int i = 0; i < prevSize; ++i) {
                float tmpGap = sqrt( (msg.x - obstacleRadarList.at(i).x) * (msg.x - obstacleRadarList.at(i).x)
                        + (msg.y - obstacleRadarList.at(i).y) * (msg.y - obstacleRadarList.at(i).y));
                if (tmpGap >= maxGap) tmpStateObstacle = true;
            }
           if (tmpStateObstacle) obstacleRadarList.push_back(msg);
        }
       else obstacleRadarList.push_back(msg);
    } else{

        // limit the size of obstacleRadarList
        while (obstacleRadarList.size() > 10){
            std::vector<ti_mmwave_rospkg::RadarScan>::iterator it = obstacleRadarList.begin();
            obstacleRadarList.erase(it);
        }
//        if (obstacleRadarList.size() == 1) obstacleRadarList.clear();
    }
//    ROS_INFO("obstacle radar num is %d", obstacleRadarList.size());

}

void ObstacleDetect::yolo_cb(const darknet_ros_msgs::BoundingBoxes msg) {
    if (!msg.bounding_boxes.empty())
        obstacleYoloList.push_back(msg);
    else{
        obstacleYoloList.clear();
        return;
    }

    // limit the size of obstacleYoloList
    if (obstacleYoloList.size() > 5) {
        std::vector<darknet_ros_msgs::BoundingBoxes>::iterator it = obstacleYoloList.begin();
        obstacleYoloList.erase(it);
    }

//    ROS_INFO("obstacle yolo num is %d", msg.bounding_boxes.size());
}

void ObstacleDetect::pubObstacleDetect() {

    // publish the state of obstacle
    std_msgs::Bool msgObstacle;
    obstacleState = !obstacleYoloList.empty() || !obstacleRadarList.empty();
    msgObstacle.data = obstacleState;
    pubObstacleState_.publish(msgObstacle);

    // clear?
}

int main(int argc, char **argv){
    ros::init(argc, argv, "obstacle_detect");
    ros::NodeHandle nh;

    ObstacleDetect objDetect(nh);
    ros::Rate rate(20);
    while (ros::ok()){
        ros::spinOnce();
        objDetect.pubObstacleDetect();
        rate.sleep();
    }
    return 0;
}
