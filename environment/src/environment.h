#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <cmath>
#include "SourceLoc.h"

#define		NODE_NAME 							"environment"
#define 	DEFAULT_SOURCE_POS_X				0
#define 	DEFAULT_SOURCE_POS_Y				0
#define 	DEFAULT_SOURCE_POS_Z				0.5
#define		DEFAULT_ENVIRONMENT_DATA			"/home/victor/windData/environments/original"
#define		DEFAULT_FIXED_FRAME					"/map2"

#define	DEFAULT_AREA_X						31
#define	DEFAULT_AREA_Y						16
#define	DEFAULT_AREA_Z						6
#define	DEFAULT_AREA_CELL_SIZE				1


double		input_source_pos_x;
double		input_source_pos_y;
double		input_source_pos_z;
std::string	input_fixed_frame;
std::string input_environment_data;

double		input_area_cell_size;
int			input_area_size_x;
int 		input_area_size_y;
int 		input_area_size_z;



void	loadNodeParameters(ros::NodeHandle);
visualization_msgs::MarkerArray loadEnvironment(std::string,double,std::string);






