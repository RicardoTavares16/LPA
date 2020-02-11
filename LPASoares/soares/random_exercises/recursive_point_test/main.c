#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 32

typedef struct point_2d {
	int x;
	int y;
	bool occupied;
} point_2d;

typedef struct edge {
	int start;
	int end;
} edge;

typedef struct solution {
	point_2d *vertices_location;
	int number_vertices;
	int number_edge_crossings;
} solution;

int compare_points(const void *a, const void *b) {
	int ax, ay, bx, by;
	ax = ((point_2d*)a)->x;
	ay = ((point_2d*)a)->y;
	bx = ((point_2d*)b)->x;
	by = ((point_2d*)b)->y;
	if(ax == bx) {
		return ay - by;
	}
	return ax - bx;
}

int count_permutations = 0;

int
optimize_intersections( point_2d *points, int number_points, int number_vertices, int vertice,
                        int last_vertice_point, edge *edges, int number_edges, solution best_solution) {

	int vertice_point = (last_vertice_point + 1) % number_points;
	int vertice_starting_point = vertice_point;

	do  {

		if (!points[vertice_point].occupied) {
			points[vertice_point].occupied = true;

			printf("Testing vertex %d on point %d\n", vertice, vertice_point);

			if ( vertice + 1 < number_vertices ) {
				optimize_intersections(points, number_points, number_vertices, vertice + 1,
				                       vertice_point, edges, number_edges, best_solution);
			}

			else {
				count_permutations++;
			}

			points[vertice_point].occupied = false;
		}
		vertice_point = (vertice_point + 1) % number_points;
	} while ( (vertice_point != vertice_starting_point ) );
	return 0;
}

int main() {
	char stdin_buffer[BUFFER_SIZE], *buffer;
	int i, number_points, number_edges, number_vertices;
	solution best_solution;

	fgets(stdin_buffer, BUFFER_SIZE , stdin); buffer = stdin_buffer;
	number_points = (int)strtol(buffer, &buffer, 10);

	point_2d points[number_points];

	for (i = 0; i < number_points; ++i) {
		fgets(stdin_buffer, BUFFER_SIZE , stdin); buffer = stdin_buffer;
		points[i].x = (int)strtol(buffer, &buffer, 10);
		points[i].y = (int)strtol(buffer, &buffer, 10);
	}

	qsort(points, (size_t) number_points, sizeof(point_2d), compare_points);

	fgets(stdin_buffer, BUFFER_SIZE , stdin); buffer = stdin_buffer;
	number_vertices = (int)strtol(buffer, &buffer, 10);
	number_edges = (int)strtol(buffer, &buffer, 10);

	best_solution.vertices_location = (point_2d*) malloc (number_vertices * sizeof(point_2d));
	edge edges[number_edges];
	best_solution.number_edge_crossings = (number_edges * number_edges) + 1;
	best_solution.number_vertices = 0;

	for (i = 0; i < number_edges; ++i) {
		fgets(stdin_buffer, BUFFER_SIZE , stdin); buffer = stdin_buffer;
		edges[i].start = (int)strtol(buffer, &buffer, 10);
		edges[i].end = (int)strtol(buffer, &buffer, 10);
	}

	printf("%d\n", optimize_intersections(points, number_points, number_vertices, 0,
	                                      -1, edges, number_edges, best_solution));

	printf("TOTAL NUMBER OF PERMUTATIONS TESTED %d", count_permutations);

	return 0;
}
