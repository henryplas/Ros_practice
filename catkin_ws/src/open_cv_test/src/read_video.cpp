#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;





int main(int, char**)
{
    VideoCapture video_capture(0); // open the default camera
    if(!video_capture.isOpened())  // check if we succeeded
        return -1;

    Mat hsv_image;
    Mat yellow_filtered;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<int> lower = {60, 100, 150};
    vector<int> upper = {100, 255, 255};

    while(true)
    {
        Mat frame;
        video_capture >> frame; // get a new frame from camera
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

        for(int idx = 0; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( idx*5, 255, 255 );
            drawContours( dst, contours, idx, color, 1, 8, hierarchy );
        }


        //display video
        imshow("name", dst);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}