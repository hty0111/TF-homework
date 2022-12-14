/*
 * @Description: 发布tf坐标；不使用极坐标
 * @version: v2.0
 * @Author: HTY
 * @Date: 2022-11-02 17:03:00
 */

#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/TransformStamped.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "tf_broadcaster");
    ros::NodeHandle node;

    static tf2_ros::TransformBroadcaster broadcaster;   // static variable, cannot be destroyed

    double T_revolution = 365.0 / 10, T_rotation = 1.0 / 10;   // T(s)

    ros::Rate rate(100);
    while (ros::ok())
    {
        /*
        // sun to earth
        geometry_msgs::TransformStamped trans_sun2earth;
        trans_sun2earth.header.stamp = ros::Time();
        trans_sun2earth.header.frame_id = "sun";
        trans_sun2earth.child_frame_id = "earth";

        // origin of earth frame, i.e. revolution
        trans_sun2earth.transform.translation.x = 3 * cos(ros::Time::now().toSec() / T_revolution);
        trans_sun2earth.transform.translation.y = 3 * sin(ros::Time::now().toSec() / T_revolution);
        trans_sun2earth.transform.translation.z = 0.0;
         
        // quaternion of earth frame, i.e. rotation
        tf2::Quaternion q_earth_axis;   // an inclined axis
        q_earth_axis.setRPY(0, -M_PI_4, 0);
        tf2::Quaternion q_earth_rotate; // self rotation
        q_earth_rotate.setRotation(tf2::Vector3(0, 0, 1), ros::Time::now().toSec() / T_rotation);

        // q = q1 * q2 = inlined_axis * self_rotation
        trans_sun2earth.transform.rotation = tf2::toMsg(q_earth_axis * q_earth_rotate);

        // broadcast
        broadcaster.sendTransform(trans_sun2earth);
        */

        // sun to middle; for earth revolution
        geometry_msgs::TransformStamped trans_sun2middle;
        trans_sun2middle.header.stamp = ros::Time(0);
        trans_sun2middle.header.frame_id = "sun";
        trans_sun2middle.child_frame_id = "middle";
        trans_sun2middle.transform.translation = geometry_msgs::Vector3();  // same origin
        tf2::Quaternion q_sun2middle;
        q_sun2middle.setRotation(tf2::Vector3(0, 0, 1), ros::Time::now().toSec() / T_revolution);
        trans_sun2middle.transform.rotation = tf2::toMsg(q_sun2middle);
        
        // middle to earth; for earth rotation
        geometry_msgs::TransformStamped trans_middle2earth;
        trans_middle2earth.header.stamp = ros::Time(0);
        trans_middle2earth.header.frame_id = "middle";
        trans_middle2earth.child_frame_id = "earth";
        trans_middle2earth.transform.translation.x = 3; // radius
        trans_middle2earth.transform.translation.y = 0;
        trans_middle2earth.transform.translation.z = 0;
        tf2::Quaternion q_earth_axis;   // an inclined axis
        q_earth_axis.setRPY(0, -M_PI_4, 0);
        tf2::Quaternion q_earth_rotate; // self rotation
        q_earth_rotate.setRotation(tf2::Vector3(0, 0, 1), ros::Time::now().toSec() / T_rotation);
        trans_middle2earth.transform.rotation = tf2::toMsg(q_earth_axis * q_earth_rotate);

        broadcaster.sendTransform(trans_sun2middle);
        broadcaster.sendTransform(trans_middle2earth);

        rate.sleep();
    }

    return 0;
}

