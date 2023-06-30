cmake_minimum_required(VERSION 3.0.2)
project(slam-gmapping)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  std_msgs
)

find_package(OpenCV REQUIRED)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS nav_msgs roscpp std_msgs
 DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(slam-gmapping src/main.cpp)
add_dependencies(slam-gmapping ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(slam-gmapping ${catkin_LIBRARIES} ${OpenCV_LIBS})