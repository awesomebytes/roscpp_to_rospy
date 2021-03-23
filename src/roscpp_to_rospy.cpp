#include "ros/ros.h"
#include "roscpp_to_rospy/roscpp_to_rospy.h"

/*
Author: Sammy Pfeiffer
*/

// Expose a roscpp stuff to Python

/* Create a ROS C++ Node */
ROScppNode::ROScppNode(const std::string& node_name, 
                bool anonymous, 
                bool disable_rosout, 
                bool disable_signals){
    uint32_t flags = anonymous & ros::init_options::AnonymousName | disable_rosout & ros::init_options::NoRosout | disable_signals & ros::init_options::NoSigintHandler;
    int argc = 0;

    if(!ros::isInitialized()){
        ros::init(argc, nullptr, node_name, flags);

        nh_ = ros::NodeHandlePtr(new ros::NodeHandle());
        nh_priv_ = ros::NodeHandlePtr(new ros::NodeHandle("~"));
    }
}

void ROScppNode::spinOnce(){
    ros::spinOnce();
}

bool ROScppNode::isInitialized(){
            std::cout << "(cout) ROScppNode is ros::isInitialized?: " << ros::isInitialized() << std::endl;
            std::cout << "(cout) ROScppNode is ros::ok?: " << ros::ok() << std::endl;
            std::cout << "(cout) ROScppNode is ros::isStarted?: " << ros::isStarted() << std::endl;
    return ros::isInitialized();
}

void ROScppNode::ROS_INFO_cpp(const std::string& text){
    ROS_INFO_STREAM(text);
}

ROScppNode::~ROScppNode() {
    if(ros::isInitialized() && !ros::isShuttingDown()){
        ros::shutdown();
    }
}
