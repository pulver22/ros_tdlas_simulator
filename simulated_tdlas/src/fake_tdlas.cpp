
#include "fake_tdlas.h"
#include <../../opt/ros/indigo/include/sensor_msgs/PointCloud.h>
#include <../../opt/ros/indigo/include/sensor_msgs/ChannelFloat32.h>
#include <../../opt/ros/indigo/include/ros/publisher.h>




//=======================================================
  int main( int argc, char** argv )
//=======================================================
{


	//ros::init(argc, argv, "fake_tdlas");
	ros::init(argc, argv, NODE_NAME);
	ros::NodeHandle n;
	loadNodeParameters(n);
	ros::Rate r(10);
	
	std::string topic_name;
	
	ros::Publisher sensor_read_pub = n.advertise<std_msgs::Float32>("Sensor_reading", 500);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("Sensor_display", 100);
	
	ros::Publisher line_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 100);
	
	//ros::Publisher cloud_pub = n.advertise<sensor_msgs::PointCloud>("cloud", 50);

	ros::ServiceClient client = n.serviceClient<msgs_and_srvs::SensorPosition2>("/odor_value");
	
	std::ifstream stream("/home/pulver/vhbennetts-gas_dispersion_simulator-133e66aa7611/demo_files/windData/environments/original.env", std::ifstream::binary);

	int numrows = 61;
	int numcols = 21;
	
	tf::TransformListener listener;
	//sensor_msgs::PointCloud cloud;
	
	
	
	
	visualization_msgs::Marker line, points;
	
	line.header.frame_id = input_fixed_frame.c_str();
	line.ns = "sensor_visualization";
	line.action = visualization_msgs::Marker::ADD;
	line.type = visualization_msgs::Marker::LINE_STRIP;
	line.id = 2;
	
	line.scale.x = 0.1;
	
	line.color.g = 1.0f;
	line.color.a = 1.0;
	
	points.header.frame_id = input_fixed_frame.c_str();
	points.ns = "sensor_visualization";
	points.action = visualization_msgs::Marker::ADD;
	points.type = visualization_msgs::Marker::POINTS;
	points.id = 3;
	
	points.scale.x = 0.2;
	points.scale.y = 0.2;
	
	points.color.r = 0.294118f;
	points.color.b = 0.509804f;
	points.color.a = 1.0;
	

	
	
	
	while (ros::ok()){

	    std_msgs::Float32	read_msg;
	    read_msg.data=0;
	    tf::StampedTransform transform;
	    
	    try{
	    listener.lookupTransform(input_fixed_frame.c_str(), input_sensor_frame.c_str(),  
					ros::Time(0), transform);
	    }
	    catch (tf::TransformException ex){
	    ROS_ERROR("%s",ex.what());
	    ros::Duration(1.0).sleep();
		}
	    
	    
	    float x_pos=transform.getOrigin().x() ;
	    float y_pos=transform.getOrigin().y()  ;
	    float z_pos=transform.getOrigin().z();
	    
	    /*
	    float x_pos = 11 ;
	    float y_pos =  40; 
	    float z_pos = 2 ;
	    */

	    
	    line.header.stamp = ros::Time::now();
	    points.header.stamp = ros::Time::now();
	    

	    
	    //float azimuthal_start = atan2(4 - y_pos, 7 - x_pos);
	    //float azimuthal_end = atan2(4 - y_pos, 30 - x_pos);
	    
	    //starting angle
	    float azimuthal_start = 3*(PI /2);
	    //ending angle
	    float azimuthal_end = 5*(PI/2);
	    
	     //float azimuthal_start = atan2(4 - y_pos, 7 - x_pos);
	    //float azimuthal_end = atan2(4 - y_pos, 30 - x_pos);
	   
	    //angle of incedence
	    float polar = 8.5*(PI/18);
	    
		    
	    float concentration_read = 0;
	    double totalConcentration = 0;
	    
	    for(double azimuthal = azimuthal_start; azimuthal < azimuthal_end; azimuthal += (azimuthal_end - azimuthal_start)/8) {
		int hit = 0;
		double m = 0;
			
		while(m < 20 && hit == 0) {
		    float curX = x_pos + m*cos(azimuthal)*sin(polar);
		    float curY = y_pos + m*sin(azimuthal)*sin(polar);
		    float curZ = z_pos + m*cos(polar);
		    
		    int offset = (((int)curZ)*((2*(numrows*numcols + 1)))) + 2*(((int)curX)*numcols + ((int)curY));
	
		    stream.seekg(offset, stream.beg);
		    int value;
		    stream >> value;
		    
		    //std::cout << "Value: " << value << std::endl;
		    
		    if(value == 1){
			hit = 1;
			//std::cout << "HIT" << std::endl;
		    }else{
			
			srv.request.x[m] = curX;
			srv.request.y[m] = curY;
			srv.request.z[m] = curZ;
			
			
			geometry_msgs::Point p;
			p.x = curX;
			p.y = curY;
			p.z = curZ;
			
			line.points.push_back(p);
			points.points.push_back(p);
			
			
			marker_pub.publish(line);
			marker_pub.publish(points);
			
		    }
		    
		    m += 1;
		}
		
		boost::array<float, 20ul> concentration_values;
		
		if(client.call(srv)){
		    //for(int i =0; i<m; i++){
			 concentration_values = srv.response.odor_r;
		   // }
		}
		
		
		double finalConcentration = 0;
		for(int i =0; i != m;i++){
		    finalConcentration = finalConcentration + concentration_values[i];
		   //concentration_values[i] = 0;
		}
		cout <<"Concentration along this laser :"<<  finalConcentration << endl;
		totalConcentration = totalConcentration+ finalConcentration;
	    
		//std::cout << "OUT!" << std::endl;
	    }
	
	cout << "Final concentration in the scanned area: " << totalConcentration << endl;
	
	
	line.points.clear();
	points.points.clear();
	marker_pub.publish(line);
	marker_pub.publish(points);  
	

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

file = fopen("/home/pulver/ros_catkin/odour_simulation_ws/src/simulated_tdlas/src/sensor_log.txt", "a");
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












