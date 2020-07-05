cmake_minimum_required(VERSION 2.8.3)
project(open_cv_test)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  actionlib_msgs
  cv_bridge
  image_transport
  message_generation
)

catkin_package(
  #INCLUDE_DIRS include
  #LIBRARIES ros_essentials_cpp
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  #DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(read_video_test src/read_video.cpp)
target_link_libraries(read_video_test ${catkin_LIBRARIES})
target_link_libraries(read_video_test ${OpenCV_LIBRARIES})

add_executable(TennisBallTalker_cpp src/tennisBallTalker.cpp)
target_link_libraries(TennisBallTalker_cpp ${catkin_LIBRARIES})
target_link_libraries(TennisBallTalker_cpp ${OpenCV_LIBRARIES})

add_executable(TennisBallListener_cpp src/tennisBallListener.cpp)
target_link_libraries(TennisBallListener_cpp ${catkin_LIBRARIES})
target_link_libraries(TennisBallListener_cpp ${OpenCV_LIBRARIES})