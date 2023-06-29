cmake_minimum_required(VERSION 3.0.2)
project(imu)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  sensor_msgs
  std_msgs
)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS nav_msgs roscpp sensor_msgs std_msgs
 DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(imu src/main.cpp)
add_dependencies(imu ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(imu ${catkin_LIBRARIES} )