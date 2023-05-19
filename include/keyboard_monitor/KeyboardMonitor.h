//
// Created by root on 4/4/23.
//

#ifndef KEYBOARD_MONITOR_KEYBOARDMONITOR_H
#define KEYBOARD_MONITOR_KEYBOARDMONITOR_H

#include <boost/thread.hpp>
#include <termios.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>


class KeyboardMonitor {
public:
    explicit KeyboardMonitor(const ros::NodeHandle &nh);

    ~KeyboardMonitor();

    void start();

private:
    termios initial_settings, new_settings;
    int peek_character;

    ros::NodeHandle nh_;
    std::string pub_topic_;
    ros::Publisher pub_;

    void init_keyboard();

    void close_keyboard();

    int keyboard_hit();

    int read_char();

    void keyboard_monitor();
};


#endif //KEYBOARD_MONITOR_KEYBOARDMONITOR_H
