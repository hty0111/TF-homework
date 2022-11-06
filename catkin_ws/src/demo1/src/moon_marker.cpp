/*
 * @Description: moon 公转
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-02 14:52:43
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_eigen/tf2_eigen.h>
#include <eigen_conversions/eigen_msg.h>


int main(int argc, char* argv[]) {
    ros::init(argc, argv, "moon");
    ros::NodeHandle node;
    ros::Publisher marker_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    // moon sphere
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/world";
    marker.header.stamp = ros::Time::now();

    marker.ns = "moon";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    marker.color.r = 1;
    marker.color.g = 1;
    marker.color.b = 0;
    marker.color.a = 0.5;

    marker.lifetime = ros::Duration();

    // moon track
    visualization_msgs::Marker track;
    track.header.frame_id = "/world";
    track.header.stamp = ros::Time();

    track.ns = "moon";
    track.id = 1;
    track.type = visualization_msgs::Marker::LINE_STRIP;
    track.action = visualization_msgs::Marker::ADD;

    track.scale.x = 0.5;
    track.scale.y = 0.5;
    track.scale.z = 0.5;

    track.color.r = 1;
    track.color.g = 1;
    track.color.b = 0;
    track.color.a = 0.1;

    track.lifetime = ros::Duration();

    // tf listener
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::TransformStamped trans_sun2earth;

    ros::Rate rate(100);
    while (ros::ok())
    {
        try
        {
            // position of Earth frame in Sun frame
            trans_sun2earth = buffer.lookupTransform("sun", "earth", ros::Time(), ros::Duration(1));
        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("Could not trans_sun2earth earth to sun: %s", ex.what());
            continue;
        }

        // msg to Eigen
        Eigen::Isometry3d T_sun2earth = tf2::transformToEigen(trans_sun2earth.transform);
        Eigen::Isometry3d T_earth2moon = Eigen::Isometry3d::Identity();
        T_earth2moon.pretranslate(Eigen::Vector3d(1, 0, 0));  // radian == 1

        Eigen::Isometry3d T_sun2moon = T_sun2earth * T_earth2moon;  // moon in sun frame

        // Eigen to msg
        geometry_msgs::Pose pose = tf2::toMsg(T_sun2moon);
        marker.pose.position = pose.position;
        marker.pose.orientation = pose.orientation;

        track.points.push_back(pose.position);
        if (track.points.size() > 50)
            track.points.erase(track.points.begin());

        // publish
        marker_pub.publish(marker);
        marker_pub.publish(track);

        rate.sleep();
    }

    return 0;
}