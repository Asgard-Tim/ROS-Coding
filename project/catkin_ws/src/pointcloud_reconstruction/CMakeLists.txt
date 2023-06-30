cmake_minimum_required(VERSION 2.8.3)
project(pointcloud_reconstruction)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
  sensor_msgs
)

find_package(PCL REQUIRED)

catkin_package(
  CATKIN_DEPENDS pcl_ros roscpp sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

link_directories(
  ${PCL_LIBRARY_DIRS}
)

add_executable(reconstruction_node src/reconstruction_node.cpp)
target_link_libraries(reconstruction_node ${catkin_LIBRARIES} ${PCL_LIBRARIES})

