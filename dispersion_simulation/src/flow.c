#include "flow.h"
#include "flow_reader.h"
#include <stdlib.h>
#include <math.h>



// Initialize the flow structure
void flow_init( struct sFlow *flow,int area_size_x, int area_size_y, int area_size_z, double area_cell_size) {
	flow->cells_count.x = 0;
	flow->cells_count.y = 0;
	flow->cells_count.z = 0;//3d
	flow->cells_size.x = area_cell_size; // sepid     0.0625;
	flow->cells_size.y = area_cell_size; // sepid     0.0625;
	flow->cells_size.z = area_cell_size; // sepid     0.0625;//3d
	
	//flow->r=alloc_data(area_size_x, area_size_y, area_size_z);
	flow->u=arr3dAlloc(area_size_x, area_size_y, area_size_z);
	flow->v=arr3dAlloc(area_size_x, area_size_y, area_size_z);
	flow->w=arr3dAlloc(area_size_x, area_size_y, area_size_z);
	
	flow->max_x=area_size_x;
	flow->max_y=area_size_y;
	flow->max_z=area_size_z;

	//flow->u=malloc(area_size_x*area_size_y*area_size_z*sizeof(double));
	//flow->v=malloc(area_size_x*area_size_y*area_size_z*sizeof(double));
	//flow->w=malloc(area_size_x*area_size_y*area_size_z*sizeof(double));
}

void flow_set_uniform(struct sFlow *flow, double u, double v, double w) {
	flow->cells_count.x = flow->max_x;
	flow->cells_count.y =flow->max_y;
	flow->cells_count.z = flow->max_z; //3d

int z;
for (z = 0; z < flow->cells_count.z; z++) {
	int x;
	for (x = 0; x < flow->cells_count.x; x++) {
		int y;
		for (y = 0; y < flow->cells_count.y; y++) {
			flow->u[x][y][z] = u;
			flow->u[x][y][z] = v;//3d
			flow->w[x][y][z] = w;
			}
		}
	}
}

void flow_set_fancy(struct sFlow *flow) {
	flow->cells_count.x =flow->max_x;// FLOW_MAX_COUNT_X;
	flow->cells_count.y = flow->max_y;//FLOW_MAX_COUNT_Y;


int z;
for (z = 0; z < flow->cells_count.z; z++) {
	int x;
	for (x = 0; x < flow->cells_count.x; x++) {
		int y;
		for (y = 0; y < flow->cells_count.y; y++) {
			//flow->u[x][y] = sin((double)x / 10.);
			flow->u[x][y][z] = sin((double)x / 10.) * 0.5 + 1.0;
			flow->w[x][y][z] = cos((double)x / 10.);
			}
		}
	}
}




void flow_read(struct sFlow *flow, char *file_u, char *file_v, char *file_w, int flagFirstTime) { //3d
	
	struct sFlowReader fr;
	flow_reader_init(&fr, flow, flagFirstTime);

	flow_reader_read(&fr, file_u, flow->u);

	flow_reader_read(&fr, file_w, flow->w);

	flow_reader_read(&fr, file_v, flow->v);//3d
	

}

