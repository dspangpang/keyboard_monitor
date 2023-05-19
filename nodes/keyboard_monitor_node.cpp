//
// Created by root on 4/4/23.
//

#include "../include/keyboard_monitor/KeyboardMonitor.h"


int main(int argc, char ** argv){

    ros::init(argc, argv, "keyboard_monitor_node");
    ros::NodeHandle nh;
    double frequency = 35;

    KeyboardMonitor km(nh);

    const auto& tmp_node_name = ros::this_node::getName();

    nh.getParam(tmp_node_name + "/pub_frequency",frequency);

    ros::Rate rate(frequency);

    km.start();

    while(ros::ok()){

        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}


