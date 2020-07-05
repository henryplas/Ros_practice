cmake_minimum_required(VERSION 3.0.2)
project(ros_service_assignment)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   RectangleAreaService.srv
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ros_service_assignment
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(rect_server src/rect_server.cpp)
target_link_libraries(rect_server ${catkin_LIBRARIES})
add_dependencies(rect_server ros_service_assignment_gencpp)

add_executable(rect_client src/rect_client.cpp)
target_link_libraries(rect_client ${catkin_LIBRARIES})
add_dependencies(rect_client ros_service_assignment_gencpp)