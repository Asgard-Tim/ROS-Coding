cmake_minimum_required(VERSION 3.0.2)
project(colourcamera)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  cv_bridge
  image_transport
)

find_package(OpenCV REQUIRED)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS roscpp sensor_msgs cv_bridge image_transport
 DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(colourcamera src/main.cpp)
add_dependencies(colourcamera ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(colourcamera
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)