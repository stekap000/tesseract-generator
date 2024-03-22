#include "stdio.h"
#include "stdbool.h"

typedef struct {
	int x, y, z, w;
} Point;

int dist(Point p, Point q) {
	return (p.x ^ q.x) + (p.y ^ q.y) + (p.z ^ q.z) + (p.w ^ q.w);
}

int point_index(Point p) {
	return 8*p.x + 4*p.y + 2*p.z + p.w;
}

void generate_vertices() {
	printf("float tesseract_vertices[16*4] = {\n");
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) {
				for(int l = 0; l < 2; ++l) {
					Point p = (Point){i, j, k, l};
					printf("\t%d, %d, %d, %d, // %2d\n", i, j, k, l, point_index(p));
				}	
			}	
		}		
	}
	printf("};\n");
}

void generate_point_indices(Point p0) {
	Point adjacent_points[4] = {
		{p0.x ^ 1, p0.y, p0.z, p0.w},
		{p0.x, p0.y ^ 1, p0.z, p0.w},
		{p0.x, p0.y, p0.z ^ 1, p0.w},
		{p0.x, p0.y, p0.z, p0.w ^ 1},
	};
	
	for(int i = 0; i < 4; ++i) {
		for(int j = i + 1; j < 4; ++j) {
				printf("\t%d, %d, %d,\n",
					   point_index(p0),
					   point_index(adjacent_points[i]),
					   point_index(adjacent_points[j]));
		}
	}
}

void generate_indices() {
	printf("int tesseract_indices[48*3] = {\n");
	for(int i = 0; i < 16; i += 2)
		generate_point_indices((Point){(i&1), (i&2) >> 1, (i&4) >> 2, (i&8) >> 3});
	printf("};\n");
}

int main() {
	generate_vertices();
	generate_indices();

	return 0;
}
