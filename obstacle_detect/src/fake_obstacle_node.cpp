//
// Created by yangzt on 2021/3/9.
//
#include <ros/ros.h>
#include "ti_mmwave_rospkg/RadarScan.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "fake_obstacle");
    ros::NodeHandle nh;

    ros::Publisher pubObstacle = nh.advertise<ti_mmwave_rospkg::RadarScan>("/ti_mmwave/radar_scan", 1000);
    ti_mmwave_rospkg::RadarScan msgObstacle;

    msgObstacle.header.frame_id = 1;
    msgObstacle.header.stamp = ros::Time::now();

    msgObstacle.point_id = 1;
    msgObstacle.x = 4.0;
    msgObstacle.y = 1.5;
    long int count = 0;

    ros::Rate rate(30);
    while (ros::ok()){
        ROS_INFO("Fake obstacle is publishing %f", msgObstacle.y);
        if (count > 150){
            count = 0;
            msgObstacle.y = 0 - msgObstacle.y;
        }
        ros::spinOnce();
        pubObstacle.publish(msgObstacle);
        rate.sleep();
        count += 1;
    }
    return 0;

}
