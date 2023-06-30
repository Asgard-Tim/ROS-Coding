cmake_minimum_required(VERSION 3.0.2)
project(final_system)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  std_msgs
  roscpp
  sensor_msgs
  cv_bridge
  image_transport
  message_generation
)

find_package(OpenCV REQUIRED)

find_package(PCL REQUIRED)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS  nav_msgs std_msgs roscpp sensor_msgs cv_bridge image_transport 
 DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(final_system src/main.cpp)
add_dependencies(final_system ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(final_system
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
  ${PCL_LIBRARIES}
)