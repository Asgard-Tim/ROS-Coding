#include <iostream>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
using namespace std;

void callback(const sensor_msgs::Imu::ConstPtr& ptr)
{
    cout << "std_msgs/Header header" << endl;
    cout << "    uint32 seq: " << ptr->header.seq << endl;
    cout << "    time stamp: " << ptr->header.stamp << endl;
    cout << "    string frame_id: " << ptr->header.frame_id << endl;
    cout << "geometry_msgs/Quaternion orientation" << endl;
    cout << "    float64 x: " << ptr->orientation.x << endl;
    cout << "    float64 y: " << ptr->orientation.y << endl;
    cout << "    float64 z: " << ptr->orientation.z << endl;
    cout << "    float64 w: " << ptr->orientation.w << endl;
    cout << "float64[9] orientation_covariance" << endl;
    cout << "    ";
    for (int i = 0; i < 9; i++) {
        cout << ptr->orientation_covariance[i] << " ";
    }
    cout << endl;
    cout << "geometry_msgs/Vector3 angular_velocity" << endl;
    cout << "    float64 x: " << ptr->angular_velocity.x << endl;
    cout << "    float64 y: " << ptr->angular_velocity.y << endl;
    cout << "    float64 z: " << ptr->angular_velocity.z << endl;
    cout << "float64[9] angular_velocity_covariance" << endl;
    cout << "    ";
    for (int i = 0; i < 9; i++) {
        cout << ptr->angular_velocity_covariance[i] << " ";
    }
    cout << endl;
    cout << "geometry_msgs/Vector3 linear_acceleration" << endl;
    cout << "    float64 x: " << ptr->linear_acceleration.x << endl;
    cout << "    float64 y: " << ptr->linear_acceleration.y << endl;
    cout << "    float64 z: " << ptr->linear_acceleration.z << endl;
    cout << "float64[9] linear_acceleration_covariance" << endl;
    cout << "    ";
    for (int i = 0; i < 9; i++) {
        cout << ptr->linear_acceleration_covariance[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------------------" << endl;
    return ;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "imu");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("/imu/data_raw", 1000, callback);
    ros::spin();
    return 0;
}
