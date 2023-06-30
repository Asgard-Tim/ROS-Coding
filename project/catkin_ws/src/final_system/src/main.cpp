#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<iomanip>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include <cstring>
#include <opencv2/opencv.hpp>
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include <memory>
#include "pcl/visualization/cloud_viewer.h"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/point_types.h"
#include "pcl/PCLPointCloud2.h"
#include "pcl/conversions.h"
#include "pcl_ros/transforms.h"
using namespace std;

pcl::visualization::CloudViewer viewer("Cloud Viewer");

void callback5(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PCLPointCloud2 pcl_pc;
    pcl_conversions::toPCL(*msg, pcl_pc);
    pcl::fromPCLPointCloud2(pcl_pc, cloud);
    viewer.showCloud(cloud.makeShared());
}

void callback4(const sensor_msgs::ImageConstPtr& ptr)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(ptr, sensor_msgs::image_encodings::TYPE_16UC1);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return ;
    }
    cv::imshow("depth_camera", cv_ptr->image);
    cv::waitKey(1);
    return ;
}

void callback3(const sensor_msgs::ImageConstPtr& ptr)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(ptr, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return ;
    }
    cv::imshow("color_camera", cv_ptr->image);
    cv::waitKey(1);
    return ;
}

void callback2(const nav_msgs::Odometry::ConstPtr& ptr)
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

void callback1(const sensor_msgs::Imu::ConstPtr& ptr)
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

class user
{
private:
    string username;
    string password;
public:
    void putusername(){cin>>username;}
    void putpassword(){cin>>password;}
    string getusername(){return username;}
    string getpassword(){return password;}
};

void initialize()
{
    cout<<"********************************************"<<endl;
    cout<<"*           欢迎您使用ROS展示系统          *"<<endl;
    cout<<"*                                          *"<<endl;
    cout<<"*                1.用户登录                *"<<endl;
    cout<<"*                2.用户注册                *"<<endl;
    cout<<"*                0.退出系统                *"<<endl;
    cout<<"*                                          *"<<endl;
    cout<<"********************************************"<<endl;
    cout<<"请输入您需要执行的功能编号:";
}

void systeminitialize(string username)
{
    cout<<"******************************************"<<endl;
    cout<<"*                 功能菜单               *"<<endl;
    cout<<"*                                        *"<<endl;
    cout<<"*             1.展示imu数据              *"<<endl;
    cout<<"*             2.展示里程计数据           *"<<endl;
    cout<<"*             3.展示颜色相机数据         *"<<endl;
    cout<<"*             4.展示深度相机数据         *"<<endl;
    cout<<"*             5.展示点云数据             *"<<endl;
    cout<<"*             0.退出登录                 *"<<endl;
    cout<<"*                                        *"<<endl;
    cout<<"******************************************"<<endl;
    cout<<"亲爱的用户"<<username<<",欢迎进入ROS数据展示平台"<<endl;
    cout<<"请输入您需要执行的功能编号:";
}

string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

void DelLineData(char* fileName, int lineNum)
{
	ifstream in;
	in.open(fileName);
	
	string strFileData = "";
	int line = 0;
	char lineData[1024] = {0};
	while(in.getline(lineData, sizeof(lineData)))
	{
        line++;
		if (line == lineNum)
			continue;
		else
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
	}
	in.close();
 
	//写入文件
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}

