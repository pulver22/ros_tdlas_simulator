#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cstdlib>
#include <math.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <vector>
#include <msgs_and_srvs/SensorPosition.h>
#include <msgs_and_srvs/readings.h>

#include<msgs_and_srvs/ChemicalValue.h>

  using namespace std;

  int ch_id;	
  float t_stamp=0.0;

  //initial positions[x][y] for robot0,robot1,robot2:
  int map_points[6]={4,0,6,0,8,0};




