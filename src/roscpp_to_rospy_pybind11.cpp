#include "ros/ros.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <image_transport/image_transport.h>
//#include "roscpp_to_rospy/roscpp_to_rospy.h"
// pyrosmsg takes care of translating messages Python<->C++
#include <pyrosmsg/pyrosmsg.h>
#include <std_msgs/String.h>

#include <iostream>

/*
Author: Sammy Pfeiffer
*/
namespace py = pybind11;

/* Create a Publisher  */
class ROSCppPublisher{
    public:
        // Not supporting tcp_nodelay or subscriber_listener parameters for now
        ROSCppPublisher(const std::string& node_name, const std::string& topic_name, const std::string& topic_type, const bool latch, const int queue_size){
            // node_name is used to initialize this cpp node if it was not initialized yet
            if (!ros::isInitialized()){
                ROS_INFO_STREAM("ROSCppPublisher not initialized, initializing...");
                int argc = 0;
                uint32_t flags = ros::init_options::NoSigintHandler; //anonymous & ros::init_options::AnonymousName | disable_rosout & ros::init_options::NoRosout | disable_signals & ros::init_options::NoSigintHandler
                ros::init(argc, nullptr, node_name, flags);
            }
            nh_ = ros::NodeHandlePtr(new ros::NodeHandle());
            //nh_priv_ = ros::NodeHandlePtr(new ros::NodeHandle("~"));
            // TODO: automate this somehow
            if (topic_type == "std_msgs/String"){
                pub_ = nh_->advertise<std_msgs::String>(topic_name, queue_size, latch);
            }
        }

        void publish(std_msgs::String& msg){
            pub_.publish(msg);
            ros::spinOnce();
            // If doing anything long running, this is the way to check to get the Control+C to get us out of here
            // And provide the Python interpreter with the signal
            // if (PyErr_CheckSignals() != 0)
            //     throw py::error_already_set();
        }


        ~ROSCppPublisher() {
            std::cout << "(cout) Destructor called." << std::endl;
            nh_->shutdown();
        }



    private:
        // image_transport::ImageTransport *it_;
        // image_transport::Publisher pub_;
        ros::NodeHandlePtr nh_;
        ros::NodeHandlePtr nh_priv_;
        ros::Publisher pub_;

};

PYBIND11_MODULE(roscpp_to_rospy, m) {
    m.doc() = "pybind11 roscpp_to_rospy";

    py::class_<ROSCppPublisher>(m, "ROSCppPublisher")
        .def(
            py::init<const std::string&,
                        const std::string&,
                        const std::string&,
                        const bool,
                        const int>(),
            "Create a ROS C++ Publisher",
                        py::arg("node_name"),
                        py::arg("topic_name"),
                        py::arg("topic_type"),
                        py::arg("latch") = false,
                        py::arg("queue_size") = 1
            )

        .def("publish", &ROSCppPublisher::publish);

    

}