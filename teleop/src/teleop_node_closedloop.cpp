

/**
 * 该例程将发布chatter话题，消息类型String
 */
 
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include <termio.h>
#include <stdio.h>

int scanKeyboard()
{
int in;
struct termios new_settings;
struct termios stored_settings;
tcgetattr(0,&stored_settings);
new_settings = stored_settings;
new_settings.c_lflag &= (~ICANON);
new_settings.c_cc[VTIME] = 0;
tcgetattr(0,&stored_settings);
new_settings.c_cc[VMIN] = 1;
tcsetattr(0,TCSANOW,&new_settings);
 
in = getchar();
 
tcsetattr(0,TCSANOW,&stored_settings);
return in;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "harvester_control");
  ros::NodeHandle n;
  ros::Publisher speed_pub = n.advertise<std_msgs::Float32>("speed", 1000);
  ros::Publisher turn_pub = n.advertise<std_msgs::Float32>("turn", 1000);
  ros::Publisher stop_pub = n.advertise<std_msgs::Int16>("stop", 1000);
  ros::Rate loop_rate(10);

  int Keyboard=0;
  int up_push_time = 0;
  int down_push_time = 0;
  float target_speed = 0;
  float target_steer_angle =0;




  // while (ros::ok())
  // {
  //   std_msgs::Int16 msg_speed;
  //   std_msgs::Int16 msg_turn;
  //   std_msgs::Int16 msg_stop;
  //     std::cin>>position;
  //     msg_turn.data = position;
  //     turn_pub.publish(msg_turn);
    
  // }


  while (ros::ok())
  {
    Keyboard =scanKeyboard();
    std_msgs::Float32 msg_speed;
    std_msgs::Float32 msg_turn;
    std_msgs::Int16 msg_stop;
    ROS_INFO("%d", Keyboard);

    if (Keyboard == 119)
    {
        target_speed = target_speed + 0.1f;
        msg_speed.data = target_speed;
     speed_pub.publish(msg_speed);
    }
    
     if (Keyboard == 115)
    {
         target_speed = target_speed - 0.1f;
         msg_speed.data = target_speed;
      speed_pub.publish(msg_speed);
    }

    if (Keyboard == 97)
    {
        target_steer_angle = target_steer_angle + 10.f;
        msg_turn.data = target_steer_angle;
      turn_pub.publish(msg_turn);
    }

    if (Keyboard == 100)
    {
        target_steer_angle = target_steer_angle - 10.f;
        msg_turn.data = target_steer_angle;
      turn_pub.publish(msg_turn);
    }

  if (Keyboard == 32)
    {
      msg_stop.data = 1;
      stop_pub.publish(msg_stop);
    }
  
   ROS_INFO("%d", up_push_time);
   ROS_INFO("%d", down_push_time);

    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}
