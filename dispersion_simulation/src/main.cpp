
#include "main.h"
using namespace std;

//---------------service response----------------------//
  bool pos(msgs_and_srvs::SensorPosition2::Request  &req,
         msgs_and_srvs::SensorPosition2::Response &res )
{
	int size = req.x.size();
	//cout << "Inside service " << endl;
	for(int i =0; i < size; i++){
	    
	//concentration=concentration at(x,y,z):
	res.odor_r[i]=concentration(req.x[i], req.y[i], req.z[i], input_area_cell_size);
	//cout << req.x[i] << " " << req.y[i]<< " " << req.z[i]<<" " << res.odor_r[i] << endl;;
	//res.odor_r1=concentration(req.x_r1, req.y_r1, req.z_r1);
	//res.odor_r2=concentration(req.x_r2, req.y_r2, req.z_r2);
	}


  return true;
}


//====================================================================================
//
//			M   A   I   N       L   O   O   P 
//
//====================================================================================



int main(int argc, char **argv) {

	//(1) Creates a log file. 
	ofstream myfile;
	myfile.open ("pos.log");
	configuration_init();
	configuration_parse_commandline(argc, argv);

	//(2) Initialize the random number generator
	mt_goodseed();

	//(3) Creates folders for videos and results
	mkdir("results", 0755);
	mkdir("video", 0755);

	//(4) Initializes and loads the node configuration
	ros::init(argc, argv, NODE_NAME);
	ros::NodeHandle n;
	loadNodeParameters(n);

//	input_area_size_x=61;
//input_area_size_y=61;
//input_area_size_z=61;
	//(5) Initializes and starts the gas dispersion simulation
	

	algorithm_init(input_wind_data.c_str(),input_snapshots,input_filament_number,input_area_size_x,input_area_size_y,input_area_size_z,input_area_cell_size,input_source_pos_x,input_source_pos_y,input_source_pos_z);



	//(6) Loads the plume constants w.r.t. the selected gas
	
	plume_start();
	







	//Plume publisher
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("dispersion_visualization", 1);
	ros::ServiceServer service = n.advertiseService("odor_value", pos);
 	


	ros::Rate r(1/input_delta_t);

	bool flow=false;

  while (ros::ok())
  {
	  
	
	//chemical id publisher
	//msgs_and_srvs::ChemicalValue chemical;
	//chemical.id=input_gas_type;
	density=Chemicalvalue[input_gas_type];

	//Service respone (hit_rate.value)
	


    //marker points for filaments
    visualization_msgs::Marker draw;
    draw.header.frame_id  = input_fixed_frame;
    draw.header.stamp =ros::Time::now();
    draw.ns = "plume_simulation";
    draw.action = visualization_msgs::Marker::ADD;
    draw.pose.orientation.w = 1.0;
    draw.id = 0;
    draw.type = visualization_msgs::Marker::POINTS;
    draw.color.a = 1;

//Calculating the hit_rate
if(flow==true){
	
	algorithm_hit_rate_calculate(algorithm.source.x - 0.5, algorithm.source.y - 0.5,algorithm.source.z-0.5, 
                                     algorithm.source.x + 0.5, algorithm.source.y + 0.5,algorithm.source.z+0.5);
}   flow=true;



	for(int k=0;k<algorithm.marker.counter*input_filament_number; k++)
		{
	//points

 	geometry_msgs::Point p;

	//color of points	
	std_msgs::ColorRGBA c;

	//width of points
	draw.scale.x = algorithm.marker.width[k];
	draw.scale.y = algorithm.marker.width[k];
	draw.scale.z = algorithm.marker.width[k];

	//assigning the point positions
	p.x =algorithm.marker.x[k];
	p.y = algorithm.marker.y[k];
	p.z = algorithm.marker.z[k];

	//c.g=1;
        c.a=1;

	//uncomment these two lines to visualize color of filaments according to increasing width
	red=algorithm.marker.colour[k];
	color_width(&red, &green, &blue); c.r=red; c.g=green; c.b=blue;

	//uncomment these two lines to visualizecolor of filaments according to concentration
	//red = concentration(p.x, p.y, p.z);
	//color_concentration(&red, &green, &blue); c.r=red; c.g=green; c.b=blue;

		
		draw.colors.push_back(c);
		draw.points.push_back(p);

		}

	//log of plume height
	myfile << algorithm.marker.z[0] <<"\n";

	//Publishing the points
	marker_pub.publish(draw);

	//publishing the chemical value
	//ChemicalValue.publish(chemical);


  r.sleep();	
  ros::spinOnce();

  }

  myfile.close(); 
	return 0;
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

	//Gas type
	parameter_name=std::string(NODE_NAME)+std::string("/gas_type");
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_gas_type=param_int;
	}
	else {
		input_gas_type=DEFAULT_GAS_TYPE;
	}

	//delta_t
	parameter_name=std::string(NODE_NAME)+std::string("/delta_t");
	if(private_nh.getParam(parameter_name,param_double)) {  
		input_delta_t=param_double;
	}
	else {
		input_delta_t=DEFAULT_DELTA_T;
	}
	
	
	//wind files
	parameter_name=std::string(NODE_NAME)+std::string("/wind_data");
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_wind_data=param_string;
	}
	else {
		input_wind_data=DEFAULT_WIND_DATA;
	}

	//filaments
	parameter_name=std::string(NODE_NAME)+std::string("/filaments");
	
	
	if(private_nh.getParam(parameter_name,param_int)) {  
		input_filament_number=param_int;
	}
	else {
		input_filament_number=DEFAULT_FILAMENT_NUMBER;
	}



	//fixed frame
	parameter_name=std::string(NODE_NAME)+std::string("/fixed_frame");
	
	if(private_nh.getParam(parameter_name,param_string)) {  
		input_fixed_frame=param_string;
	}
	else {
		input_fixed_frame=DEFAULT_FIXED_FRAME;
	}
	
	//snapshots
	parameter_name=std::string(NODE_NAME)+std::string("/snapshots");

	if(private_nh.getParam(parameter_name,param_int)) {  
		input_snapshots=param_int;
	}
	else {
		input_snapshots=DEFAULT_SNAPSHOTS;
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
	ROS_INFO("Gas type: %d",input_gas_type);
	ROS_INFO("Delta time: %f",input_delta_t);
	ROS_INFO("wind file location: %s",input_wind_data.c_str());
	ROS_INFO("Number of filaments: %d",input_filament_number);
	ROS_INFO("Fixed frame: %s",input_fixed_frame.c_str());
	ROS_INFO("Snapshots: %d",input_snapshots);
	ROS_INFO("Area size (%d,%d,%d) - with cell %f",input_area_size_x,input_area_size_y,input_area_size_z,input_area_cell_size);
	



}


