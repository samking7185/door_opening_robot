#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

class TeleopRobot
{
public:
  TeleopRobot();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_, vertical_, horizontal_;
  double l_scale_, a_scale_, v_scale_, h_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};

  
TeleopRobot::TeleopRobot():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobot::joyCallback, this);
}



void TeleopRobot::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_robot");
  TeleopRobot teleop_robot;

  ros::spin();
}
