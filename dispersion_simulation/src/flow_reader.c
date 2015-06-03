#include "flow_reader.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Initialize the flow_reader structure
void flow_reader_init(struct sFlowReader *fr, struct sFlow *flow, int flagFirstTime) {
	fr->flow = flow;
	fr->item.col = 0;    //??
	fr->item.row = 0;
	fr->item.page = 0;
	if(flagFirstTime)
		fr->item.value = 0;
}

// Called every now and then to update everything
void flow_reader_read(struct sFlowReader *fr, char *filename, double ***array) {
	// Empty the array
	int z;
	for (z = 0; z < fr->flow->max_x; z++) {
		int x;
		for (x = 0; x < fr->flow->max_y; x++) {
			int y;
			for (y = 0; y < fr->flow->max_z; y++) {
				array[x][y][z] = 0.;   ///why 0. ???
			}
		}
	}
	fr->flow->cells_count.x = 0;
	fr->flow->cells_count.y = 0;
	fr->flow->cells_count.z = 0;

	// Open the file
	//printf("%s \n", filename);
	fr->filedes = open(filename, O_RDONLY);
	fr->parser.row = 0;
	fr->parser.col = 0;
	fr->parser.page = 0;

	fr->parser.state = cFlowReaderState_Default;
//sepid
	fr->parser.bufferpos = 0;
	fr->parser.bufferlen = read(fr->filedes, fr->parser.buffer, sizeof(fr->parser.buffer));
	

	// Read all values
	while (flow_reader_next_item(fr)) {
		if ((fr->item.row >= fr->flow->max_x) || (fr->item.col >= fr->flow->max_y)|| (fr->item.page >= fr->flow->max_z)) {
			printf("Flow array too small! Requested item was (%d, %d, %d)\n limit is (%d,%d,%d)", fr->item.row, fr->item.col,fr->item.page,fr->flow->max_x,fr->flow->max_y,fr->flow->max_z);
			exit(1);
		}
		if (fr->item.row >= fr->flow->cells_count.x) {
			fr->flow->cells_count.x = fr->item.row + 1;
		}
		if (fr->item.col >= fr->flow->cells_count.y) {
			fr->flow->cells_count.y = fr->item.col + 1;
		}
		if (fr->item.page >= fr->flow->cells_count.z) {
			fr->flow->cells_count.z = fr->item.page + 1;
		}
		array[fr->item.row][fr->item.col][fr->item.page] = fr->item.value;
		
	}
	
	// Close the file
	close(fr->filedes);
	
}

int flow_reader_next_item(struct sFlowReader *fr) {
	char item[128];
	int itemnw = 0;

	while (1) {
		while (fr->parser.bufferpos < fr->parser.bufferlen) {
			char ch = fr->parser.buffer[fr->parser.bufferpos++]; //++ in array char?? ch= 1,2,3.....
			
			if (fr->parser.state == cFlowReaderState_BeginningOfRow) {
				if (ch == '\n' || ch == '\r') {
				} else if (ch == '\t' || ch == ' ') {
				} else if (ch == '#') {
					fr->parser.state = cFlowReaderState_Comment;
				} else if (ch == ';'){
					fr->item.col = fr->parser.col;
					fr->item.row = fr->parser.row;
					fr->item.page = fr->parser.page;//3d
					//item[itemnw] = 0;
					//fr->item.value = strtod(item, 0);
					fr->parser.col = 0;
					fr->parser.row = 0;
					fr->parser.page++;
					fr->parser.state = cFlowReaderState_BeginningOfRow;
				}else {
					item[0] = ch;
					itemnw = 1;
					fr->parser.state = cFlowReaderState_Default;
				}
			} else if (fr->parser.state == cFlowReaderState_BeginningOfCol) {
				if (ch == '\n' || ch == '\r') {
					fr->parser.state = cFlowReaderState_BeginningOfRow;
				} else if (ch == '\t' || ch == ' ') {
				} else if (ch == '#') {
					fr->parser.state = cFlowReaderState_Comment;
				} else {
					item[0] = ch;
					itemnw = 1;
					fr->parser.state = cFlowReaderState_Default;
				}
			} else if (fr->parser.state == cFlowReaderState_Comment) {
				if (ch == '\n' || ch == '\r') {
					fr->parser.state = cFlowReaderState_BeginningOfRow;
				}
			} else {
				if (ch == '\n' || ch == '\r') {
					fr->item.col = fr->parser.col;
					fr->item.row = fr->parser.row;
					fr->item.page = fr->parser.page;//3d
					item[itemnw] = 0;
					fr->item.value = strtod(item, 0);
					fr->parser.col = 0;
					fr->parser.row++;
					fr->parser.state = cFlowReaderState_BeginningOfRow;
					return 1;
				} else if (ch == '\t' || ch == ' ') {
					fr->item.col = fr->parser.col;
					fr->item.row = fr->parser.row;
					fr->item.page = fr->parser.page;//3d
					item[itemnw] = 0;
					fr->item.value = strtod(item, 0);
					fr->parser.col++;
					fr->parser.state = cFlowReaderState_BeginningOfCol;
					return 1;
				} 	else if (ch == '#') {
					fr->item.col = fr->parser.col;
					fr->item.row = fr->parser.row;
					fr->item.page = fr->parser.page;//3d
					item[itemnw] = 0;
					fr->item.value = strtod(item, 0);
					fr->parser.col = 0;
					fr->parser.row++;
					fr->parser.state = cFlowReaderState_Comment;
					return 1;
				} else {
					if (itemnw < 128) {
						item[itemnw] = ch;
						itemnw++;
					}
				}
			}
		}

		// Read new chunk
		fr->parser.bufferpos = 0;
		fr->parser.bufferlen = read(fr->filedes, fr->parser.buffer, sizeof(fr->parser.buffer));
		if (fr->parser.bufferlen == 0) {
			break;
		}
	}

	if (fr->parser.state == cFlowReaderState_Default) {
		fr->item.col = fr->parser.col;
		fr->item.row = fr->parser.row;
		fr->item.page = fr->parser.page;//3d
		item[itemnw] = 0;
		fr->item.value = strtod(item, 0);
		fr->parser.state = cFlowReaderState_BeginningOfRow;
		return 1;
	}

	// at end of file
	return 0;
}
