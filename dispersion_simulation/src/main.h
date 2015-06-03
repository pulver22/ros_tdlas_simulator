#include "foamToFilament.h"
#include "utility.h"
#include "algorithm.h"
#include "global.h"
#include "configuration.h"
#include "mtwist.h"
#include "filament.h"
#include <fstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
//#include <msgs_and_srvs/SensorPosition.h>
#include <msgs_and_srvs/SensorPosition2.h>
#include "Filamentproperties.h"




#define DEFAULT_SNAPSHOTS					100

#define DEFAULT_SOURCE_POS_X				0
#define DEFAULT_SOURCE_POS_Y				0
#define DEFAULT_SOURCE_POS_Z				0.5


#define	DEFAULT_AREA_X						31
#define	DEFAULT_AREA_Y						16
#define	DEFAULT_AREA_Z						6
#define	DEFAULT_AREA_CELL_SIZE				1

#define	DEFAULT_GAS_TYPE					METHANE_ID
#define	DEFAULT_DELTA_T						0.3
#define	DEFAULT_WIND_DATA					"/home/victor/windData/single_obstacle/single_obstacle0."
//#define	DEFAULT_WIND_DATA					"/home/victor/ros_catkin/odour_simulation_ws/src/dispersion_simulation/CSV/Velocity0."
#define	DEFAULT_FILAMENT_NUMBER				300
#define	DEFAULT_FIXED_FRAME					"/map"

#define	NODE_NAME 							"dispersal_simulation"



double		input_source_pos_x;
double		input_source_pos_y;
double		input_source_pos_z;


double			input_area_cell_size;
int			input_area_size_x;
int 		input_area_size_y;
int 		input_area_size_z;


int			input_snapshots;
int			input_gas_type;
double		input_delta_t;
std::string	input_wind_data;
int			input_filament_number;
std::string	input_fixed_frame;

void 		loadNodeParameters(ros::NodeHandle private_nh);
