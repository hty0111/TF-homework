/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-03 19:46:01
 */

#include <ros/ros.h>
#include <std_msgs/Float32.h>


void float_callback(const std_msgs::Float32::ConstPtr & msg)
{
    ROS_WARN("Received number: %.2f", msg->data);
}


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle node;
    ros::Subscriber subscriber = node.subscribe<std_msgs::Float32>("float_topic", 5, float_callback);

    while (ros::ok())
    {
        ros::spinOnce();
        ros::Duration(2).sleep();
    }

    return 0;
}
