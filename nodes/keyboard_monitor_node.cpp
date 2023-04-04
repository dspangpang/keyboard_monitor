//
// Created by root on 4/4/23.
//

#include "../include/keyboard_monitor/KeyboardMonitor.h"


int main(int argc, char ** argv){

    ros::init(argc, argv, "keyboard_monitor_node");
    ros::NodeHandle nh;

    KeyboardMonitor km(nh);

    ros::Rate rate(35);

    km.start();

    while(ros::ok()){

        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}


