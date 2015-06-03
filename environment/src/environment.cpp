#include "environment.h"



int main( int argc, char** argv )
{

  
ros::init(argc, argv, NODE_NAME);
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("source_visualization", 10);
  ros::Publisher pub_marker = n.advertise<visualization_msgs::MarkerArray>("environment_visualization", 100);



//n.getParam("environment/source_height",sourcelocation);
loadNodeParameters(n);
//visualization_msgs::MarkerArray environment;

visualization_msgs::MarkerArray environment;
environment=loadEnvironment (input_environment_data,input_area_cell_size,input_fixed_frame);
 

  ros::Rate r(1);

  while (ros::ok())
  {
	// Displays the emitting source
		visualization_msgs::Marker source[2];
		source[0].id=0;
		source[1].id=1;
		source[0].header.frame_id=source[1].header.frame_id= input_fixed_frame;
		source[0].header.stamp=source[1].header.stamp=ros::Time::now();
		source[0].ns =source[1].ns = "source_visualization";
		source[0].action =source[1].action = visualization_msgs::Marker::ADD;
		source[0].type=source[1].type=visualization_msgs::Marker::CYLINDER;

		source[0].scale.x = 0.5;
		source[0].scale.y = 0.5;
		source[0].scale.z = 1.0;
		source[0].color.g = 0.6f;
		source[0].color.b = 0.4f;
		source[0].color.a = 0.6;
		source[0].pose.position.x = input_source_pos_x+input_area_cell_size/2;
		source[0].pose.position.y = input_source_pos_y;
		source[0].pose.position.z = input_source_pos_z;
		source[0].pose.orientation.x = 0.0;
		source[0].pose.orientation.y = 1.0;
		source[0].pose.orientation.z = 0.0;
		source[0].pose.orientation.w = 1.0;

		source[1].scale.x = 0.5;
		source[1].scale.y = 0.5;
		source[1].scale.z = input_source_pos_z;
		source[1].color.g = 0.6f;
		source[1].color.b = 0.4f;
		source[1].color.a = 0.6;
		source[1].pose.position.x = input_source_pos_x+input_area_cell_size/2;
		source[1].pose.position.y = input_source_pos_y;
		source[1].pose.position.z = input_source_pos_z/2;
		
		
		
		marker_pub.publish(source[0]);
		marker_pub.publish(source[1]);	

	
		pub_marker.publish(environment);
		
 

    r.sleep();
  }
}


void	loadNodeParameters(ros::NodeHandle private_nh)
{

	std::string parameter_name;
	std::string 	param_string;
	double		param_double;
	int		param_int;
	bool		param_bool;
	
	

	//Source postion (x)
	parameter_name=std::string(NODE_NAME)+std::string("/source_position_x");
	if(private_nh.getParam(parameter_name,param_double)) {  
		input_source_pos_x=param_double;
	}
	else {
		input_source_pos_x=DEFAULT_SOURCE_POS_X;
	}
	
	//Source postion (y)
	parameter_name=std::string(NODE_NAME)+std::string("/source_position_y");
	if(private_nh.getParam(parameter_name,param_double)) {  
		input_source_pos_y=param_double;
	}
	else {
		input_source_pos_y=DEFAULT_SOURCE_POS_Y;
	}

	//Source postion (z)
	parameter_name=std::string(NODE_NAME)+std::string("/source_position_z");
	if(private_nh.getParam(parameter_name,param_double)) {  
		input_source_pos_z=param_double;
	}
	else {
		input_source_pos_z=DEFAULT_SOURCE_POS_Z;
	}

	
	
	//environment files
	parameter_name=std::string(NODE_NAME)+std::string("/environment_data");
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_environment_data=param_string;
	}
	else {
		input_environment_data=DEFAULT_ENVIRONMENT_DATA;
	}

	//fixed frame
	parameter_name=std::string(NODE_NAME)+std::string("/fixed_frame");
	
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_fixed_frame=param_string;
	}
	else {
		input_fixed_frame=DEFAULT_FIXED_FRAME;
	}
	
	
	//Exploration area size x
	parameter_name=std::string(NODE_NAME)+std::string("/area_size_x");	
	
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_area_size_x=param_int;
	}
	else {
		input_area_size_x=DEFAULT_AREA_X;
	}

	//Exploration area size y
	parameter_name=std::string(NODE_NAME)+std::string("/area_size_y");	
	
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_area_size_y=param_int;
	}
	else {
		input_area_size_y=DEFAULT_AREA_Y;
	}	



	//Exploration area size z
	parameter_name=std::string(NODE_NAME)+std::string("/area_size_z");	
	
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_area_size_z=param_int;
	}
	else {
		input_area_size_z=DEFAULT_AREA_Z;
	}	
	
	//Cell size for the exploration area
	parameter_name=std::string(NODE_NAME)+std::string("/area_cell_size");	
	
	if(private_nh.getParam(parameter_name,param_double)) {  
		input_area_cell_size=param_double;
	}
	else {
		input_area_cell_size=DEFAULT_AREA_CELL_SIZE;
	}	
	



	ROS_INFO("The data provided in the roslaunch file is:");
	ROS_INFO("Source position: (%f,%f,%f)",input_source_pos_x,input_source_pos_y,input_source_pos_z);
	ROS_INFO("environment file location: %s",input_environment_data.c_str());
	ROS_INFO("Area size (%d,%d,%d) - with cell %f",input_area_size_x,input_area_size_y,input_area_size_z,input_area_cell_size);
	



}



