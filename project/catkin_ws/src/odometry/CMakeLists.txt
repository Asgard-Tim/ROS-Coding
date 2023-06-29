cmake_minimum_required(VERSION 3.0.2)
project(odometry)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(odometry src/main.cpp)
add_dependencies(odometry ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(odometry ${catkin_LIBRARIES} )