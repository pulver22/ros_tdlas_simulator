#include "moving_sensor.h"
#include <fstream>
#include <iostream>
#include <ros/ros.h>



  int counter=1;
  int toggle=0;
  bool initial = true;
  double response1=0;	
  double response2[S_NO];
  float a;
  float record[S_NO][sim_time]={0};
  float tau[S_NO]={12.4*0.04};	
  float servive_val[S_NO]={0};

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


 /* void sensor_start() {

	ROS_INFO("\nHEIGHTS OF SENSORS: [1][2][3]\n");
		std::cin>>sensor0>>sensor1>>sensor2;
			
	ROS_INFO("\nSENSOR MODELS: [TGS 2600 => 0][TGS 2611 => 1][TGS 2620 => 2]\n");
		std::cin>>robot_0_sensor_model>>robot_1_sensor_model>>robot_2_sensor_model;

}*/


//conversion from concentration to sensor resistance ratio:
  float sensor_response(float concentration, int ch_id, int robot_id, int sensor_model){



	if(concentration==0) {
		if(sensor_model==0){response1=21;}
		if(sensor_model==1){response1=1;}
		if(sensor_model==2){response1=8.7;}

 }
			else {  
			
			//A*e^B + C*e^D
			response1= (dd[sensor_model][ch_id][0]* exp(dd[sensor_model][ch_id][1] * concentration))+(dd[sensor_model][ch_id][2]* exp(dd[sensor_model][ch_id][3]* concentration)) ;

//std::cout<<"id "<<sensor_model<<"  "<<ch_id<<std::endl;
 }

	//storing sensor response in array for comparision:
	record[robot_id][counter]=response1;

	//comparision between last value and current value:
  //decay:
  if(record[robot_id][counter]>record[robot_id][counter-1]) {tau[robot_id]=40.7*0.15;}

  //rise:
  if(record[robot_id][counter]<record[robot_id][counter-1])  {tau[robot_id]=7.4*0.04;}

   //alpha value
   a=1/(tau[robot_id]+1);
                        //filtered response:
			response2[robot_id]=(a* response1)+(1-a)*response2[robot_id];
			
  toggle++;
  if(toggle==3){toggle=0; counter++;} 


//initial sensor values:
	if(initial==true) {

		if(sensor_model==0){response2[robot_id]= 21;}
		if(sensor_model==1 && ch_id!=2){response2[robot_id]= 1;}
		if(sensor_model==2){response2[robot_id]= 8.7;}
  		if(robot_id==2)    {initial = false;}

    }
		//TGS2600 hydrogen response=0.1.
		if(sensor_model==1 && ch_id==2){response2[robot_id]= 0.100000;} 

	        return response2[robot_id]; 

}
