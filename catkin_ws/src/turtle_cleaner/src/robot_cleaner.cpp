#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

const double x_min = 0;
const double x_max = 11;
const double y_min = 0;
const double y_max = 11;
const double PI = 3.14159265359;
//method to move robot straight

void move(double speed, double distance, bool isForward);
void rotate(double angular_speed, double relative_angle, bool clockwise);
void setDesiredOrientation(double desired_angle);
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message);
void moveGoal(turtlesim::Pose goal_pose, double distance_tolerance);
double getDistance(double x1, double y1, double x2, double y2);
void gridClean();
void spiralClean();

int main(int argc, char *argv[])
{
	
	ros::init(argc, argv, "robot_cleaner");
	ros::NodeHandle n;


	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
	pose_subscriber = n.subscribe("/turtle1/pose", 10, poseCallback);


	ROS_INFO("Start testing");
	// cout<<"enter speed: ";
	// double speed = 0;
	// cin>>speed;
	// cout<<"enter distance: ";
	// double distance;
	// cin>>distance;
	// cout<< "forward?: ";
	// bool isForward;
	// cin >> isForward;
	// move(speed, distance, isForward);

	// cout<<"enter speeof rotation: ";
	// double ang_speed = 0;
	// cin>>ang_speed;
	// cout<<"enter relative angle: ";
	// double ang_distance;
	// cin>> ang_distance;
	// cout<< "clockwise?: ";
	// bool isclk;
	// cin >> isclk;
	// rotate(ang_speed, ang_distance, isclk);

	// setDesiredOrientation(1.5);
	ros::Rate loop_rate(0.5);
	// loop_rate.sleep();
	// setDesiredOrientation(-0.75);
	// loop_rate.sleep();
	// setDesiredOrientation(0);


	// turtlesim::Pose goal_pose;
	// goal_pose.x = 1;
	// goal_pose.y = 1;
	// goal_pose.theta = 0;
	// moveGoal(goal_pose, 0.01);
	// loop_rate.sleep();
	
	// gridClean();

	spiralClean();

	ros::spin();

	return 0;
}



void move(double speed, double distance, bool isForward)
{
	geometry_msgs::Twist vel_msg;

	if(isForward)
		vel_msg.linear.x = abs(speed);
	else
		vel_msg.linear.x = - abs(speed);
	
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;

	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;
	vel_msg.angular.z = 0;


	//t0 is current time
	//loop
	//publish velocity
	//estimate distance = speed * (t1 - t0)
	//current_distance_moved <= distance?

	double t0 = ros::Time::now().toSec();

	double current_distance = 0;

	ros::Rate loop_rate(10);

	do
	{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_distance = speed * (t1 - t0);
		ros::spinOnce();
		loop_rate.sleep();
	}
	while(current_distance < distance);


	vel_msg.linear.x = 0;
	velocity_publisher.publish(vel_msg);
}

void rotate(double angular_speed, double relative_angle, bool clockwise)
{
	geometry_msgs::Twist vel_msg;

	vel_msg.linear.x = 0;
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;


	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

	if(clockwise)
		vel_msg.angular.z = -abs(angular_speed);
	else
		vel_msg.angular.z = abs(angular_speed);


	double t0 = ros::Time::now().toSec();
	ros::Rate loop_rate(10);
	double current_angle = 0;

	do
	{
	velocity_publisher.publish(vel_msg);
	double t1 = ros::Time::now().toSec();
	current_angle = angular_speed * (t1 - t0);
	ros::spinOnce();
	loop_rate.sleep();
	}
	while (current_angle < relative_angle);


	vel_msg.angular.z = 0;
	velocity_publisher.publish(vel_msg);

}

void setDesiredOrientation(double desired_angle)
{
	double rel_angle = desired_angle - turtlesim_pose.theta;
	bool clockwise = (rel_angle < 0) ? true:false;
	rotate(PI / 18, abs(rel_angle), clockwise);
}

void poseCallback(const turtlesim::Pose::ConstPtr & pose_message)
{
	turtlesim_pose.x = pose_message->x;
	turtlesim_pose.y = pose_message->y;
	turtlesim_pose.theta = pose_message->theta;
}

double getDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void moveGoal(turtlesim::Pose goal_pose, double distance_tolerance)
{
	geometry_msgs::Twist vel_msg;

	ros::Rate loop_rate(10);

	do{
		vel_msg.linear.x = 1 * getDistance(turtlesim_pose.x, 
			turtlesim_pose.y, goal_pose.x, goal_pose.y);
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 2 * (atan2(goal_pose.y - turtlesim_pose.y, 
			goal_pose.x - turtlesim_pose.x) - turtlesim_pose.theta);

		velocity_publisher.publish(vel_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	while(getDistance(turtlesim_pose.x, turtlesim_pose.y, 
		goal_pose.x, goal_pose.y) > distance_tolerance);

	cout<<"goal reached"<<endl;
	vel_msg.linear.x = 0;
	vel_msg.angular.z = 0;
	velocity_publisher.publish(vel_msg);


}


void gridClean()
{
	ros::Rate loop(0.5);
	turtlesim::Pose pose;
	pose.x = 1;
	pose.y = 1;
	pose.theta = 0;
	moveGoal(pose, 0.01);
	loop.sleep();
	setDesiredOrientation(0);
	loop.sleep();

	move(2.0, 9.0, true);
	loop.sleep();
	rotate(PI /18, PI/ 2, false);
	loop.sleep();
	move(2.0, 9.0, true);

	rotate(1.0, PI / 2, false);
	loop.sleep();
	move(2.0, 1.0, true);
	rotate(PI / 18, PI / 2, false);
	loop.sleep();
	move(2.0, 9.0, true);



	rotate(1.0, PI/2, true);
	loop.sleep();
	move(2.0, 1.0, true);
	rotate(PI / 18, PI / 2, true);
	loop.sleep();
	move(2.0, 9.0, true);

	double distance = getDistance(turtlesim_pose.x, 
		turtlesim_pose.y, x_max, y_max);
}

void spiralClean()
{
	geometry_msgs::Twist vel_msg;
	double count = 0;

	double constant_speed = 4;
	double vk = 1;
	double wk = 2;
	double rk = 0.5;
	ros::Rate loop(1);

	do
	{
		rk = rk + 0.5;
		vel_msg.linear.x = rk;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = constant_speed;


		velocity_publisher.publish(vel_msg);
		ros::spinOnce();

		loop.sleep();	
	}
	while((turtlesim_pose.x < 10.5) && (turtlesim_pose.y < 10.5));

	vel_msg.linear.x = 0;

	velocity_publisher.publish(vel_msg);


}