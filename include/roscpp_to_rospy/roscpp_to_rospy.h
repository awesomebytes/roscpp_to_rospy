#include "ros/ros.h"

/*
Author: Sammy Pfeiffer
*/

// To expose a roscpp stuff to Python

#ifndef ROSCPP_TO_ROSPY_ROSCPPNODE_
#define ROSCPP_TO_ROSPY_ROSCPPNODE_

class ROScppNode {
public:
    /* Create a ROS C++ Node */
    ROScppNode(const std::string& node_name, 
                    bool anonymous=false, 
                    bool disable_rosout=false, 
                    bool disable_signals=false);

    ~ROScppNode();

    ros::NodeHandlePtr nh_;
    ros::NodeHandlePtr nh_priv_;
};


#endif