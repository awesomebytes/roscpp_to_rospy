#include "ros/ros.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/*
Author: Sammy Pfeiffer
*/

// Expose a roscpp stuff to Python

namespace py = pybind11;

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


PYBIND11_MODULE(roscpp_to_rospy, m) {
    m.doc() = "pybind11 roscpp_to_rospy";

    py::class_<ROScppNode>(m, "ROScppNode")
        .def(py::init<const std::string&,
            bool,
            bool,
            bool>(),
            "Create ROS cpp Node with the given node_name",
                py::arg("node_name"),
                py::arg("anonymous") = false, 
                py::arg("disable_rosout") = false,
                py::arg("disable_signals") = false);

}

#endif