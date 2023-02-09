#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "draw_circle_cw");
    ros::NodeHandle nh;
    ROS_INFO("draw_circle_cw node has been started");

    ros::Publisher pub_vel_cmd = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        geometry_msgs::Twist msg_vel_cmd;

        msg_vel_cmd.linear.x = -1.0;
        msg_vel_cmd.angular.z = -2.0;

        pub_vel_cmd.publish(msg_vel_cmd);

        loop_rate.sleep();
    }

    return 0;
}