#include "hit_rate.h"
#include <stdlib.h>
#include <math.h>

// Initialize the flow structure
void hit_rate_init(struct sHitRate *hit_rate,int max_rate_x,int max_rate_y,int max_rate_z, double cell_size) {
	hit_rate->cells_count.x = max_rate_x;
	hit_rate->cells_count.y = max_rate_y;
	hit_rate->cells_count.z = max_rate_z; //3d

	hit_rate->cells_size.x = cell_size;
	hit_rate->cells_size.y = cell_size;
	hit_rate->cells_size.z = cell_size;//3d

	int x;
	int y;
	int z;//3d
	
	hit_rate->value=arr3dAlloc(max_rate_x,max_rate_y,max_rate_z);
for (z = 0; z < hit_rate->cells_count.z; z++) { //3d
	for (x = 0; x < hit_rate->cells_count.x; x++) {
		for (y = 0; y < hit_rate->cells_count.y; y++) {
			hit_rate->value[x][y][z] = 0; //3d
			}		
		}
	}
}

int hit_rate_add(struct sHitRate *hit_rate, double x, double y, double z, double weight) { //3d
	double xd = x / hit_rate->cells_size.x;
	double yd = y / hit_rate->cells_size.y;
	double zd = z / hit_rate->cells_size.z;//3d

	int xi = (int)floor(xd + hit_rate->cells_size.x/2);		// +0.5
	int yi = (int)floor(yd + hit_rate->cells_size.x/2);
	int zi = (int)floor(zd + hit_rate->cells_size.x/2);//3d
	if (xi < 0) {
		return 0;
	}
	if (yi < 0) {
		return 0;
	}
	if (zi < 0) { //3d
		return 0;
	}
	if (xi >= hit_rate->cells_count.x) {
		return 0;
	}
	if (yi >= hit_rate->cells_count.y) {
		return 0;
	}
	if (zi >= hit_rate->cells_count.z) {//3d
		return 0;
	}
	hit_rate->value[xi][yi][zi] += weight;

	return 1;
}

void hit_rate_rescale(struct sHitRate *hit_rate, double factor) {
	int x;
	int y;
	int z;
	for (x = 0; x < hit_rate->cells_count.x; x++) {
		for (y = 0; y < hit_rate->cells_count.y; y++) {
			for (z = 0; z < hit_rate->cells_count.z; z++) {
			hit_rate->value[x][y][z] *= factor;
			}
		}
	}
}

void hit_rate_save(struct sHitRate *hit_rate, char *filename) {
	FILE *f = fopen(filename, "w");
	fwrite(hit_rate->value, sizeof(double), hit_rate->cells_count.x*hit_rate->cells_count.y, f);
	fclose(f);
}
