/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-03 19:46:01
 */

#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "tf_listener");

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::TransformStamped trans;

    ros::Rate rate(10);
    ros::Time time = ros::Time::now() + ros::Duration(0.55);
    while (ros::ok())
    {
        try
        {
            trans = buffer.lookupTransform("map", "base_link", time, ros::Duration(0.1));
        }
        catch (tf2::TransformException & ex)
        {
            ROS_WARN_ONCE("Could not transform: %s", ex.what());
            continue;
        }

        ROS_INFO("x offset from base_link to map = %.4f", trans.transform.translation.x);

        rate.sleep();
    }

    return 0;
}
