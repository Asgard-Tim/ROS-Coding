#include <iostream>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
using namespace std;

void callback(const sensor_msgs::Imu::ConstPtr& ptr)
{
    ROS_INFO("std_msgs/Header header");
    ROS_INFO("    uint32 seq: %d", ptr->header.seq);
    ROS_INFO("    time stamp: %d.%d", ptr->header.stamp.sec, ptr->header.stamp.nsec);
    ROS_INFO("    string frame_id: %s", ptr->header.frame_id.c_str());
    ROS_INFO("geometry_msgs/Quaternion orientation");
    ROS_INFO("    float64 x: %f", ptr->orientation.x);
    ROS_INFO("    float64 y: %f", ptr->orientation.y);
    ROS_INFO("    float64 z: %f", ptr->orientation.z);
    ROS_INFO("    float64 w: %f", ptr->orientation.w);
    ROS_INFO("float64[9] orientation_covariance");
    ROS_INFO("    %f %f %f %f %f %f %f %f %f",
             ptr->orientation_covariance[0], ptr->orientation_covariance[1], ptr->orientation_covariance[2],
             ptr->orientation_covariance[3], ptr->orientation_covariance[4], ptr->orientation_covariance[5],
             ptr->orientation_covariance[6], ptr->orientation_covariance[7], ptr->orientation_covariance[8]);
    ROS_INFO("geometry_msgs/Vector3 angular_velocity");
    ROS_INFO("    float64 x: %f", ptr->angular_velocity.x);
    ROS_INFO("    float64 y: %f", ptr->angular_velocity.y);
    ROS_INFO("    float64 z: %f", ptr->angular_velocity.z);
    ROS_INFO("float64[9] angular_velocity_covariance");
    ROS_INFO("    %f %f %f %f %f %f %f %f %f",
             ptr->angular_velocity_covariance[0], ptr->angular_velocity_covariance[1], ptr->angular_velocity_covariance[2],
             ptr->angular_velocity_covariance[3], ptr->angular_velocity_covariance[4], ptr->angular_velocity_covariance[5],
             ptr->angular_velocity_covariance[6], ptr->angular_velocity_covariance[7], ptr->angular_velocity_covariance[8]);
    ROS_INFO("geometry_msgs/Vector3 linear_acceleration");
    ROS_INFO("    float64 x: %f", ptr->linear_acceleration.x);
    ROS_INFO("    float64 y: %f", ptr->linear_acceleration.y);
    ROS_INFO("    float64 z: %f", ptr->linear_acceleration.z);
    ROS_INFO("float64[9] linear_acceleration_covariance");
    ROS_INFO("    %f %f %f %f %f %f %f %f %f",
             ptr->linear_acceleration_covariance[0], ptr->linear_acceleration_covariance[1], ptr->linear_acceleration_covariance[2],
             ptr->linear_acceleration_covariance[3], ptr->linear_acceleration_covariance[4], ptr->linear_acceleration_covariance[5],
             ptr->linear_acceleration_covariance[6], ptr->linear_acceleration_covariance[7], ptr->linear_acceleration_covariance[8]);
    ROS_INFO("-------------------------------------------------------------");
    return;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "imu");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("/imu/data_raw", 1000, callback);
    ros::spin();
    return 0;
}
