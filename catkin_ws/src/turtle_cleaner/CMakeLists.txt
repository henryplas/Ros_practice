cmake_minimum_required(VERSION 3.0.2)
project(turtle_cleaner)




find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	geometry_msgs
	message_generation
)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES turtle_cleaner
   CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs message_runtime
#  DEPENDS system_lib
)


add_executable(robot_cleaner_node src/robot_cleaner.cpp)
target_link_libraries(robot_cleaner_node ${catkin_LIBRARIES})
#add_dependencies(robot_cleaner_node turtle_cleaner_gencpp)