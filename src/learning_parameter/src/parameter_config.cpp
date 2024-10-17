#include <string>
#include <ros/ros.h>
#include <std_srvs/Empty.h>

int main(int argc, char **argv)
{
    int red, green, blue;
    ros::init(argc, argv, "parameter_config");
    ros::NodeHandle n;

    ros::param::get("/turtlesim/background_color/r",red);
    ros::param::get("/turtlesim/background_color/g",green);
    ros::param::get("/turtlesim/background_color/b",blue);

    ROS_INFO("Get background color: r=%d, g=%d, b=%d", red, green, blue);

    ros::param::set("/turtlesim/background_color/r", 0);
    ros::param::set("/turtlesim/background_color/g", 0);
    ros::param::set("/turtlesim/background_color/b",0);
    ROS_INFO("Set background color: r=255, g=255, b=255");

    ros::param::get("/turtlesim/background_color/r",red);
    ros::param::get("/turtlesim/background_color/g",green);
    ros::param::get("/turtlesim/background_color/b",blue);
    ROS_INFO("Re-get background color: r=%d, g=%d, b=%d", red, green, blue);

    ros::service::waitForService("/clear");
    ros::ServiceClient clear_background = n.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty srv;
    clear_background.call(srv);
    ROS_INFO("Clear background color");


}