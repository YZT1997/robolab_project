//
// Created by yangzt on 2020/11/8.
//
#include "actionlib/server/simple_action_server.h"
#include "test_action/demoAction.h"

typedef actionlib::SimpleActionServer<test_action::demoAction> Server;

void execute(const test_action::demoGoalConstPtr& goal, Server* as){
    ros::Rate rate(1);
    test_action::demoFeedback feedback;
    ROS_INFO("Disk %d is working", goal->numGoal);
    for (int i = 0; i < 100; ++i) {
        feedback.complete_percent = i;
        as->publishFeedback(feedback);
        rate.sleep();
    }
    ROS_INFO("Dish %d finish working.", goal->numGoal);
    as->setSucceeded();
}

int main(int argc, char** argv){
    ros::init(argc, argv, "do_dishes_server");
    ros::NodeHandle n;
    Server server(n, "do_dishes", boost::bind(&execute, _1, &server), false);
    server.start();
    ROS_INFO("server is start");
    ros::spin();
    return 0;

}