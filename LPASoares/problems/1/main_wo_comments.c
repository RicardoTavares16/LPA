
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
	int a;
	int b;
} edge;

typedef struct vertex {
	int edge[28];
	int edge_count;
	bool seen;
} vertex;

typedef struct solution {
	int vertices_location[81];
	edge edges[28];
	int number_edges;
	int number_edge_crossings;
} solution;

point_2d points[81];
vertex vertices[81];
char intersect[43046721];

solution best_solution;
solution temp_solution;
int number_points, number_vertices, number_edges,  number_points_p2, number_points_p3;

void copy_solution(int number_edge_crossings) {
	int i;

	best_solution.number_edges = temp_solution.number_edges;
	best_solution.number_edge_crossings = number_edge_crossings;

	for (i = 0; i < number_vertices; i++) {
		best_solution.vertices_location[i] = temp_solution.vertices_location[i];
	}
}

int optimize_intersections(int vertex, int last_vertex_point) {
	
	if (vertices[vertex].seen == false) {

		if (vertex < number_vertices - 1) {
			
			if (optimize_intersections(vertex + 1, last_vertex_point)) {				
				return 1;
			}
			else return 0;
		}
		else {
			if (temp_solution.number_edge_crossings == 0) {
				copy_solution(0);
				return 1;
			}

			else {
				copy_solution(temp_solution.number_edge_crossings);
				return 0;
			}
		}
	}
	
	int i, j, temp_local_edges, local_edge_crossing_count, local_edge_count;
	int vertex_point = (last_vertex_point + 1) % number_points;
	int vertex_starting_point = vertex_point;
	int local_edge_crossing_count_begin = temp_solution.number_edge_crossings;

	do {
		if (!points[vertex_point].occupied) {
			points[vertex_point].occupied = true;	
			local_edge_crossing_count = local_edge_crossing_count_begin;
			local_edge_count = 0;
			temp_local_edges = temp_solution.number_edges;
			for (i = 0; i < vertices[vertex].edge_count; i++) {
				for (j = 0; j < temp_local_edges; j++) {
					if (intersect[
							    temp_solution.vertices_location[temp_solution.edges[j].a] +
							    temp_solution.vertices_location[temp_solution.edges[j].b] * number_points +
							    temp_solution.vertices_location[vertices[vertex].edge[i]] * number_points_p2 +
							    vertex_point * number_points_p3
					            ] == 1 )
					{
						
						local_edge_crossing_count++;
						if (local_edge_crossing_count >= best_solution.number_edge_crossings) {
							goto WORSE_SOLUTION_BREAK;
						}
					}
					else continue;
				}
				temp_solution.edges[temp_solution.number_edges].a = vertex;
				temp_solution.edges[temp_solution.number_edges].b = vertices[vertex].edge[i];
				temp_solution.number_edges++;
				local_edge_count++;
			}			
			temp_solution.number_edge_crossings = local_edge_crossing_count;
			temp_solution.vertices_location[vertex] = vertex_point;
			if (vertex < number_vertices - 1) {
				if (optimize_intersections(vertex + 1, vertex_point)) {
					return 1;
				}
			}			
			else {
				if (temp_solution.number_edge_crossings == 0) {
					copy_solution(0);
					return 1;
				}
				else copy_solution(local_edge_crossing_count);
			}
			temp_solution.number_edge_crossings = local_edge_crossing_count_begin;
			WORSE_SOLUTION_BREAK:
			points[vertex_point].occupied = false;
			temp_solution.number_edges = temp_local_edges;
		}
		vertex_point = (vertex_point + 1) % number_points;

	} while ((vertex_point != vertex_starting_point));

	return 0;
}

