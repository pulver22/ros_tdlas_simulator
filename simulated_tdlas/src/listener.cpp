#include "listener.h"


using namespace std;



/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const sensor_msgs::PointCloud& msg)
{
    int size = msg.points.size();
    cout << "SIze: " << size;
    int i=0;
    while ( i <  size){
	geometry_msgs::Point32 p2;
	p2 = msg.points[i];
	float concentration = msg.channels[0].values[i];
    
	cout << "[SUBSCRIBER] I heard: ("<< p2.x << ","<<p2.y <<","<<p2.z <<") with concentration"<< concentration << endl;
    
	i++;
    }

    //ROS_INFO("[",msg.header.stamp,"]: I heard: [%s]", msg.points[0].x, ",",msg.points[0].y ,",",msg.points[0].z, "with concentration", msg.channels[0].values[0]);
}

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "listener");

    ros::NodeHandle n;

    
    ros::Subscriber sub = n.subscribe("/Tdlas04/cloud", 50, chatterCallback);

    while(ros::ok()){
	//std::cout << "one spin "<<std::endl;
    
	ros::spinOnce();
    }

  return 0;
}