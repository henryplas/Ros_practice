#include "ros/ros.h"
#include "ros_essentials_cpp/IoTSensor.h"

void iot_sensor_callback(const ros_essentials_cpp::IoTSensor& msg)
{

  ROS_INFO("[%d]\n[%s]\n[%f]\n[%f]", msg.id,
                                      msg.name.c_str(),
                                      msg.temperature,
                                      msg.humidity);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "iot_sub");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("iot_sensor_topic", 1000, iot_sensor_callback);
  ros::spin();

  return 0;
}