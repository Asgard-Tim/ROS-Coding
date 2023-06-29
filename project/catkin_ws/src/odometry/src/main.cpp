#include <iostream>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
using namespace std;

void callback(const nav_msgs::Odometry::ConstPtr& ptr)
{
    cout << "std_msgs/Header header" << endl;
    cout << "    uint32 seq: " << ptr->header.seq << endl;
    cout << "    time stamp: " << ptr->header.stamp << endl;
    cout << "    string frame_id: " << ptr->header.frame_id << endl;
    cout << "string child_frame_id: " << ptr->child_frame_id << endl;
    cout << "geometry_msgs/PoseWithCovariance pose" << endl;
    cout << "    geometry_msgs/Pose pose" << endl;
    cout << "        geometry_msgs/Point position" << endl;
    cout << "        float64 x: " << ptr->pose.pose.position.x << endl;
    cout << "        float64 y: " << ptr->pose.pose.position.y << endl;
    cout << "        float64 z: " << ptr->pose.pose.position.z << endl;
    cout << "    geometry_msgs/Quaternion orientation" << endl;
    cout << "        float64 x: " << ptr->pose.pose.orientation.x << endl;
    cout << "        float64 y: " << ptr->pose.pose.orientation.y << endl;
    cout << "        float64 z: " << ptr->pose.pose.orientation.z << endl;
    cout << "        float64 w: " << ptr->pose.pose.orientation.w << endl;
    cout << "    float64[36] covariance" << endl;
    cout << "        " << endl;
    for (int i = 0; i < 36; i++) {
        cout << ptr->pose.covariance[i] << " ";
    }
    cout << endl;
    cout << "geometry_msgs/TwistWithCovariance twist" << endl;
    cout << "    geometry_msgs/Twist twist" << endl;
    cout << "        geometry_msgs/Vector3 linear" << endl;
    cout << "            float64 x: " << ptr->twist.twist.linear.x << endl;
    cout << "            float64 y: " << ptr->twist.twist.linear.y << endl;
    cout << "            float64 z: " << ptr->twist.twist.linear.z << endl;
    cout << "        geometry_msgs/Vector3 angular" << endl;
    cout << "            float64 x: " << ptr->twist.twist.angular.x << endl;
    cout << "            float64 y: " << ptr->twist.twist.angular.y << endl;
    cout << "            float64 z: " << ptr->twist.twist.angular.z << endl;
    cout << "    float64[36] covariance" << endl;
    cout << "        " << endl;
    for (int i = 0; i < 36; i++) {
        cout << ptr->twist.covariance[i] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------------------" << endl;
    return ;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odometry");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("/odom", 1000, callback);
    ros::spin();
    return 0;
}