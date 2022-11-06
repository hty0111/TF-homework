/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-03 19:45:50
 */


#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "tf_broadcaster");

    tf2_ros::TransformBroadcaster broadcaster;

    double x_offset = 0.0;

    ros::Rate rate(10);
    while (ros::ok())
    {
        geometry_msgs::TransformStamped trans;
        trans.header.stamp = ros::Time::now();
        trans.header.frame_id = "map";
        trans.child_frame_id = "base_link";

        trans.transform.translation.x = x_offset;
        trans.transform.translation.y = 0;
        trans.transform.translation.z = 0;

        tf2::Quaternion q;
        q.setRPY(0, 0, 0);
        trans.transform.rotation = tf2::toMsg(q);

        broadcaster.sendTransform(trans);

        x_offset += 0.1;

        rate.sleep();
    }

    return 0;
}
