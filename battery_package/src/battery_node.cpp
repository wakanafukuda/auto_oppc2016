#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/Int16.h"

using namespace std;

ros::Publisher sen_pub;
ros::Subscriber sen_sub;

std_msgs::Int16 b_value;

void batteryCallBack(const std_msgs::Int16 msg){
  b_value.data = msg.data;
  ROS_INFO("battery: %d ",msg.data);
  sen_pub.publish(b_value);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "battery_package");
  ros::NodeHandle n;

  sen_pub = n.advertise<std_msgs::Int16>("sensors",1000);
  sen_sub = n.subscribe("chatterbattery",1000,batteryCallBack);

  b_value.data = 0;
  sen_pub.publish(b_value);
  while(ros::ok()){
    ros::spinOnce();
    sleep(1);
  }
  return 0;
}
