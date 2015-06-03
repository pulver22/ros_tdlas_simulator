#include <fstream>
#include <iostream>
#include <ros/ros.h>
#include <msgs_and_srvs/SensorPosition.h>
#include <msgs_and_srvs/ChemicalValue.h>
#include <msgs_and_srvs/readings.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/Marker.h>

  #define S_NO 3
  #define sim_time 100000 //ms/s..

 int ch_id;
 geometry_msgs::PoseWithCovarianceStamped amcl_pos;

 int sensor0;
 int sensor1;
 int sensor2;

 int sensor0_model;
 int sensor1_model;
 int sensor2_model;

  //display sensor marker:
  visualization_msgs::Marker sensor[S_NO],connector[S_NO];

//sensor_resp:
   double response1=0;	
   double response2[S_NO];
   float record[S_NO][100000] ={0};
   int counter=1;
   int toggle=0;
   bool initial =true;
   float a;
   float tau[S_NO]={12.4*0.04};
   //float dd[3][3][4];
   float servive_val[S_NO];

  float dd[3][3][4]={
		//constants: A, B, C, D			
		{  //TGS2620
		{6.018,-0.01662, 0.9832,-0.0005651},  //ethanol
		{18.79,-0.01062, 6.138, -0.0002136 },  //methane
		{3.884 ,-0.0127,0.8745,-0.0003222 }, //hydrogen
		},

		{  //TGS2600
		{0.4668,-0.3249, 0.3293, -0.01051 },  //ethanol
		{0.2202, -0.1122, 0.8356, -0.001932},  //methane
		{0.0,0.0,0.0,0.0},  //hydrogen
		},

		{  //TGS2611
		{4.766,-0.001639, 3.497, -7.348e-05 },  //ethanol
		{3.286 ,-0.002211, 1.806 -0.000103},  //methane
		{4.535, -0.001723, 2.69, -5.191e-05},  //hydrogen
		}
	};








void chemicalCallback (const msgs_and_srvs::ChemicalValue::ConstPtr& msg);
void amclCallback     (const geometry_msgs::PoseWithCovarianceStamped& msg);
float sensor_response (float concentration, int ch_id, int robot_id, int sensor_model);


