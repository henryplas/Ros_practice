#include "ros/ros.h"
#include "ros_service_assignment/RectangleAreaService.h"

bool area(ros_service_assignment::RectangleAreaService::Request  &req,
         ros_service_assignment::RectangleAreaService::Response &res)
{
  res.area = req.width * req.height;
  ROS_INFO("request: width=%f, height=%f", (float)req.width, (float)req.height);
  ROS_INFO("sending back response: [%f]", (float)res.area);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rect_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("rect_service", area);
  ROS_INFO("Ready to make an area");
  ros::spin();

  return 0;
}