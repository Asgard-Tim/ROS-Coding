使用指南

详细操作过程详见演示视频Demo(链接：https://www.bilibili.com/video/BV1YV411M7jj/)

这里给出一些操作命令可供复制：

（1）docker虚拟机启动容器

docker run -p 5900:5900 -p 6080:80 --rm -e RESOLUTION=1920x1080 liujiboy/ros

（2）库文件安装

sudo apt-get update

sudo apt-get upgrade

sudo apt-get install libopencv-dev

sudo apt-get install libopencv-contrib-dev

sudo apt-get update

sudo apt-get install libproj-dev

sudo apt-get install libpcl-dev

sudo apt-get install libsdl1.2-dev

sudo apt install libsdl-image1.2-dev

sudo apt-get install ros-kinetic-gmapping

sudo apt-get install ros-kinetic-slam-gmapping

（3）运行程序

roscore

rosbag play --loop --pause all.bag

rosrun gmapping slam_gmapping

source /home/ubuntu/project/catkin_ws/devel/setup.bash

cd /home/ubuntu/project/catkin_ws

rosrun final_system final_system
