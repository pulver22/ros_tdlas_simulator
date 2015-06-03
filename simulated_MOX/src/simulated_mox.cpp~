#include "simulated_mox.hpp"




  int main( int argc, char** argv )
{

  ros::init(argc, argv, "fake_MOX");
  ros::NodeHandle n;
  ros::Rate r(1000);

//receiving chemical value.
  ros::Subscriber sub = n.subscribe("ChemicalValue", 1000,chemicalCallback);

//robot pose
  ros::Subscriber amcl_sub = n.subscribe("/amcl_pose", 10, amclCallback);

//rxplot publisher:
  ros::Publisher readings = n.advertise<msgs_and_srvs::readings>("sensor_readings", 10);

//Service for sensor position
  ros::ServiceClient client = n.serviceClient<msgs_and_srvs::SensorPosition>("odor_value");

//sensor display marker
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("sensor_display", 100);


//pararmeters
  n.getParam("/simulated_MOX/sensor0_hight",sensor0);
  n.getParam("/simulated_MOX/sensor1_hight",sensor1);
  n.getParam("/simulated_MOX/sensor2_hight",sensor2);          
  n.getParam("/simulated_MOX/sensor0_model",sensor0_model);
  n.getParam("/simulated_MOX/sensor1_model",sensor1_model);
  n.getParam("/simulated_MOX/sensor2_model",sensor2_model);

//Service request for the value i.e hit_rate.value[][][]
  msgs_and_srvs::SensorPosition srv;

  msgs_and_srvs::readings response;




  while (ros::ok())
  {
 /* srv.request.x_r0 = int(amcl_pos.pose.pose.position.x);
  srv.request.y_r0 = int(amcl_pos.pose.pose.position.y);
  srv.request.z_r0 = sensor0;

  srv.request.x_r1 = int(amcl_pos.pose.pose.position.x);
  srv.request.y_r1 = int(amcl_pos.pose.pose.position.y);
  srv.request.z_r1 = sensor1;

  srv.request.x_r2 = int(amcl_pos.pose.pose.position.x);
  srv.request.y_r2 = int(amcl_pos.pose.pose.position.y);
  srv.request.z_r2 = sensor2;

  if (client.call(srv))
     {
     //checks of missing any subscribed value
     servive_val[0]=(float)srv.response.odor_r0;
     servive_val[1]=(float)srv.response.odor_r1;
     servive_val[2]=(float)srv.response.odor_r2;
     }
*/
//sensor response
//  response.r0_val=(sensor_response(servive_val[0], ch_id, 0,sensor0_model));
//  response.r1_val=(sensor_response(servive_val[1], ch_id, 1,sensor1_model));
//  response.r2_val=(sensor_response(servive_val[2], ch_id, 2,sensor2_model));

//concentration
 // response.r0_con=servive_val[0];
 // response.r1_con=servive_val[1];
 // response.r2_con=servive_val[2];

//============================================0

  sensor[0].header.frame_id =sensor[1].header.frame_id =sensor[2].header.frame_id = "/map";
  sensor[0].header.stamp =sensor[1].header.stamp=sensor[2].header.stamp = ros::Time::now();
  sensor[0].ns =sensor[1].ns=sensor[2].ns = "sensor_visualization";
  sensor[0].action =sensor[1].action =sensor[2].action =visualization_msgs::Marker::ADD;
  sensor[0].type = sensor[1].type = sensor[2].type = visualization_msgs::Marker::SPHERE;
  sensor[0].id=0;
  sensor[1].id=1;
  sensor[2].id=2;


  //connector:
  connector[0].header.frame_id =connector[1].header.frame_id =connector[2].header.frame_id = "/map";
  connector[0].header.stamp =connector[1].header.stamp=connector[2].header.stamp = ros::Time::now();
  connector[0].ns =connector[1].ns=connector[2].ns = "sensor_visualization";
  connector[0].action =connector[1].action =connector[2].action =visualization_msgs::Marker::ADD;
  connector[0].type = connector[1].type = connector[2].type = visualization_msgs::Marker::CYLINDER;
  connector[0].id=3;
  connector[1].id=4;
  connector[2].id=5;


  //sensor color/size
  sensor[0].scale.x =sensor[1].scale.x =sensor[2].scale.x = 0.5;
  sensor[0].scale.y =sensor[1].scale.y =sensor[2].scale.y = 0.5;
  sensor[0].scale.z =sensor[1].scale.z =sensor[2].scale.z = 0.25;
  sensor[0].color.r =sensor[1].color.r =sensor[2].color.r = 2.0f;
  sensor[0].color.g =sensor[1].color.g =sensor[2].color.g = 1.0f;
  sensor[0].color.a =sensor[1].color.a =sensor[2].color.a = 1.0;

//sensor_0:
  sensor[0].pose.position.x = amcl_pos.pose.pose.position.x;
  sensor[0].pose.position.y = amcl_pos.pose.pose.position.y;
  sensor[0].pose.position.z = amcl_pos.pose.pose.position.z+sensor0;

  //sensor_1:
  sensor[1].pose.position.x = amcl_pos.pose.pose.position.x;
  sensor[1].pose.position.y =amcl_pos.pose.pose.position.y;
  sensor[1].pose.position.z = amcl_pos.pose.pose.position.z+sensor1;

  //sensor_2:
  sensor[2].pose.position.x = amcl_pos.pose.pose.position.x;
  sensor[2].pose.position.y = amcl_pos.pose.pose.position.y;
  sensor[2].pose.position.z = amcl_pos.pose.pose.position.z+sensor2;

  //connector:
  connector[0].scale.x =connector[1].scale.x =connector[2].scale.x = 0.1;
  connector[0].scale.y =connector[1].scale.y =connector[2].scale.y = 0.1;
  connector[0].color.a =connector[1].color.a =connector[2].color.a = 1.0;


    connector[0].color.r = 1.0f;
    connector[1].color.b = 1.0f;
    connector[2].color.g = 1.0f;

    connector[0].scale.z =sensor0; 
    connector[1].scale.z = sensor1;
    connector[2].scale.z = sensor2;

    connector[0].pose.position.x = amcl_pos.pose.pose.position.x;
    connector[0].pose.position.y = amcl_pos.pose.pose.position.y;
    connector[0].pose.position.z = float(sensor0)/2;

    connector[1].pose.position.x = amcl_pos.pose.pose.position.x;
    connector[1].pose.position.y = amcl_pos.pose.pose.position.y;
    connector[1].pose.position.z = float(sensor1)/2;

    connector[2].pose.position.x = amcl_pos.pose.pose.position.x;
    connector[2].pose.position.y = amcl_pos.pose.pose.position.y;
    connector[2].pose.position.z = float(sensor2)/2;




//===============================================
//Publishing sensor and connectior display:
  for(int j=0;j<=S_NO;j++)
     {
     marker_pub.publish(sensor[j]);
     marker_pub.publish(connector[j]);
     }

//Publishing value for rxplot
  readings.publish(response);

  ros::spinOnce();
  r.sleep();

  }
}



//================================================================//
//			     Callbacks				  //
//================================================================//
  //receiving chemical value.
  void chemicalCallback(const msgs_and_srvs::ChemicalValue::ConstPtr& msg)
{
	ch_id=msg->id;

}

  void amclCallback(const geometry_msgs::PoseWithCovarianceStamped& msg)
{
	amcl_pos.pose.pose.position.x = msg.pose.pose.position.x;
	amcl_pos.pose.pose.position.y = msg.pose.pose.position.y;
	amcl_pos.pose.pose.position.z = msg.pose.pose.position.z;

}


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




