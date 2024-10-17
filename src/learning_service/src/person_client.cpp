#include <ros/ros.h>
#include "learning_service/Person.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "person_client");
    ros::NodeHandle n;

     // wait for service and create service client
    ros::service::waitForService("/show_person");
    ros::ServiceClient person_client=n.serviceClient<learning_service::Person>("/show_person");

    learning_service::Person srv;
    srv.request.name="John";
    srv.request.age=25;
    srv.request.sex=learning_service::Person::Request::male;

    ROS_INFO("Call service to show person[name:%s, age:%d, sex:%d]",
    srv.request.name.c_str(), srv.request.age, srv.request.sex);
    person_client.call(srv);

    ROS_INFO("Show person resutl: %s", srv.response.result.c_str());
    return 0;
}
