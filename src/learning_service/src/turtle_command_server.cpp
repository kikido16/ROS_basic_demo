#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>

ros::Publisher turtle_vel_pub;
bool pubCommand=false;

// Callback function for turtle command service,input req and output res
bool commandCallback(std_srvs::Trigger::Request &req,
                    std_srvs::Trigger::Response &res)
{
    pubCommand=!pubCommand;
    ROS_INFO("Publish turtle velocity command [%s]",pubCommand==true?"Yes":"No");

    res.success=true;
    res.message="Change turtle command state!";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_command_server");
    ros::NodeHandle n;
    // Create a server and register the commandCallback function
    ros::ServiceServer command_service=n.advertiseService("turtle_command",commandCallback);
    //create a publisher to publish turtle velocity command
    turtle_vel_pub=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ROS_INFO("Ready to receive turtle command.");
    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        //check callback function
        ros::spinOnce();
        if(pubCommand)
        {
            geometry_msgs::Twist vel_msgs;
            vel_msgs.linear.x=0.5;
            vel_msgs.angular.z=0.2;
            turtle_vel_pub.publish(vel_msgs);
        }
    }

}