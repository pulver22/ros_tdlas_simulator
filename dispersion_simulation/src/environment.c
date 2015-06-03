#include "environment.h"
#include <stdlib.h>
#include <math.h>

// Initializes the environment.
void environment_init(struct sEnvironment *environment,int max_x,int max_y,int max_z) {
	
	environment->lines.count = 0;
	environment->rectangles.count = 0;

	environment->arena.width = max_x; //sepid 18;
	environment->arena.height = max_y; //sepid 10;
	environment->arena.length = max_z;


	environment_lines_add(environment, 0, 0, 16, 0);
	environment_lines_add(environment, 16, 0, 16, 4);
	environment_lines_add(environment, 0, 0, 0, 4);
	environment_lines_add(environment, 0, 4, 16, 4);
	
	environment_lines_add(environment, 6, 1.2, 6, 2);
	environment_lines_add(environment, 6, 2, 8, 2);
	environment_lines_add(environment, 8, 2, 8, 1.2);
	environment_lines_add(environment, 8, 1.2, 6, 1.2);
	
	environment_rectangles_add(environment, 6, 1.2, 8, 2);
/*
	environment_lines_add(environment, 0, 10, 10, 10);
	environment_lines_add(environment, 18, 1, 18, 2);
	environment_lines_add(environment, 18, 4, 18, 9);
	environment_rectangles_add(environment, 6, 0, 18, 1);
	environment_rectangles_add(environment, 10, 9, 18, 10);
	environment_rectangles_add(environment, 11.5, 4.5, 14.5, 6);
	environment_rectangles_add(environment, 3, 4.5, 8, 7);
	environment_rectangles_add(environment, 3, 4.5, 5, 8);
	environment_rectangles_add(environment, 6, 3.5, 8, 7);*/
}

// Adds a line.
void environment_lines_add(struct sEnvironment *environment, double x1, double y1, double x2, double y2) {
	if (environment->lines.count >= 32) {
		printf("Not enough memory allocated for lines.\n");
		exit(1);
	}

	
	int index = environment->lines.count;
	environment->lines.item[index].x1 = x1;
	environment->lines.item[index].y1 = y1;
	environment->lines.item[index].x2 = x2;
	environment->lines.item[index].y2 = y2;
	environment->lines.count++;
}

// Adds a rectangle.
void environment_rectangles_add(struct sEnvironment *environment, double x1, double y1, double x2, double y2) {
	if (environment->rectangles.count >= 32) {
		printf("Not enough memory allocated for rectangles.\n");
		exit(1);
	}

	int index = environment->rectangles.count;
	environment->rectangles.item[index].x1 = x1;
	environment->rectangles.item[index].y1 = y1;
	environment->rectangles.item[index].x2 = x2;
	environment->rectangles.item[index].y2 = y2;
	environment->rectangles.count++;
}

/*
if ((x < 0) || (y < 0) || (z < 0)|| (x > environment->arena.width) || (y > environment->arena.height)|| (z > environment->arena.length)) {
		return 0;
	}


*/



// Returns whether a point (world coordinates) is valid or not.
int environment_position_valid(struct sEnvironment *environment, double x, double y, double z) {
	// Arena
	if ((z < 0)|| (z >= environment->arena.length-1) || (x >= environment->arena.width-1) || (y >= environment->arena.height-1)) {
		
		return 0;
	}

	// Rectangles
	int i;
	for (i = 0; i < environment->rectangles.count; i++) {
		if ((x > environment->rectangles.item[i].x1) && (y > environment->rectangles.item[i].y1) && (x < environment->rectangles.item[i].x2) && (y < environment->rectangles.item[i].y2)) {
			return 0;
		}
	}

	return 1;
}
