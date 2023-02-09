#include "ros/ros.h" // headers for ROS functionalities.
#include "turtlesim/Pose.h" //To use the message turtlsim/Pose
#include "geometry_msgs/Twist.h" // To use Twist message
// initialise a variable to store the value of the turtle position in the x-axis
float turtle_pose_x = 0;

float desired_x_dist = 0; // initialise the desired x distance

// define pose_callback function
void pose_callback(const turtlesim::Pose::ConstPtr& pose_msg)
{

// read the turtle x position that we need to control
turtle_pose_x = pose_msg->x;
// Print log message data on the screen
ROS_INFO("turtle_pose_x: [%f]", pose_msg->x);
}
int main(int argc, char **argv) // C++ main function
{ // main start
ros::init(argc, argv, "my_turtle_pose_control"); // initialize the node
ros::NodeHandle nh; // create a NodeHandle of name nh
ROS_INFO("my_turtle_pose_control node has been started"); //Logging the information of node

nh.getParam("desired_x_distance_in_m", desired_x_dist);

//Creates a subscriber for /turtle1/pose via pose_callback
ros::Subscriber sub_pose_data = nh.subscribe("/turtle1/pose", 1000, pose_callback);
//Creates a publisher to publish to the /turtle1/cmd_vel topic
ros::Publisher pub_vel_cmd = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
//Sets the loop to publish at a rate of 10Hz
ros::Rate loop_rate(10);
while (ros::ok()) // Loop
{
//Declares a message of name "msg_vel_cmd" and type "geometry_msgs/Twist"
geometry_msgs::Twist msg_vel_cmd;
//msg_vel_cmd.linear.x = 0.5;
//msg_vel_cmd.angular.z = 0.0;
//checking the robot distance is greater than the commanded distance
if(turtle_pose_x < desired_x_dist)
{
msg_vel_cmd.linear.x = 1.0; //turtle linear velocity in x-axis (horizontal)
msg_vel_cmd.angular.z = 0.0;
}
else
{
msg_vel_cmd.linear.x = 0.0; //turtle linear velocity in x-axis (horizontal)
msg_vel_cmd.angular.z = 0.0;
}
// Print command velocity sent to turtle on the screen
ROS_INFO("turtle linear command velocity: [%f]", msg_vel_cmd.linear.x);
pub_vel_cmd.publish(msg_vel_cmd); //Publish the message
/**
* It allows calling the callback functions and publishing at the required rate as well
.
*/
ros::spinOnce();
// Delays until it is time to send another message

loop_rate.sleep();
}
return 0; // Program termination status
} // main end