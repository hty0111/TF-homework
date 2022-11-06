/*
 * @Description: sun静止 与世界坐标系重合
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-02 14:51:22
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "sun");
    ros::NodeHandle node;
    ros::Publisher marker_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    visualization_msgs::Marker marker;
    marker.header.frame_id = "/world";
    marker.header.stamp = ros::Time();

    marker.ns = "sun";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0;
    marker.pose.orientation.y = 0;
    marker.pose.orientation.z = 0;
    marker.pose.orientation.w = 1;

    marker.scale.x = 1.5;
    marker.scale.y = 1.5;
    marker.scale.z = 1.5;

    marker.color.r = 1;
    marker.color.g = 0;
    marker.color.b = 0;
    marker.color.a = 0.6;

    marker.lifetime = ros::Duration();

    ros::Rate rate(10);
    while (ros::ok())
    {
        marker_pub.publish(marker);
        rate.sleep();
    }

    return 0;
}