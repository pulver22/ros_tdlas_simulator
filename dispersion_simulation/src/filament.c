#ifdef __cplusplus
 extern "C" {
 #endif

#include "filament.h"
#include "global.h"
#include "mtwist.h"
#include <stdlib.h>
//#include"Filamentproperties.h"





void filament_init(struct sFilament *f, double x, double y, double z,int z_max) {//3d
	f->configuration.stddev = 0.5;
	f->max_z=z_max;
	f->configuration.growthgamma = 4e-4; //4e-7
	f->state.x = x;
	f->state.y = y;
	f->state.z = z;
	f->state.width = 0.05;//0.01m
	f->state.valid = 1;

}




void filament_step(struct sFilament *f, double simulation_step) {

  f->value.gas=density;
  f->value.air=1.22521;
  f->value.g=9.8;

	//calculation of accleration:
	f->value.a = f->value.g * ( f->value.air - f->value.gas ) / ( f->value.gas + f->value.air );

	//acclelration=0
	//f->value.a =-9.8;

	//f->value.a = f->value.g * (( f->value.air / f->value.gas) -1 );

	// Advection
	flow_get(&algorithm.flow, f->state.x, f->state.y, f->state.z); //3d
	f->state.x += algorithm.flow.result.u * simulation_step;
	f->state.y += algorithm.flow.result.w * simulation_step;

	//acclelration in z-axis
	f->state.z += ((0.5) * (f->value.a) * (pow(simulation_step,2)) +  algorithm.flow.result.v * simulation_step);


	if (! environment_position_valid(&algorithm.environment, f->state.x, f->state.y,f->state.z)) { 
	
	//boundries of ceiling and floor.
	if(f->state.z>f->max_z) {
		f->state.z=f->max_z-(mt_drand() * 0.25);
		}
	if(f->state.z<0) {
		f->state.z=0+(mt_drand()* 0.25);
		}

		//f->state.valid = 0;
		return;
	}

	// Stochastic process (vmi)
	double stddev = f->configuration.stddev * simulation_step;
	double newpos_x = f->state.x + mt_drand() * stddev * 2 - stddev;
	double newpos_y = f->state.y + mt_drand() * stddev * 2 - stddev;
	double newpos_z = f->state.z + mt_drand() * stddev * 2 - stddev; //3d

	// Set the new filament position
	if (environment_position_valid(&algorithm.environment, newpos_x, newpos_y, newpos_z)) {   

		f->state.x = newpos_x;
		f->state.y = newpos_y;
		f->state.z = newpos_z;

	}

	// Filament growth
	f->state.width += 0.5 * f->configuration.growthgamma / f->state.width;

}

#ifdef __cplusplus
 }
 #endif
