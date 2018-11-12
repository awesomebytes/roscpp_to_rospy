#include "ros/ros.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>

namespace py = pybind11;

class ROScppNode {
public:
    ROScppNode(const std::string& node_name, 
                    bool anonymous=false, 
                    bool disable_rosout=false, 
                    bool disable_signals=false){
        uint32_t flags = anonymous & ros::init_options::AnonymousName | disable_rosout & ros::init_options::NoRosout | disable_signals & ros::init_options::NoSigintHandler;
        int argc = 0;

        ros::init(argc, nullptr, node_name, flags);

        nh_ = ros::NodeHandle();

    }

    ~ROScppNode() {
        if(ros::isInitialized() && !ros::isShuttingDown()){
            ros::shutdown();
        }
    }

    ros::NodeHandle nh_;
};


PYBIND11_MODULE(roscpp_to_rospy, m) {
    m.doc() = "pybind11 roscpp_to_rospy";

    py::class_<ROScppNode>(m, "ROScppNode")
        .def(py::init<const std::string&, 
                bool, 
                bool, 
                bool>(),
                "Create ROS cpp Node",
                py::arg("node_name"),
                py::arg("anonymous") = false, 
                py::arg("disable_rosout") = false,
                py::arg("disable_signals") = false);

}