#include <iostream>
#include <cstdlib>
#include <limits>

typedef struct Vertex Vertex;

struct Edge
{
	int cost;
	Vertex *target;
	Edge *next;
};

struct Vertex
{
	int dist;
	Edge *arc;
	Vertex *next;
	Vertex *previous;
};

Vertex **graph;
Vertex *queue;

Vertex *createVertex()
{
	Vertex *newVertex;
	newVertex = (Vertex *)malloc(sizeof(Vertex));
	newVertex->arc = NULL;
	newVertex->next = NULL;
	newVertex->previous = NULL;
	return newVertex;
}

Edge *createEdge(int cost, Vertex *target)
{
	Edge *newEdge = (Edge *)malloc(sizeof(Edge));
	newEdge->cost = cost;
	newEdge->target = target;
	return newEdge;
}

void insertEdge(Vertex *source, Vertex *target, int cost)
{
	if (source->arc)
	{
		Edge *tmpEdge;
		for (tmpEdge = source->arc; tmpEdge->next; tmpEdge = tmpEdge->next)
			;
		tmpEdge->next = createEdge(cost, target);
	}
	else
	{
		source->arc = createEdge(cost, target);
	}
}

Vertex *getSmallestDistVertex()
{
	int smallestDist = queue->dist;

	Vertex *smallestDistVertex = queue;

	for (Vertex *tempVertex = queue; tempVertex; tempVertex = tempVertex->next)
	{
		if (tempVertex->dist < smallestDist)
		{
			smallestDistVertex = tempVertex;
			smallestDist = tempVertex->dist;
		}
	}
	if (smallestDistVertex == queue)
	{
		queue = smallestDistVertex->next;
		smallestDistVertex->previous = NULL;
	}
	else if (smallestDistVertex->next == NULL)
	{
		smallestDistVertex->previous->next = NULL;
	}
	else
	{
		smallestDistVertex->previous->next = smallestDistVertex->next;
		smallestDistVertex->next->previous = smallestDistVertex->previous;
	}

	return smallestDistVertex;
}

int dijkstra(int source, int target, int totalVertices)
{
	for (int i = 1; i <= totalVertices; i++)
	{
		graph[i]->dist = std::numeric_limits<int>::max();
	}
	graph[source]->dist = 0;
	queue = graph[1];

	for (int i = 1; i <= totalVertices; i++)
	{
		Vertex *u = getSmallestDistVertex();
		if (u == graph[target])
		{
			break;
		}

		Edge *tmpEdge = u->arc;
		for (; tmpEdge; tmpEdge = tmpEdge->next)
		{
			if (tmpEdge->target->dist > u->dist + tmpEdge->cost)
			{
				tmpEdge->target->dist = u->dist + tmpEdge->cost;
			}
		}
	}

	return graph[target]->dist;
}

int main()
{
	int totalVertices, targetVertex;
	std::cin >> totalVertices >> targetVertex;

	graph = (Vertex **)malloc((totalVertices + 1) * sizeof(Vertex));
	graph[1] = createVertex();

	for (int i = 2; i <= totalVertices; i++)
	{
		graph[i] = createVertex();
		graph[i - 1]->next = graph[i];
		graph[i]->previous = graph[i - 1];
	}

	for (int i = 1; i <= totalVertices; i++)
	{
		int source;
		std::cin >> source;
		//std::cout << "source: " << source << std::endl;
		for (int target = 1; target <= totalVertices; target++)
		{
			int tempWeight;
			std::cin >> tempWeight;
			if (tempWeight != -1 && source != target)
			{
				insertEdge(graph[source], graph[target], tempWeight);
			}
		}
	}

	std::cout << dijkstra(1, targetVertex, totalVertices) << std::endl;
}
