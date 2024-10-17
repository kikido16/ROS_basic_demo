#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_spawn");
    ros::NodeHandle n;

    // wait for service and create service client
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle=n.serviceClient<turtlesim::Spawn>("/spawn");

    // create service request object and fill in request parameters
    turtlesim::Spawn srv;
    srv.request.x=2.0;
    srv.request.y=2.0;
    srv.request.name="turtle2";
    
    // call service and wait for response
    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]",
             srv.request.x, srv.request.y, srv.request.name.c_str());
    add_turtle.call(srv);

    // check if service call was successful and print response message
    ROS_INFO("Spwan turtle successfully [name:%s]",srv.response.name.c_str());
    return 0;
}