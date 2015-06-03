
#include "fake_MOX.h"

//=======================================================
  int main( int argc, char** argv )
//=======================================================
{


	//ros::init(argc, argv, "fake_MOX");
	ros::init(argc, argv, NODE_NAME);
	ros::NodeHandle n;
	loadNodeParameters(n);
	ros::Rate r(10);
	
	std::string topic_name;
	
	ros::Publisher sensor_read_pub = n.advertise<std_msgs::Float32>("Sensor_reading", 500);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("Sensor_display", 100);
	
	ros::ServiceClient client = n.serviceClient<msgs_and_srvs::SensorPosition>("/odor_value");
	
	visualization_msgs::Marker sensor,connector;
	sensor.header.frame_id = input_fixed_frame.c_str();
	sensor.ns = "sensor_visualization";
	
	sensor.action =visualization_msgs::Marker::ADD;
	sensor.type = visualization_msgs::Marker::SPHERE;
	sensor.id=0;
	
	sensor.scale.x = 0.5;
	sensor.scale.y = 0.5;
	sensor.scale.z = 0.25;
	sensor.color.r =2.0f;
	sensor.color.g = 1.0f;
	sensor.color.a =1.0;
	
	
	connector.header.frame_id = input_fixed_frame.c_str();
	connector.ns  = "sensor_visualization";
	connector.action = visualization_msgs::Marker::ADD;
	connector.type =  visualization_msgs::Marker::CYLINDER;
	connector.id=1;

//connector color/size
	connector.scale.x = 0.1;
	connector.scale.y = 0.1;

	connector.color.a  = 1.0;
	connector.color.r = 1.0f;
	connector.color.b = 1.0f;
	connector.color.g = 1.0f;

	
	
//receiving chemical value.
 /* ros::Subscriber sub = n.subscribe("ChemicalValue", 1000, chemicalCallback);

//robot pose
ros::Subscriber amcl_sub = n.subscribe("/amcl_pose", 10, amclCallback);

//rqt_plot:
  ros::Publisher readings = n.advertise<msgs_and_srvs::readings>("sensor_readings", 10);

//Service for sensor position
  ros::ServiceClient client = n.serviceClient<msgs_and_srvs::SensorPosition>("odor_value");

//sensor display marker
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("sensor_display", 100);

  n.getParam("/simulated_MOX/sensor0_hight",sensor0);
  n.getParam("/simulated_MOX/sensor1_hight",sensor1);
  n.getParam("/simulated_MOX/sensor2_hight",sensor2);          
  n.getParam("/simulated_MOX/sensor0_model",robot_0_sensor_model);
  n.getParam("/simulated_MOX/sensor1_model",robot_1_sensor_model);
  n.getParam("/simulated_MOX/sensor2_model",robot_2_sensor_model);

//sensor
  sensor[0].header.frame_id =sensor[1].header.frame_id =sensor[2].header.frame_id = "/map";
  sensor[0].header.stamp =sensor[1].header.stamp=sensor[2].header.stamp = ros::Time::now();
  sensor[0].ns =sensor[1].ns=sensor[2].ns = "sensor_visualization";
  sensor[0].action =sensor[1].action =sensor[2].action =visualization_msgs::Marker::ADD;
  sensor[0].type = sensor[1].type = sensor[2].type = visualization_msgs::Marker::SPHERE;
  sensor[0].id=0;
  sensor[1].id=1;
  sensor[2].id=2;
//sensor color/size
  sensor[0].scale.x =sensor[1].scale.x =sensor[2].scale.x = 0.5;
  sensor[0].scale.y =sensor[1].scale.y =sensor[2].scale.y = 0.5;
  sensor[0].scale.z =sensor[1].scale.z =sensor[2].scale.z = 0.25;
  sensor[0].color.r =sensor[1].color.r =sensor[2].color.r = 2.0f;
  sensor[0].color.g =sensor[1].color.g =sensor[2].color.g = 1.0f;
  sensor[0].color.a =sensor[1].color.a =sensor[2].color.a = 1.0;
//connector:
  connector[0].header.frame_id =connector[1].header.frame_id =connector[2].header.frame_id = "/map";
  connector[0].header.stamp =connector[1].header.stamp=connector[2].header.stamp = ros::Time::now();
  connector[0].ns =connector[1].ns=connector[2].ns = "sensor_visualization";
  connector[0].action =connector[1].action =connector[2].action =visualization_msgs::Marker::ADD;
  connector[0].type = connector[1].type = connector[2].type = visualization_msgs::Marker::CYLINDER;
  connector[0].id=3;
  connector[1].id=4;
  connector[2].id=5;
//connector color/size
  connector[0].scale.x =connector[1].scale.x =connector[2].scale.x = 0.1;
  connector[0].scale.y =connector[1].scale.y =connector[2].scale.y = 0.1;
  connector[0].color.a =connector[1].color.a =connector[2].color.a = 1.0;
  connector[0].color.r = 1.0f;
  connector[1].color.b = 1.0f;
  connector[2].color.g = 1.0f;
  connector[0].scale.z =sensor0; 
  connector[1].scale.z = sensor1;
  connector[2].scale.z = sensor2;

*/
	tf::TransformListener listener;
	while (ros::ok()){

	std_msgs::Float32	read_msg;
	read_msg.data=0;
	tf::StampedTransform transform;
	int received;
	received=0;
    try{
      listener.lookupTransform(input_fixed_frame.c_str(), input_sensor_frame.c_str(),  
                               ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      received=1;
      ros::Duration(1.0).sleep();
    }
	
	if (received==0) {
		float x_pos=transform.getOrigin().x();
		float y_pos=transform.getOrigin().y();
		float z_pos=transform.getOrigin().z();
		
		connector.header.stamp = ros::Time::now(); 
		sensor.header.stamp = ros::Time::now();
		connector.scale.z = z_pos;
		
		sensor.pose.position.x = x_pos;
		sensor.pose.position.y = y_pos;
		sensor.pose.position.z = z_pos;
		
		connector.pose.position.x = x_pos;
		connector.pose.position.y = y_pos;
		connector.pose.position.z = float(z_pos)/2;
		
		marker_pub.publish(sensor);
		marker_pub.publish(connector);
		
		
		
			
		// request for concentration
		
		srv.request.x = x_pos; 
		srv.request.y = y_pos; 
		srv.request.z = z_pos;
		float concentration_read;
		if (client.call(srv)) {
			concentration_read=(float)srv.response.odor_r;
			read_msg.data=sensor_response(concentration_read, input_gas_type, 0,input_sensor_model,sensor0_log);
			initial = false;
			sensor_read_pub.publish(read_msg);
		}
		else{
			//ROS_INFO("no contact");
		}
		 
		
	}
	// TF read
	
  ros::spinOnce();
  r.sleep();
}
 
}

//===================================================================================
float sensor_response(float concentration, int ch_id, int sensor_id, int sensor_model,float* sensor)
//===================================================================================

{

//initial sensor values:
  if(initial==true)
      {
      if(sensor_model==0){filtered_resp[sensor_id]= 21;sensor[counter[sensor_id]]=21;}
      if(sensor_model==1 && ch_id!=2){filtered_resp[sensor_id]= 1;sensor[counter[sensor_id]]=1;}
      if(sensor_model==2){filtered_resp[sensor_id]= 8.7;sensor[counter[sensor_id]]=8.7;}
  		   
      return filtered_resp[sensor_id];
      }

  if(concentration==0)
      {
      if(sensor_model==0){y_out=21;}
      if(sensor_model==1){y_out=1;}
      if(sensor_model==2){y_out=8.7;}
      }
  else {  
			
//A*e^B + C*e^D
  if(ch_id<3)    //response for ethanol, methan and hydeogen
     y_out= (cons[sensor_model][ch_id][0]* exp(cons[sensor_model][ch_id][1] * concentration))+(cons[sensor_model][ch_id][2]* exp(cons[sensor_model][ch_id][3]* concentration)) ;
  else           //response for all other gases
     y_out= (cons[sensor_model][0][0]* exp(cons[sensor_model][0][1] * concentration))+(cons[sensor_model][0][2]* exp(cons[sensor_model][0][3]* concentration)) ;
 }

//storing sensor response in array for comparision:
  sensor[counter[sensor_id]]=y_out;

//comparision between last value and current value:
//decay:
  if(sensor[counter[sensor_id]]>sensor[counter[sensor_id]-1]) {tau=40.7*0.15;}

//rise:
  if(sensor[counter[sensor_id]]<sensor[counter[sensor_id]-1])  {tau=7.4*0.04;}

//alpha value
  a=1/(tau+1);

//filtered response:
  filtered_resp[sensor_id]=(a* y_out)+(1-a)*filtered_resp[sensor_id];
			
  counter[sensor_id]++;

//TGS2600 hydrogen response=0.1.
  if(sensor_model==1 && ch_id==2){filtered_resp[sensor_id]= 0.100000;} 

  return filtered_resp[sensor_id]; 

}




//====================================================================
void amclCallback(const geometry_msgs::PoseWithCovarianceStamped& msg)
//====================================================================
{
	amcl_pos.pose.pose.position.x = msg.pose.pose.position.x;
	amcl_pos.pose.pose.position.y = msg.pose.pose.position.y;
	amcl_pos.pose.pose.position.z = msg.pose.pose.position.z;

}


//========================================================================
  void chemicalCallback(const msgs_and_srvs::ChemicalValue::ConstPtr& msg)
//========================================================================
{
	ch_id=msg->id;

}

//========================================================================
  void  writeTofile       (msgs_and_srvs::readings response)
//========================================================================
{
static FILE *file;

file = fopen("/home/victor/ros_catkin/odour_simulation_ws/src/simulated_MOX/src/sensor_log.txt", "a");
  if (file == NULL) {
    fprintf(stderr, "Error opening sensor_log.txt\n");
    exit(1);
  }

fprintf (file, "%f %f %f\n", response.r0_val,response.r1_val,response.r2_val);

fclose(file);

}





void	loadNodeParameters(ros::NodeHandle private_nh)
{

	std::string parameter_name;
	std::string 	param_string;
	double		param_double;
	int		param_int;
	bool		param_bool;
	
	//Gas type
	parameter_name=std::string(NODE_NAME)+std::string("/gas_type");
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_gas_type=param_int;
	}
	else {
		
		input_gas_type=DEFAULT_GAS_TYPE;
	}
	

    //Gas type
	parameter_name=std::string(NODE_NAME)+std::string("/sensor_model");
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_sensor_model=param_int;
	}
	else {
		
		input_sensor_model=DEFAULT_SENSOR_MODEL;
	}
	
	//sensor_frame
	parameter_name=std::string(NODE_NAME)+std::string("/sensor_frame");
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_sensor_frame=param_string;
	}
	else {
		input_sensor_frame=DEFAULT_SENSOR_FRAME;
	}

	//fixed frame
	parameter_name=std::string(NODE_NAME)+std::string("/fixed_frame");
	
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_fixed_frame=param_string;
	}
	else {
		
		input_fixed_frame=DEFAULT_FIXED_FRAME;
		}
	
	



	ROS_INFO("The data provided in the roslaunch file is:");
	
	ROS_INFO("Gas type: %d",input_gas_type);
	ROS_INFO("Sensor model: %d",input_sensor_model);
	ROS_INFO("Fixed frame: %s",input_fixed_frame.c_str());
	ROS_INFO("Sensor frame: %s",input_sensor_frame.c_str());
	


}












