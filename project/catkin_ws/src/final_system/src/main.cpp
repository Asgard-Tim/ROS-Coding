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
#include "nav_msgs/OccupancyGrid.h"
using namespace std;

pcl::visualization::CloudViewer viewer("Cloud Viewer");

void callback6(const nav_msgs::OccupancyGrid::ConstPtr& ptr)
{   
    std::cout << "resolution: " << ptr->info.resolution << std::endl;
    std::cout << "width: " << ptr->info.width << std::endl;
    std::cout << "height: " << ptr->info.height << std::endl;
    double scale = 1.0;
    int width = 1200;
    int height = 1200;
    cv::Point offset(-1600, -1600);
    cv::Mat map = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
    for (int i = 0; i < ptr->info.width * ptr->info.height; ++i) {
        int x = (i % ptr->info.width + offset.x) * scale, y = (i / ptr->info.width + offset.y) * scale;
        if (ptr->data[i] == -1) {
            cv::circle(map, cv::Point(x, y), 1, cv::Scalar(255, 255, 255), -1);
        } else if (ptr->data[i] >= 80) {
            cv::circle(map, cv::Point(x, y), 3, cv::Scalar(0, 0, 0), -1);
        } else {
            cv::circle(map, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), -1);
        }    
    }
    cv::imshow("map", map);
    cv::waitKey(1000);
    return ;
}

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

void callback1(const sensor_msgs::Imu::ConstPtr& ptr)
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
    cout<<"*             6.Gmapping算法建图         *"<<endl;
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
                    else if(op2=="6")
                    {
                        ros::init(argc, argv, "show_map");
                        ros::NodeHandle nodeHandle;
                        ros::Subscriber subscriber = nodeHandle.subscribe("/map", 1000, callback6);
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