void flow_get(struct sFlow *flow, double x, double y, double z) { //3d
	flow->result.u = 0;
	flow->result.v = 0; //3d
	flow->result.w = 0;

	double xd = x / flow->cells_size.x;
	double yd = y / flow->cells_size.y;
	double zd = z / flow->cells_size.z; //3d
	int xi = (int)floor(xd);
	int yi = (int)floor(yd);
	int zi = (int)floor(zd); //3d
	xd -= xi;
	yd -= yi;
	zd -= zi; //3d

	if ((xi < 0) || (yi < 0) || (xi + 1 >= flow->cells_count.x) || (yi + 1 >= flow->cells_count.y)) {
		return;
	}

	if ((flow->u[xi][yi][zi] > 900) || (flow->u[xi+1][yi][zi] > 900) || (flow->u[xi+1][yi+1][zi] > 900) || (flow->u[xi][yi+1][zi] > 900)) {
		return;
	}
	if ((flow->w[xi][yi][zi] > 900) || (flow->w[xi+1][yi][zi] > 900) || (flow->w[xi+1][yi+1][zi] > 900) || (flow->w[xi][yi+1][zi] > 900)) {
		return;
	}

	flow->result.u += flow->u[xi][yi][zi] * (1 - xd) * (1 - yd) * (1 - zd);
	flow->result.u += flow->u[xi][yi][zi+1] * (1 - xd) * (1-yd) * zd;
	flow->result.u += flow->u[xi][yi+1][zi] * (1 - xd) * yd * (1 - zd);
	flow->result.u += flow->u[xi][yi+1][zi+1] * (1 - xd) * yd * zd;
	flow->result.u += flow->u[xi+1][yi][zi] * xd * (1 - yd) * (1 - zd);
	flow->result.u += flow->u[xi+1][yi][zi+1] * xd * (1 - yd) * zd;
	flow->result.u += flow->u[xi+1][yi+1][zi] * xd * yd * (1 - zd);
	flow->result.u += flow->u[xi+1][yi+1][zi+1] * xd * yd * zd;
	
	flow->result.w += flow->w[xi][yi][zi] * (1 - xd) * (1 - yd) * (1 - zd);
	flow->result.w += flow->w[xi][yi][zi+1] * (1 - xd) * (1-yd) * zd;
	flow->result.w += flow->w[xi][yi+1][zi] * (1 - xd) * yd * (1 - zd);
	flow->result.w += flow->w[xi][yi+1][zi+1] * (1 - xd) * yd * zd;
	flow->result.w += flow->w[xi+1][yi][zi] * xd * (1 - yd) * (1 - zd);
	flow->result.w += flow->w[xi+1][yi][zi+1] * xd * (1 - yd) * zd;
	flow->result.w += flow->w[xi+1][yi+1][zi] * xd * yd * (1 - zd);
	flow->result.w += flow->w[xi+1][yi+1][zi+1] * xd * yd * zd;

	flow->result.v += flow->v[xi][yi][zi] * (1 - xd) * (1 - yd) * (1 - zd);
	flow->result.v += flow->v[xi][yi][zi+1] * (1 - xd) * (1-yd) * zd;
	flow->result.v += flow->v[xi][yi+1][zi] * (1 - xd) * yd * (1 - zd);
	flow->result.v += flow->v[xi][yi+1][zi+1] * (1 - xd) * yd * zd;
	flow->result.v += flow->v[xi+1][yi][zi] * xd * (1 - yd) * (1 - zd);
	flow->result.v += flow->v[xi+1][yi][zi+1] * xd * (1 - yd) * zd;
	flow->result.v += flow->v[xi+1][yi+1][zi] * xd * yd * (1 - zd);
	flow->result.v += flow->v[xi+1][yi+1][zi+1] * xd * yd * zd;
}
/*
double ***alloc_data(int xlen, int ylen, int zlen)
{
    double ***p;
    size_t i, j;

    if ((p = malloc(xlen * sizeof *p)) == NULL) {
        perror("malloc 1");
        return NULL;
    }

    for (i=0; i < xlen; ++i)
        p[i] = NULL;

    for (i=0; i < xlen; ++i)
        if ((p[i] = malloc(ylen * sizeof *p[i])) == NULL) {
            perror("malloc 2");
            free_data(p, xlen, ylen);
            return NULL;
        }

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            p[i][j] = NULL;

    for (i=0; i < xlen; ++i)
        for (j=0; j < ylen; ++j)
            if ((p[i][j] = malloc(zlen * sizeof *p[i][j])) == NULL) {
                perror("malloc 3");
                free_data(p, xlen, ylen);
                return NULL;
            }

    return p;
}


void free_data(double ***data, int xlen, int ylen)
{
    size_t i, j;

    for (i=0; i < xlen; ++i) {
        if (data[i] != NULL) {
            for (j=0; j < ylen; ++j)
                free(data[i][j]);
            free(data[i]);
        }
    }
    free(data);
}*/

double*** arr3dAlloc(const int ind1, const int ind2, const int ind3)
{
  int i;
  int j;
  double*** array = (double***) malloc( (ind1 * sizeof(double*)) + (ind1*ind2 * sizeof(double**)) + (ind1*ind2*ind3 * sizeof(double)) );
  for(i = 0; i < ind1; ++i) {
    array[i] = (double**)(array + ind1) + i * ind2;
    for(j = 0; j < ind2; ++j) {
      array[i][j] = (double*)(array + ind1 + ind1*ind2) + i*ind2*ind3 + j*ind3;
    }
  }
  return array;
}
