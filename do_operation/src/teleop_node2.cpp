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
  ros::Publisher vert_pub_, horz_pub_;
  ros::Subscriber joy_sub_;

};

  
TeleopRobot::TeleopRobot():
  vertical_(1),
  horizontal_(2)
{
  nh_.param("axis_vertical", vertical_, vertical_);
  nh_.param("axis_horizontal", horizontal_, horizontal_);
  nh_.param("scale_vertical", v_scale_, v_scale_);
  nh_.param("scale_horizontal", h_scale_, h_scale_);

  vert_pub_ = nh_.advertise<std_msgs::Float64>("/mobile_robot/joint1_position_controller/command", 1);
  horz_pub_ = nh_.advertise<std_msgs::Float64>("/mobile_robot/joint2_position_controller/command", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopRobot::joyCallback, this);
}



void TeleopRobot::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  std_msgs::Float64 twist;
  std_msgs::Float64 twist1;
  twist.data = v_scale_*joy->axes[vertical_];
  twist1.data = -h_scale_*joy->axes[horizontal_];

  vert_pub_.publish(twist);
  horz_pub_.publish(twist1);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_robot2");
  TeleopRobot teleop_robot2;

  ros::spin();
}
