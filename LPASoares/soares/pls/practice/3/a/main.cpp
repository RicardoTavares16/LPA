#include <iostream>
#include <cstdlib>
#include <limits>

int totalCountVertices, targetVertex;

typedef struct edge edge;
typedef struct vertex vertex;

struct edge {
	int cost;
	vertex *target;
	edge *next;
};

struct vertex {
	int dist;
	edge *arc;
	vertex *next;
	vertex *previous;
};

vertex **graph;

vertex *queue;

vertex *createVertex(){
	vertex *newVertex;
	newVertex = (vertex*) malloc(sizeof(vertex));
	newVertex->arc = NULL;
	newVertex->next = NULL;
	newVertex->previous = NULL;
	return newVertex;
}

edge *createEdge(int cost, vertex *target) {
	edge *newEdge = (edge*) malloc(sizeof(edge));
	newEdge->cost = cost;
	newEdge->target = target;
	return newEdge;
}

void insertEdge(vertex *source, vertex *target, int cost) {
	if (source->arc) {
		edge *tempEdge;
		for (tempEdge = source->arc; tempEdge->next; tempEdge = tempEdge->next);
		tempEdge->next = createEdge(cost, target);
	}
	else {
		source->arc = createEdge(cost, target);
	}
}

vertex *getSmallestDistVertex(){
	int smallestDist = queue->dist;
	vertex *smallestDistVertex = queue;
	for (vertex *tempVertex = queue; tempVertex; tempVertex = tempVertex->next) {
		if (tempVertex->dist < smallestDist) {
			smallestDistVertex = tempVertex;
			smallestDist = tempVertex->dist;
		}
	}
	if (smallestDistVertex == queue) {
		queue = smallestDistVertex->next;
		smallestDistVertex->previous = NULL;
	}
	else if(smallestDistVertex->next == NULL) {
		smallestDistVertex->previous->next = NULL;
	}
	else {
		smallestDistVertex->previous->next = smallestDistVertex->next;
		smallestDistVertex->next->previous = smallestDistVertex->previous;
	}

	return smallestDistVertex;
}

int dijkstra(int source, int destiny) {
	for(int i = 1; i <= totalCountVertices; i++) {
		graph[i]->dist = std::numeric_limits<int>::max();
	}
	graph[source]->dist = 0;
	queue = graph[1];

	for(int i = 1; i <= totalCountVertices; i++) {
		vertex *u = getSmallestDistVertex();
		if (u == graph[destiny]) break;
		edge *tempEdge = u->arc;
		for(; tempEdge; tempEdge = tempEdge->next) {
			if (tempEdge->target->dist > u->dist + tempEdge->cost) {
				tempEdge->target->dist = u->dist + tempEdge->cost;
			}
		}
	}
	return graph[destiny]->dist;
}

int main() {
    std::cin >> totalCountVertices >> targetVertex;
	graph = (vertex **) malloc((totalCountVertices+1) * sizeof(vertex));
	graph[1] = createVertex();
	for (int i = 2; i <= totalCountVertices; i++) {
		graph[i] = createVertex();
		graph[i-1]->next = graph[i];
		graph[i]->previous = graph[i-1];

	}
	for(int i = 1; i <= totalCountVertices; i++) {
        int source;
        std::cin >> source;
        for(int target = 1; target <= totalCountVertices; target++) {
        	int tempWeight;
            std::cin >> tempWeight;
            if (tempWeight != -1 && source != target) {
            	insertEdge(graph[source], graph[target], tempWeight);
            }
        }
    }
	std::cout << dijkstra(1, targetVertex) << std::endl;
}
