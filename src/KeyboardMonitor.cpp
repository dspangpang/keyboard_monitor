//
// Created by root on 4/4/23.
//

#include "../include/keyboard_monitor/KeyboardMonitor.h"

KeyboardMonitor::KeyboardMonitor(const ros::NodeHandle &nh){
    init_keyboard();
    peek_character = -1;

    this->nh_ = nh;
    const auto& tmp_node_name = ros::this_node::getName();
    nh_.getParam(tmp_node_name + "/pub_topic", pub_topic_);

    pub_ = nh_.advertise<std_msgs::Int32>(pub_topic_, 10);
}

KeyboardMonitor::~KeyboardMonitor(){
    close_keyboard();
}

void KeyboardMonitor::init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag |= ICANON;
    new_settings.c_lflag |= ECHO;
    new_settings.c_lflag |= ISIG;

    // 设置非规范模式
    new_settings.c_lflag &= ~(ICANON | ECHO);

    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void KeyboardMonitor::close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int KeyboardMonitor::keyboard_hit()
{
    unsigned char ch;
    int n_read;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    n_read = int (read(0,&ch,1));
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(n_read == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int KeyboardMonitor::read_char()
{
    char ch;

    if(peek_character != -1)
    {
        ch = char(peek_character);
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}

void KeyboardMonitor::keyboard_monitor(){
    while(ros::ok()){
        keyboard_hit();
        std_msgs::Int32 msg;
        msg.data =  read_char();
        pub_.publish(msg);
    }
}

void KeyboardMonitor::start() {
    boost::function0<void> f = [this] { keyboard_monitor(); };
    boost::thread process(f);

}
