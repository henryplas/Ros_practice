#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void listenerCallback(const sensor_msgs::ImageConstPtr& msg)
{
	//recieve image
	cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, 
      	sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }


    //image processing for tennis ball
    Mat hsv_image;
    Mat yellow_filtered;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<int> lower = {60, 100, 150};
    vector<int> upper = {100, 255, 255};

    Mat frame = cv_ptr->image;

    Mat dst = Mat::zeros(frame.rows, frame.cols, CV_8UC3); 


    //convdrt color
    cvtColor(frame, hsv_image, COLOR_RGB2HSV);
    //filter out the yellows
    inRange(hsv_image, lower, upper, yellow_filtered);
    //find contours
    findContours(yellow_filtered.clone(),
        contours,
        hierarchy,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE);

    if (hierarchy.empty() != true)
    {
    	for(int idx = 0; idx >= 0; idx = hierarchy[idx][0] )
	    {
	        Scalar color(idx*5, 255, 255 );
	        drawContours(dst, contours, idx, color, 1, 8, hierarchy );
	    }
	}

    imshow("test", dst);
    waitKey(1);
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "TennisBallListener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("tennis_ball_image", 
		10, listenerCallback);

	ros::spin();
	return 0;
}