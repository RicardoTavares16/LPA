#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 32

typedef struct vertex {
	int x;
	int y;
} vertex;

typedef struct edge {
	vertex a;
	vertex b;
} edge;

int greater(int a, int b) {if (a >= b) return a; else return b;}

int smaller(int a, int b) {if (a <= b) return a; else return b;}

vertex *get_bounding_box(vertex *box, edge a) {

	box[0].x = smaller(a.a.x, a.b.x);
	box[0].y = smaller(a.a.y, a.b.y);

	box[1].x = greater(a.a.x, a.b.x);
	box[1].y = greater(a.a.y, a.b.y);

	return box;
}

int cross_product(vertex a, vertex b) {
	return a.x * b.y - b.x * a.y;
}

bool bounding_boxes_intercept(vertex *box_a, vertex *box_b){
	return ( (box_a[0].x <= box_b[1].x) && (box_a[1].x >= box_b[0].x) &&
				(box_a[0].y <= box_b[1].y ) && (box_a[1].y >= box_b[0].y) );
}







bool check_point_segment(vertex a, vertex b, vertex c) {
	if (b.x <= greater(a.x, c.x) && b.x >= smaller(a.x, c.x) && b.y <= greater(a.y, c.y) && b.y >= smaller(a.y, c.y)) {
		return true;
	}
	return false;
}

int orientation(vertex a, vertex b, vertex c) {
	int val;
	val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	if (val == 0) return 0;
	else if (val > 0) return 1;
	else return 2;
}

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

int check_intersection(edge a, edge b) {

	if (check_point_match(a, b)) return 0;

	int o1 = orientation(a.a, a.b, b.a);
	int o2 = orientation(a.a, a.b, b.b);
	int o3 = orientation(b.a, b.b, a.a);
	int o4 = orientation(b.a, b.b, a.b);
	if (o1 != o2 && o3 != o4)
		return 1;
	if (o1 == 0 && check_point_segment(a.a, b.a, a.b)) return 1;
	if (o2 == 0 && check_point_segment(a.a, b.b, a.b)) return 1;
	if (o3 == 0 && check_point_segment(b.a, a.a, b.b)) return 1;
	if (o4 == 0 && check_point_segment(b.a, a.b, b.b)) return 1;
	return 0;
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
