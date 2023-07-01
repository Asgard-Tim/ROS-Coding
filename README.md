使用指南

详细操作过程详见演示视频Demo(链接：)

这里给出一些操作命令可供复制：

docker run -p 5900:5900 -p 6080:80 --rm -e RESOLUTION=1920x1080 liujiboy/ros
roscore
rosbag play --loop --pause all.bag
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libopencv-dev
sudo apt-get install libopencv-contrib-dev
sudo apt-get update
sudo apt-get install libproj-dev
sudo apt-get install libpcl-dev
source /home/ubuntu/project/catkin_ws/devel/setup.bash
cd /home/ubuntu/project/catkin_ws
rosrun final_system final_system
