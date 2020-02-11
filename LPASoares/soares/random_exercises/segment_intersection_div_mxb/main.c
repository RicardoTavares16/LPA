#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

typedef struct vertex {
	int x;
	int y;
} vertex;

typedef struct edge {
	vertex a;
	vertex b;
} edge;

int check_vertex_match(edge a, edge b) { //checks if any of the vertices from the edges match

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

int check_intersection(edge a, edge b) {

	if (check_vertex_match(a, b)) return 0;

	long double slope_a, slope_b, ta, tb, intercept_a, intercept_b, denominator;

	int x1 = a.a.x;
	int y1 = a.a.y;
	int x2 = a.b.x;
	int y2 = a.b.y;
	int x3 = b.a.x;
	int y3 = b.a.y;
	int x4 = b.b.x;
	int y4 = b.b.y;

	denominator = ((x4 - x3) * (y1 - y2)) - ((x1 - x2) * (y4 - y3));

	if (denominator == 0) { //means that both lines are vertical or horizontal (we have to check if they are on top)

		//vertical
		if (x1 == x2) {
			if ((y3 > y2) || (y1 > y4)) {
				return 0;
			}
			return 1;
		}
			//horizontal
		else if (y1 == y2) {
			if ( (x3 > x2) || (x1 > x4)) {
				return 0;
			}
			return 1;
		}
			//oblique
		else {
			// since they are not vertical nor horizontal, we can use the slope the check if the line segments are collinear
			//by calculating their b
			slope_a = (long double)(y2 - y1) / (x2 - x1);
			slope_b = (long double)(y4 - y3) / (x4 - x3);
			intercept_a = y1 - slope_a * x1;
			intercept_b = y3 - slope_b * x3;
			//if they have the same b, they are the same line, all we need to do is verify if the segments are withing each other
			if (intercept_a == intercept_b) {
				if ((y3 == (slope_a * x3) + intercept_a) && x3 > x1 && x3 < x2) return 1;
			}
			return 0;
		}
	} else {
		if (check_vertex_match(a, b)) return 0;
		ta = (((y3 - y4) * (x1 - x3)) + ((x4 - x3) * (y1 - y3))) / denominator;
		tb = (((y1 - y2) * (x1 - x3)) + ((x2 - x1) * (y1 - y3))) / denominator;
		if (ta >= 0 && ta <= 1 && tb >= 0 && tb <= 1) return 1;
		else return 0;
	}
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

			//if intersection found function check intersection returns 1
			if (check_intersection(edges[i], edges[j])) {
				printf("Got intersection with edges a[(%d,%d),(%d,%d)] & b[(%d,%d),(%d,%d)]\n",
				       edges[i].a.x, edges[i].a.y, edges[i].b.x, edges[i].b.y,
				       edges[j].a.x, edges[j].a.y, edges[j].b.x, edges[j].b.y);
			}
		}
	}
	return 0;
}
