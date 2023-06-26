#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist tmp_twist;

ros::Publisher cmd_vel_pub;

void keyboard_callback(const std_msgs::Int32ConstPtr &msg){

    auto tmp = msg->data;

    std::cout << "key value : " << tmp << std::endl;

    switch (tmp)
    {
    case 119:
        tmp_twist.linear.x += 0.1; 
        break;
    
    case 115:
        tmp_twist.linear.x -= 0.1; 
        break;
    
    case 100:
        tmp_twist.angular.z -= 0.1; 
        break;

    case 97:
        tmp_twist.angular.z += 0.1; 
        break;

    case 32:
        tmp_twist.linear.x = 0;
        tmp_twist.angular.z = 0; 
        break;

    default:
        break;
    }

    cmd_vel_pub.publish(tmp_twist);
}


int main(int argc, char ** argv){

    ros::init(argc, argv, "keyboard_to_cmd_vel_node");
    ros::NodeHandle nh;

    std::string sub_topic;

    const auto& tmp_node_name = ros::this_node::getName();

    nh.getParam(tmp_node_name + "/sub_topic", sub_topic);

    ros::Subscriber key_val_sub;

    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    key_val_sub = nh.subscribe<std_msgs::Int32>(sub_topic, 1, keyboard_callback);
    
    
    ros::spin();

    return 0;
}

