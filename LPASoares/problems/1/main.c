/*
 * LPA 2018/2019
 * Mooshak ID -> PASSEVITE
 * João Soares - jmsoares@student.dei.uc.pt
 * José Ferreira - jmamede@student.dei.uc.pt
 * Madalena Santos - mcsantos@student.dei.uc.pt
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Buffer size for input reading
#define BUFFER_SIZE 32

//Structure to store a R2 point with (x,y) coordinates and a boolean variable to know if the point is occupied
typedef struct point_2d {
	int x;
	int y;
	bool occupied;
} point_2d;

//Structure to store the ID of the start and ending vertices that compose an edge
typedef struct edge {
	int a;
	int b;
} edge;

/* Structure to store information related to a vertex. Stores the ID of the vertices to which it connects to compose an
edge, the number of neighbours that the vertex has and if that particular vertex has been seen when creating the edges list */
typedef struct vertex {
	int edge[28];
	int edge_count;
	bool seen;
} vertex;

/* Structure to save a solution to the problem. It stores the ID of the point for each vertex set, how many vertices
compose the solution, the edges, number of edges, and how many edge crossings we have on the solution */
typedef struct solution {
	int vertices_location[81];
	edge edges[28];
	int number_edges;
	int number_edge_crossings;
} solution;

//Array to store all the x,y coordinates available to place the vertices
point_2d points[81];

//Array to store all the vertices and related information of the problem
vertex vertices[81];

/* Pointer to an array allocated later in the program. This will store all the pre-processed information related to the intersections
of all the point coordinates available */
char intersect[43046721];

//Variable to store the best solution found so far
solution best_solution;

//Variable to store the solution we are building, to see if its viable
solution temp_solution;

/* Several variables to store information related to the problem
We also store the number of points to the power of 2 and 3, because we use the value repeatedly */
int number_points, number_vertices, number_edges,  number_points_p2, number_points_p3;

//Function to copy the temporary solution into the best solution
void copy_solution(int number_edge_crossings){
	int i;

	best_solution.number_edges = temp_solution.number_edges;
	best_solution.number_edge_crossings = number_edge_crossings;

	for (i = 0; i < number_vertices; i++) {
		best_solution.vertices_location[i] = temp_solution.vertices_location[i];
	}
}