int main(int argc, char** argv)
{
    while(true)
    {
        fstream userinformation;
        userinformation.open("userinformation.txt",ios::in|ios::app);
        initialize();//初始化界面
        //账号注册与登录模块
        string op1;
        cin>>op1;
        if(op1=="1")
        {
            //用户登录，先让用户输入账号和密码   
            user user1;
            int flagin=0;
            cout<<"请输入您的用户名:";
            user1.putusername();
            cout<<"请输入您的用户密码:";
            user1.putpassword();
            //将用户录入的与文件中保存的账号密码进行比对
            string use=user1.getusername()+" "+user1.getpassword();
            while(true)
            {
                string inform;
                getline(userinformation,inform);
                if(inform=="")
                    break;
                if(use==inform)
                {
                    cout<<"亲爱的用户"<<user1.getusername()<<",欢迎您登录本系统"<<endl;
                    systeminitialize(user1.getusername());//初始化界面
                    string op2;
                    cin>>op2;
                    if(op2=="1")
                    {
                        ros::init(argc, argv, "imu");
                        ros::NodeHandle nodeHandle;
                        ros::Subscriber subscriber = nodeHandle.subscribe("/imu/data_raw", 1000, callback1);
                        ros::spin();         
                    }
                    else if(op2=="2")
                    {  
                        ros::init(argc, argv, "odometry");
                        ros::NodeHandle nodeHandle;
                        ros::Subscriber subscriber = nodeHandle.subscribe("/odom", 1000, callback2);
                        ros::spin();
                    }
                    else if(op2=="3")
                    {
                        ros::init(argc, argv, "colourcamera");
                        ros::NodeHandle nodeHandle;
                        image_transport::ImageTransport imageTransport(nodeHandle);
                        image_transport::Subscriber subscriber = imageTransport.subscribe("/camera/color/image_raw", 1000, callback3);
                        ros::spin();
                    }
                    else if(op2=="4")
                    {
                        ros::init(argc, argv, "depthcamera");
                        ros::NodeHandle nodeHandle;
                        image_transport::ImageTransport imageTransport(nodeHandle);
                        image_transport::Subscriber subscriber = imageTransport.subscribe("/camera/depth/image_rect_raw", 1000, callback4);
                        ros::spin();            
                    }
                    else if(op2=="5")
                    {
                        ros::init(argc, argv, "pclpoints");
                        ros::NodeHandle nodeHandle;
                        ros::Subscriber subscriber = nodeHandle.subscribe("/rslidar_points", 1000, callback5);
                        ros::spin();  
                    }
                    else if(op2=="0")
                    {
                        cout<<"正在为您登出中……";       
                    }
                    else
                    {
                        cout<<"您输入了无效的操作代码,请重新输入";
                    }
                    flagin=1;
                    break;
                }
            }
            if(flagin==0)
            {
                cout<<"您输入的账号或密码错误,请检查后重新输入";
            }
        }
        else if(op1=="2")
        {
            //用户注册，输入用户名与密码
            user user1;
            cout<<"请输入您的用户名(仅可使用数字与字母):";
            user1.putusername();
            //判断用户名是否已经存在
            int flag=0;
            while(true)
            {
                string name;
                userinformation>>name;
                string empty;
                getline(userinformation,empty);
                if(name=="")
                    break;
                if(user1.getusername()==name)
                {
                    cout<<"您输入的用户名已经存在,注册失败,请重新输入"<<endl;
                    flag=1;
                    break;
                }
            }
            userinformation.close();
            userinformation.open("userinformation.txt",ios::in|ios::app);
            if(flag==0)
            {
                cout<<"请输入您的用户密码(仅可使用数字或字母,不小于6位):";
                user1.putpassword();
                //判断用户输入的密码是否符合要求，若符合要求则录入文件
                string pass=user1.getpassword();
                if(pass.length()<6)
                {
                    cout<<"您输入的密码小于6位,请重新输入"<<endl;
                }
                else
                {
                    cout<<"您已成功注册,请进行登录"<<endl;
                    userinformation<<user1.getusername()<<" "<<user1.getpassword()<<endl;
                }
            }
        }
        else if(op1=="0")
        {
            int fl=0;
            while(fl==0)
            {
                cout<<"您确认要退出该系统吗?(是请按1,否请按0)";
                int opp;
                cin>>opp;
                if(opp==1)
                    exit(0);
                else if(opp==0)
                    fl=1;
                else
                    cout<<"您输入有误,请重新输入"<<endl;
            }
            
        }
        else
        {
            cout<<"您输入了无效的操作代码,请重新输入";
        }
        userinformation.close();
    }
    return 0;
}