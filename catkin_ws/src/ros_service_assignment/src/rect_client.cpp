#include "ros/ros.h"
#include "ros_service_assignment/RectangleAreaService.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rect_client");
  if (argc != 3)
  {
    ROS_INFO("usage: find area of rectangle");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ros_service_assignment::RectangleAreaService>("rect_service");
  ros_service_assignment::RectangleAreaService srv;
  srv.request.width = atof(argv[1]);
  srv.request.height = atof(argv[2]);


  if (client.call(srv))
  {
    ROS_INFO("Area: %f", (float)srv.response.area);
  }
  else
  {
    ROS_ERROR("Failed to call service rect_service");
    return 1;
  }

  return 0;
}