#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

static const std::string OPENCV_WINDOW = "Image window";


image_transport::Subscriber image_sub;
image_transport::Publisher image_pub;


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // Output modified video stream
    //Convert this message to a ROS sensor_msgs::Image message. 
    image_pub.publish(cv_ptr->toImageMsg());
}

int main(int argc, char *argv[])
{
	
	ros::init(argc, argv, "TennisBallTalker");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_sub = it.subscribe("image", 1, imageCallback);
	image_pub = it.advertise("tennis_ball_image", 1);
	ros::spin();
	return 0;
}