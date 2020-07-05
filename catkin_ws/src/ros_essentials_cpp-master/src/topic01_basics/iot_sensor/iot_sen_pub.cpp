#include "ros/ros.h"
#include "ros_essentials_cpp/IoTSensor.h"

#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "iot_pub");

  ros::NodeHandle n;
  ros::Publisher chatter_pub = 
          n.advertise<ros_essentials_cpp::IoTSensor>("iot_sensor_topic", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    // std_msgs::String msg;
    // std::stringstream ss;
    // ss << "hello world " << count;

    ros_essentials_cpp::IoTSensor msg;



    msg.id = 1;
    msg.name = "iot_parking_01";
    msg.temperature = 6969.234;
    msg.humidity = 123.56;

    ROS_INFO("[%d]\n[%s]\n[%f]\n[%f]", msg.id,
                                      msg.name.c_str(),
                                      msg.temperature,
                                      msg.humidity);
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}