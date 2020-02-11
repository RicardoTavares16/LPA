#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BUFFER_SIZE 32

typedef struct vertex {
	int x;
	int y;
} vertex;

typedef struct edge {
	vertex a;
	vertex b;
} edge;

int check_point_match(edge a, edge b) { //checks if any of the vertices from the edges match
	int x1 = a.a.x;
	int y1 = a.a.y;
	int x2 = a.b.x;
	int y2 = a.b.y;
	int x3 = b.a.x;
	int y3 = b.a.y;
	int x4 = b.b.x;
	int y4 = b.b.y;

	if (x1 == x3 && y1 == y3) return 1;
	else if (x1 == x4 && y1 == y4) return 1;
	else if (x2 == x3 && y2 == y3) return 1;
	else if (x2 == x4 && y2 == y4) return 1;
	else return 0;
}

double determinant(double a, double b, double c, double d) {
	return a*d - b*c;
}

bool check_intersection(edge a, edge b) {

	double x1, x2, x3, x4, y1, y2, y3, y4, ixOut, iyOut, xnom, ynom;
	double detL1, detL2, x1mx2, x3mx4, y1my2, y3my4, denom;

	x1 = a.a.x;
	y1 = a.a.y;
	x2 = a.b.x;
	y2 = a.b.y;
	x3 = b.a.x;
	y3 = b.a.y;
	x4 = b.b.x;
	y4 = b.b.y;

	detL1 = determinant(x1, y1, x2, y2);
	detL2 = determinant(x3, y3, x4, y4);

	x1mx2 = x1 - x2;

	x3mx4 = x3 - x4;

	y1my2 = y1 - y2;

	y3my4 = y3 - y4;

	xnom = determinant(detL1, x1mx2, detL2, x3mx4);
	ynom = determinant(detL1, y1my2, detL2, y3my4);

	denom = determinant(x1mx2, y1my2, x3mx4, y3my4);

	if(denom == 0.0) return false;

	ixOut = xnom / denom;
	iyOut = ynom / denom;

	if(!isfinite(ixOut) || !isfinite(iyOut)) return false;

	return true;
}

int main() {
	char stdin_buffer[BUFFER_SIZE], *buffer;
	int i, j, number_vertices, number_edges;
	vertex *vertices;
	edge *edges;

	// number vertices
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_vertices = (int) strtol(buffer, &buffer, 10);

	//allocate space for the vertices
	vertices = (vertex *) malloc(number_vertices * sizeof(vertex));

	// vertices coords
	for (i = 0; i < number_vertices; ++i) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		vertices[i].x = (int) strtol(buffer, &buffer, 10);
		vertices[i].y = (int) strtol(buffer, &buffer, 10);
	}

	// number of edges
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_edges = (int) strtol(buffer, &buffer, 10);

	//allocate space for the edges
	edges = (edge *) malloc(number_edges * sizeof(edge));

	// edges vertices
	for (i = 0; i < number_edges; ++i) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		edges[i].a = vertices[(int) strtol(buffer, &buffer, 10)];
		edges[i].b = vertices[(int) strtol(buffer, &buffer, 10)];
	}

	//n^2 function to test all intersections
	for (i = 0; i < number_edges - 1; i++) {
		for (j = i + 1; j < number_edges; j++) {
			if (check_point_match(edges[i], edges[j])) continue;

			if (check_intersection(edges[i], edges[j])) {
				printf("Got intersection with edges a[(%d,%d),(%d,%d)] & b[(%d,%d),(%d,%d)]\n",
				       edges[i].a.x, edges[i].a.y, edges[i].b.x, edges[i].b.y,
				       edges[j].a.x, edges[j].a.y, edges[j].b.x, edges[j].b.y);
			}
		}
	}
	return 0;
}



