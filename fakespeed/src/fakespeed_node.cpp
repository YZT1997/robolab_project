#include <ros/publisher.h>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include <iostream>
#include <sstream>
#include <string>
//using namespace std;

ros::Publisher *publisher1 = nullptr;
ros::Publisher *publisher2 = nullptr;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "fakeSpeed");
	ros::NodeHandle n;
    int target_speed = 0;
	ros::Publisher chatter_pub = n.advertise<std_msgs::Bool>("is_obstacle", 1000);
	ros::Publisher chatter_pub2 = n.advertise<std_msgs::Float32>("car_speed",1000);
	ros::Publisher chatter_pub3 = n.advertise<std_msgs::Float32>("motor_current", 1000);
	ros::Publisher chatter_pub4 = n.advertise<std_msgs::Int16>("motor_speed", 1000);
	publisher1 = &chatter_pub4;
	std::cout<<publisher1<<std::endl;

	ros::Rate loop_rate(10);

	std_msgs::Bool msg_obstacle;
	std_msgs::Float32 msg_speed;
	std_msgs::Float32 msg_current;
	std_msgs::Int16 msg_target_speed;
	n.getParam("target_speed", target_speed);

	int count = 0;
    bool obstacle_state = false;
	while (ros::ok() && count < 10)
	{
		/**
		 * 向 Topic: chatter 发送消息, 发送频率为10Hz（1秒发10次）；消息池最大容量2000。
		 */
        msg_target_speed.data = target_speed;
        publisher1->publish(msg_target_speed);
//        publisher2->publish(msg_target_speed);
		loop_rate.sleep();
		// ++count;
		count  = count + 1;
//        ROS_INFO_STREAM(target_speed);
        usleep(50000);
	}
//	delete publisher1;
    std::cout<<publisher1<<std::endl;
	ROS_INFO_STREAM("Speed end");
	return 0;

}
