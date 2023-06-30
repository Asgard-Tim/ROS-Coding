#include <iostream>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
using namespace std;

void callback(const nav_msgs::Odometry::ConstPtr& ptr)
{
    ROS_INFO("std_msgs/Header header");
    ROS_INFO("    uint32 seq: %d", ptr->header.seq);
    ROS_INFO("    time stamp: %d.%d", ptr->header.stamp.sec, ptr->header.stamp.nsec);
    ROS_INFO("    string frame_id: %s", ptr->header.frame_id.c_str());
    ROS_INFO("string child_frame_id: %s", ptr->child_frame_id.c_str());
    ROS_INFO("geometry_msgs/PoseWithCovariance pose");
    ROS_INFO("    geometry_msgs/Pose pose");
    ROS_INFO("        geometry_msgs/Point position");
    ROS_INFO("        float64 x: %f", ptr->pose.pose.position.x);
    ROS_INFO("        float64 y: %f", ptr->pose.pose.position.y);
    ROS_INFO("        float64 z: %f", ptr->pose.pose.position.z);
    ROS_INFO("    geometry_msgs/Quaternion orientation");
    ROS_INFO("        float64 x: %f", ptr->pose.pose.orientation.x);
    ROS_INFO("        float64 y: %f", ptr->pose.pose.orientation.y);
    ROS_INFO("        float64 z: %f", ptr->pose.pose.orientation.z);
    ROS_INFO("        float64 w: %f", ptr->pose.pose.orientation.w);
    ROS_INFO("    float64[36] covariance");
    ROS_INFO("        ");
    for (int i = 0; i < 36; i++) {
        ROS_INFO("%f ", ptr->pose.covariance[i]);
    }
    ROS_INFO("geometry_msgs/TwistWithCovariance twist");
    ROS_INFO("    geometry_msgs/Twist twist");
    ROS_INFO("        geometry_msgs/Vector3 linear");
    ROS_INFO("            float64 x: %f", ptr->twist.twist.linear.x);
    ROS_INFO("            float64 y: %f", ptr->twist.twist.linear.y);
    ROS_INFO("            float64 z: %f", ptr->twist.twist.linear.z);
    ROS_INFO("        geometry_msgs/Vector3 angular");
    ROS_INFO("            float64 x: %f", ptr->twist.twist.angular.x);
    ROS_INFO("            float64 y: %f", ptr->twist.twist.angular.y);
    ROS_INFO("            float64 z: %f", ptr->twist.twist.angular.z);
    ROS_INFO("    float64[36] covariance");
    ROS_INFO("        ");
    for (int i = 0; i < 36; i++) {
        ROS_INFO("%f ", ptr->twist.covariance[i]);
    }
    ROS_INFO("-------------------------------------------------------------");
    return;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "odometry");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("/odom", 1000, callback);
    ros::spin();
    return 0;
}