void build_populate_intersection_map() {
	int i, j, k, l, o1, o2, o3, o4;
	point_2d aa, ab, ba, bb;

	for(i = 0; i < number_points; i++) {

		for(j = 0; j < number_points; j++) {
			if (j == i) continue;

			for(k = 0; k < number_points; k++) {
				if (k == j || k == i) continue;

				for(l = 0; l < number_points; l++) {
					if (l == k || l == j || l == i) continue;

					aa = points[i];
					ab = points[j];
					ba = points[k];
					bb = points[l];

					o1 = (ab.y - aa.y) * (ba.x - ab.x) - (ab.x - aa.x) * (ba.y - ab.y);
					o1 = o1 == 0 ? 0 : o1 > 0 ? 1 : 2;
					o2 = (ab.y - aa.y) * (bb.x - ab.x) - (ab.x - aa.x) * (bb.y - ab.y);
					o2 = o2 == 0 ? 0 : o2 > 0 ? 1 : 2;
					o3 = (bb.y - ba.y) * (aa.x - bb.x) - (bb.x - ba.x) * (aa.y - bb.y);
					o3 = o3 == 0 ? 0 : o3 > 0 ? 1 : 2;
					o4 = (bb.y - ba.y) * (ab.x - bb.x) - (bb.x - ba.x) * (ab.y - bb.y);
					o4 = o4 == 0 ? 0 : o4 > 0 ? 1 : 2;

					if (o1 != o2 && o3 != o4)
						intersect[i + (j * number_points) + (k * number_points_p2) + (l * number_points_p3)] = 1;

					else if (
							o1 == 0 &&
							(ba.x <= (aa.x >= ab.x ? aa.x : ab.x) &&
							 ba.x >= (aa.x <= ab.x ? aa.x : ab.x) &&
							 ba.y <= (aa.y >= ab.y ? aa.y : ab.y) &&
							 ba.y >= (aa.y <= ab.y ? aa.y : ab.y))
							) intersect[i + (j * number_points) + (k * number_points_p2) + (l * number_points_p3)] = 1;

					else if (
							o2 == 0 &&
							(bb.x <= (aa.x >= ab.x ? aa.x : ab.x) &&
							 bb.x >= (aa.x <= ab.x ? aa.x : ab.x) &&
							 bb.y <= (aa.y >= ab.y ? aa.y : ab.y) &&
							 bb.y >= (aa.y <= ab.y ? aa.y : ab.y))
							) intersect[i + (j * number_points) + (k * number_points_p2) + (l * number_points_p3)] = 1;

					else if (
							o3 == 0 &&
							(aa.x <= (ba.x >= bb.x ? ba.x : bb.x) &&
							 aa.x >= (ba.x <= bb.x ? ba.x : bb.x) &&
							 aa.y <= (ba.y >= bb.y ? ba.y : bb.y) &&
							 aa.y >= (ba.y <= bb.y ? ba.y : bb.y))
							) intersect[i + (j * number_points) + (k * number_points_p2) + (l * number_points_p3)] = 1;

					else if (
							o4 == 0 &&
							(ab.x <= (ba.x >= bb.x ? ba.x : bb.x) &&
							 ab.x >= (ba.x <= bb.x ? ba.x : bb.x) &&
							 ab.y <= (ba.y >= bb.y ? ba.y : bb.y) &&
							 ab.y >= (ba.y <= bb.y ? ba.y : bb.y))
							) intersect[i + (j * number_points) + (k * number_points_p2) + (l * number_points_p3)] = 1;
				}
			}
		}
	}
}

void write_result_to_file(){
	int i, j;

	FILE *file = fopen("data.out", "w");

	for (i = 0; i < number_vertices; i++) {
		for (j = 0; j < vertices[i].edge_count; j++) {
			fprintf(file, "%d %d %d %d\n",
			        points[best_solution.vertices_location[i]].x,
			        points[best_solution.vertices_location[i]].y,
			        points[best_solution.vertices_location[vertices[i].edge[j]]].x,
			        points[best_solution.vertices_location[vertices[i].edge[j]]].y
			);
		}
	}

	fclose(file);
}

int main(int argc, char *argv[]) {

	
	if (argc > 2) {
		printf("Wrong number of arguments\nUse -out to save results to data.out\n");
		return 0;
	}

	char stdin_buffer[BUFFER_SIZE], *buffer;
	int i, edge_vertex_a, edge_vertex_b;

	
	best_solution.number_edge_crossings = 1000;
	temp_solution.number_edge_crossings = 0;
	temp_solution.number_edges = 0;

	
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_points = (int) strtol(buffer, &buffer, 10);

	number_points_p2 = number_points * number_points;
	number_points_p3 = number_points * number_points * number_points;

	
	for (i = 0; i < number_points; i++) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		points[i].x = (int) strtol(buffer, &buffer, 10);
		points[i].y = (int) strtol(buffer, &buffer, 10);
	}

	
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_vertices = (int) strtol(buffer, &buffer, 10);
	number_edges = (int) strtol(buffer, &buffer, 10);

	
	for (i = 0; i < number_vertices; i++) {
		vertices[i].edge_count = 0;
		vertices[i].seen = false;
	}

	
	for (i = 0; i < number_edges; i++) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		edge_vertex_a = (int) strtol(buffer, &buffer, 10) - 1;
		edge_vertex_b = (int) strtol(buffer, &buffer, 10) - 1;
		vertices[edge_vertex_a].seen = true;
		vertices[edge_vertex_b].seen = true;

		if (edge_vertex_a > edge_vertex_b) {
			vertices[edge_vertex_a].edge[vertices[edge_vertex_a].edge_count] = edge_vertex_b;
			vertices[edge_vertex_a].edge_count++;
		}
		else {
			vertices[edge_vertex_b].edge[vertices[edge_vertex_b].edge_count] = edge_vertex_a;
			vertices[edge_vertex_b].edge_count++;
		}
	}

	build_populate_intersection_map();

	optimize_intersections(0, -1);

	printf("%d\n", best_solution.number_edge_crossings);

	
	if (argc == 2){
		if (strcmp(argv[1],"-out") == 0) write_result_to_file();
	}

	
	return 0;
}
