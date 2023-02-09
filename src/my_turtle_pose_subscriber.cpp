#include "ros/ros.h" // headers for ROS functionalities.
#include "turtlesim/Pose.h" // To use the message turtlesim/Pose
// define pose_callback function
void pose_callback(const turtlesim::Pose::ConstPtr& pose_msg)
{
    // Print log message data on the screen
    ROS_INFO("x: [%f], y: [%f]", pose_msg->x, pose_msg->y, pose_msg->theta);
    ROS_INFO("x: [%f], y: [%f]", pose_msg->linear_velocity, pose_msg->linear_velocity);
}

int main(int argc, char **argv) //C++ main function
{ // Main start
 ros::init(argc, argv, "my_turtle_pose_subscriber"); // initialize the node
 ros::NodeHandle nh; // create a NodeHandle of name nh
 ROS_INFO("my_turtle_pose_subscriber node has been started"); // Logging the information of node

 //Creates subscriber of name sub_pose_data, and ask it to subscribe
 //the /turtle1/pose topic and recieve data via function called pose_callback, with a queue size of 100
 ros::Subscriber sub_pose_data = nh.subscribe("/turtle1/pose", 1000, pose_callback);
 /**
  * ros::spin() will enter a loop, pumping callbacks, waiting for a message to arrive
  * When a message arrives, the pose_callback() function is called
  * ros::spin() will exit when Ctrl-C is pressed, or the node is shut down by the master
 */
ros::spin();

return 0;
}