//Function to optimize the intersections, which, in this case, is getting the minimum number of intersections possible
int optimize_intersections(int vertex, int last_vertex_point) {

	/* We check whether the vertex in hand has been see or not (being seen means that our vertex is either the start
	or the end of an edge) */
	if (vertices[vertex].seen == false) {

		/* If we have a vertex that doesn't relate to any edge, we can skip the edge & intersection check, proceeding to
		call the function for the next vertex */
		if (vertex < number_vertices - 1) {

			/* If it's not the last vertex, we call the function to the next one, but give it the same starting position of
			the last one */
			if (optimize_intersections(vertex + 1, last_vertex_point)) {
				/* If we have a return of 1, it means we've got a solution with 0 intersections, so we can return all the way
				out of the recursion */
				return 1;
			}
			//else we return 0 to continue the search
			else return 0;
		}
		/* In case this is the last vertex left to be placed, having reached this point means we have a solution better than the best one at
		hand. We only need to check if the number of crossings is 0 (to return 1) or not (to return 0 and continue) */
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

	//Initialization of variables
	int i, j, temp_local_edges, local_edge_crossing_count, local_edge_count;

	//Stores the ID of the current (x,y) point we are setting the vertex to test
	int vertex_point = (last_vertex_point + 1) % number_points;

	//Stores the ID of the (x,y) point where we started to test
	int vertex_starting_point = vertex_point;

	//Stores the number of edge crossings that the solution we have built so far has
	int local_edge_crossing_count_begin = temp_solution.number_edge_crossings;

	//We do this cycle while our vertex is positioned around all the (x,y) points, until it reaches its starting position
	do {

		//If there is a point that is not being used by any previous points
		if (!points[vertex_point].occupied) {

			//We set the flag of that point as "occupied"
			points[vertex_point].occupied = true;

			//Set this variable to the number of crossings of the solution we're building
			local_edge_crossing_count = local_edge_crossing_count_begin;

			//Number of edges we successfully tested so far
			local_edge_count = 0;

			//Number of edges that are currently set on the solution we're building
			temp_local_edges = temp_solution.number_edges;

			//Iterates over all the edges where our vertex participates
			for (i = 0; i < vertices[vertex].edge_count; i++) {

				//Iterates over all the edges set on the solution so far
				for (j = 0; j < temp_local_edges; j++) {

					//Here we use the pre-computed intersection information and check whether the edges intersect or not
					if (intersect[
							    temp_solution.vertices_location[temp_solution.edges[j].a] +
							    temp_solution.vertices_location[temp_solution.edges[j].b] * number_points +
							    temp_solution.vertices_location[vertices[vertex].edge[i]] * number_points_p2 +
							    vertex_point * number_points_p3
					            ] == 1 )
					{
						//If they intersect, we update our intersection count
						local_edge_crossing_count++;

						/* Here we check if the intersection count is still a better solution than our current best
						found so far. If it's not, we break, because there's no need to continue */
						if (local_edge_crossing_count >= best_solution.number_edge_crossings) {
							goto WORSE_SOLUTION_BREAK;
						}
					}
					else continue;
				}

				/* When we reach this part, it means that we+ve successfully tested our new edge with all the edges set on the
				solution, and the intersection count so far is still better than our best solution. So we
				record the edge on the temporary solution, and update its count */
				temp_solution.edges[temp_solution.number_edges].a = vertex;
				temp_solution.edges[temp_solution.number_edges].b = vertices[vertex].edge[i];
				temp_solution.number_edges++;
				local_edge_count++;
			}

			/* If we reach this, it means that we tested all the edges that our current vertex completes, against all
			the edges that were set on the solution, and the intersection count is still better. So we record our
			vertex's (x,y) point ID and update the number of edge crossings and the number of vertices of the solution */
			temp_solution.number_edge_crossings = local_edge_crossing_count;
			temp_solution.vertices_location[vertex] = vertex_point;

			//If we're not the last vertex, we call the function to test for the next vertex
			if (vertex < number_vertices - 1) {
				if (optimize_intersections(vertex + 1, vertex_point)) {
					//if we have a return of 1, means we got a solution with 0 intersections, so we can return all the way
					// out of the recursion
					return 1;
				}
			}

			/* If we have the last vertex, and have reached here, it means we have a solution better than the best one.
            We only need to check if the number of crossings is 0 (to return 1) or not (to return 0 and continue) */
			else {
				if (temp_solution.number_edge_crossings == 0) {
					copy_solution(0);
					return 1;
				}
				else copy_solution(local_edge_crossing_count);
			}

			//After doing all the calculations, we clean the temporary solution so we can re-test with other points
			temp_solution.number_edge_crossings = local_edge_crossing_count_begin;
			WORSE_SOLUTION_BREAK:
			points[vertex_point].occupied = false;
			temp_solution.number_edges = temp_local_edges;
		}

		//We go to the next point in order to test
		vertex_point = (vertex_point + 1) % number_points;

	} while ((vertex_point != vertex_starting_point));

	return 0;
}

/* Function to build and populate the intersection map. This map holds the information correlating every combination of
4 distinct points (since when any point is repeated we never have an intersection) to whether the created 2 segments
have an intersection between them */
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

//Function to write the (x,y) coordinates of both points of each edge to a file named data.out
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

//Main
int main(int argc, char *argv[]) {

	//If the argument count is bigger than 2 we print info and return
	if (argc > 2) {
		printf("Wrong number of arguments\nUse -out to save results to data.out\n");
		return 0;
	}

	char stdin_buffer[BUFFER_SIZE], *buffer;
	int i, edge_vertex_a, edge_vertex_b;

	//Variable initialization. We set the best solution to 1000, which, considering the problem bounds, will serve as "INFINITY"
	best_solution.number_edge_crossings = 1000;
	temp_solution.number_edge_crossings = 0;
	temp_solution.number_edges = 0;

	//Input reading for number of points
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_points = (int) strtol(buffer, &buffer, 10);

	number_points_p2 = number_points * number_points;
	number_points_p3 = number_points * number_points * number_points;

	//Input reading for (x,y) coordinates of points
	for (i = 0; i < number_points; i++) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		points[i].x = (int) strtol(buffer, &buffer, 10);
		points[i].y = (int) strtol(buffer, &buffer, 10);
	}

	//Input reading for number of vertices and edges
	fgets(stdin_buffer, BUFFER_SIZE, stdin);
	buffer = stdin_buffer;
	number_vertices = (int) strtol(buffer, &buffer, 10);
	number_edges = (int) strtol(buffer, &buffer, 10);

	//Initialization of variables
	for (i = 0; i < number_vertices; i++) {
		vertices[i].edge_count = 0;
		vertices[i].seen = false;
	}

	//Input reading for edges
	for (i = 0; i < number_edges; i++) {
		fgets(stdin_buffer, BUFFER_SIZE, stdin);
		buffer = stdin_buffer;
		edge_vertex_a = (int) strtol(buffer, &buffer, 10) - 1;
		edge_vertex_b = (int) strtol(buffer, &buffer, 10) - 1;
		vertices[edge_vertex_a].seen = true;
		vertices[edge_vertex_b].seen = true;

		/* While reading the edges, we want to store the information in the biggest vertex ID that relates to the smallest
		one. Eg. we have edge 3 9, so we store info in vertex 9 to show that it connects to vertex 3, creating an edge. This way,
		while setting the vertices up, we have the guarantee that when we set a vertex, all the dependent ones to complete
		all its edges are already set */
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

	//If the program was called with the -out we write the edges endpoint coordinates to a file
	if (argc == 2){
		if (strcmp(argv[1],"-out") == 0) write_result_to_file();
	}

	//THE END
	return 0;
}
