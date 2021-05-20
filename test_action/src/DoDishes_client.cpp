//
// Created by yangzt on 2020/11/8.
//
#include "actionlib/client/simple_action_client.h"
#include "test_action/demoAction.h"

typedef actionlib::SimpleActionClient<test_action::demoAction> Client;

// call this function when action is finished
void doneCb(const actionlib::SimpleClientGoalState& state, const test_action::demoResultConstPtr& client){
    ROS_INFO("Yay! The dishes are now clean");
    ros::shutdown();
}

void activeCb(){
    ROS_INFO("goal went active");
}

void feedbackCb(const test_action::demoFeedbackConstPtr& feedback){
    ROS_INFO("percent_complete: %f",feedback->complete_percent);
}
int main(int argc, char** argv)
{
   ros::init(argc, argv, "do_dishes_client");
   Client client("do_dishes", true); // true -> don't need ros::spin()

   ROS_INFO("Waiting for action server to start");
   client.waitForServer();
   ROS_INFO("Action server started, sending goals");

   test_action::demoGoal goal;
   goal.numGoal = 1;

   client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
   ros::spin();

   return 0;
 }
