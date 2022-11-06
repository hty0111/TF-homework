/*
 * @Description: earth 自传+公转
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-02 14:52:40
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf2_ros/transform_listener.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "earth");
    ros::NodeHandle node;
    ros::Publisher marker_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    // earth sphere
    visualization_msgs::Marker sphere;
    sphere.header.frame_id = "/world";
    sphere.header.stamp = ros::Time();

    sphere.ns = "earth";
    sphere.id = 0;
    sphere.type = visualization_msgs::Marker::SPHERE;
    sphere.action = visualization_msgs::Marker::ADD;

    sphere.scale.x = 1;
    sphere.scale.y = 1;
    sphere.scale.z = 1;

    sphere.color.r = 0;
    sphere.color.g = 0;
    sphere.color.b = 1;
    sphere.color.a = 0.5;

    sphere.lifetime = ros::Duration();

    // earth track
    visualization_msgs::Marker track;
    track.header.frame_id = "/world";
    track.header.stamp = ros::Time();

    track.ns = "earth";
    track.id = 1;
    track.type = visualization_msgs::Marker::LINE_STRIP;
    track.action = visualization_msgs::Marker::ADD;

    track.scale.x = 1;
    track.scale.y = 1;
    track.scale.z = 1;

    track.color.r = 0;
    track.color.g = 0;
    track.color.b = 1;
    track.color.a = 0.3;

    track.lifetime = ros::Duration();

    // tf listener
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    geometry_msgs::TransformStamped trans_sun2earth, trans_earth2self;

    ros::Rate rate(100);
    while (ros::ok())
    {
        try
        {
            // position of Earth frame in Sun frame
            trans_sun2earth = buffer.lookupTransform("sun", "earth", ros::Time(), ros::Duration(1));
        }
        catch (tf2::TransformException & ex)
        {
            ROS_WARN("Could not transform earth to sun: %s", ex.what());
            continue;
        }

        sphere.pose.position.x = trans_sun2earth.transform.translation.x;
        sphere.pose.position.y = trans_sun2earth.transform.translation.y;
        sphere.pose.position.z = trans_sun2earth.transform.translation.z;
        sphere.pose.orientation = trans_sun2earth.transform.rotation;

        geometry_msgs::Point p;
        p.x = trans_sun2earth.transform.translation.x;
        p.y = trans_sun2earth.transform.translation.y;
        p.z = trans_sun2earth.transform.translation.z;
        track.points.push_back(p);

        if (track.points.size() > 10000)
            track.points.erase(track.points.begin());

        marker_pub.publish(sphere);
        marker_pub.publish(track);

        rate.sleep();
    }

    return 0;
}