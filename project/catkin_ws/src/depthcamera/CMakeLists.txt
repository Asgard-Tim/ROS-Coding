cmake_minimum_required(VERSION 3.0.2)
project(depthcamera)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
)

find_package(OpenCV REQUIRED)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs
 DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(depthcamera src/main.cpp)
add_dependencies(depthcamera ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(depthcamera
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)