visualization_msgs::MarkerArray loadEnvironment (std::string file_name,double cell_size,std::string global_frame){

visualization_msgs::MarkerArray array_out;

//open file
FILE *file_ptr;
file_ptr = fopen(file_name.c_str(), "r");
// Counts the number of blocks needed
char ch;
int n_blocks=0;
do {
	ch = getc(file_ptr);
	if (ch=='1') {
		n_blocks++;
	}
}while(ch!=EOF);
fclose(file_ptr);



file_ptr = fopen(file_name.c_str(), "r");

double x_pos,y_pos,z_pos;
x_pos=y_pos=z_pos=0;
int block_idx=0;

array_out.markers.resize(n_blocks);
do {
	ch = getc(file_ptr);
	if (ch=='1' || ch=='0'){

			if(ch=='1'){

				array_out.markers[block_idx].header.frame_id = global_frame;
				array_out.markers[block_idx].header.stamp = ros::Time::now();
				array_out.markers[block_idx].ns = "environment_visualization";
				array_out.markers[block_idx].id = block_idx+2;
				array_out.markers[block_idx].type = visualization_msgs::Marker::CUBE;
				array_out.markers[block_idx].action = visualization_msgs::Marker::ADD;
				array_out.markers[block_idx].pose.position.x = x_pos+cell_size/2;
				array_out.markers[block_idx].pose.position.y = y_pos+cell_size/2;
				array_out.markers[block_idx].pose.position.z = z_pos;
				array_out.markers[block_idx].pose.orientation.x = 0.0;
				array_out.markers[block_idx].pose.orientation.y = 0.0;
				array_out.markers[block_idx].pose.orientation.z = 0.0;
				array_out.markers[block_idx].pose.orientation.w = 1.0;
				array_out.markers[block_idx].scale.x = cell_size;
				array_out.markers[block_idx].scale.y = cell_size;
				array_out.markers[block_idx].scale.z = cell_size;
				array_out.markers[block_idx].color.r = 0.0f;
				array_out.markers[block_idx].color.g = 0.0f;
				array_out.markers[block_idx].color.b = 1.0f;
				array_out.markers[block_idx].color.a = 1.0;
				block_idx++;
				
			}
			y_pos=y_pos+cell_size;
			
	}

	else if (ch==';') {
			x_pos=0;
			y_pos=0;
			z_pos=z_pos+cell_size;
			ch = getc(file_ptr);
	}
	else if (ch == '\n' || ch == '\r') {
			y_pos=0;
			x_pos=x_pos+cell_size;
	}
} while(ch!=EOF);

fclose(file_ptr);
return array_out;
}


