#include "ros/ros.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roscpp_to_rospy/roscpp_to_rospy.h"

/*
Author: Sammy Pfeiffer
*/

// Expose a roscpp stuff to Python thru pybind11

namespace py = pybind11;

PYBIND11_MODULE(roscpp_to_rospy_pybind11, m) {
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
                py::arg("disable_signals") = false)

        .def("isInitialized", &ROScppNode::isInitialized)
                
        .def("spinOnce", &ROScppNode::spinOnce)
        
        .def("ROS_INFO", &ROScppNode::ROS_INFO_cpp);

}
