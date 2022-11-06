/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-03 19:45:50
 */


#include <ros/ros.h>
#include <std_msgs/Float32.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle node;
    ros::Publisher publisher = node.advertise<std_msgs::Float32>("float_topic", 10);

    float number = 0.0;

    ros::Rate rate(2);
    while (ros::ok())
    {
        std_msgs::Float32 msg;
        msg.data = number;
        publisher.publish(msg);

        ROS_INFO("Published number: %.2f", number);

        number += 0.5;
        rate.sleep();
    }

    return 0;
}