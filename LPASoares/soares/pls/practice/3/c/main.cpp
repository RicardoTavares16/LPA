#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int vertexCount;
int maxDepth;
int timer;
std::vector< std::vector<int> > adjMatrix;
std::vector<int> vertexDegree;
std::vector<bool> isVisited;
std::queue<int> leafQueue;
std::vector<int> depth;
std::vector<int> minHeight;
std::vector<int> maxHeight;

void clearAndPopulateLeafQueue() {
    leafQueue = std::queue<int>();
    for(int i = 1; i <= vertexCount; i++) {
		if(vertexDegree[i] == 1) leafQueue.push(i);
	}
}

void clearIsVisitedVector() {
    for(int i = 0; i < (int)isVisited.size(); i++) {
        isVisited[i] = false;
    }
}

void getRootsForMinDepth() {
    std::vector<int> localVertexDegree(vertexDegree);

	int localVertexCount = vertexCount;

	while(localVertexCount > 2) {

        int queueSize = (int)leafQueue.size();
		for(int i = 0; i < queueSize; i++) {
			int temp = leafQueue.front();
			leafQueue.pop();
			localVertexCount--;
			for(int j = 0; j < (int)adjMatrix[temp].size(); j++) {
				localVertexDegree[adjMatrix[temp][j]]--;
				if (localVertexDegree[adjMatrix[temp][j]] == 1) {
					leafQueue.push(adjMatrix[temp][j]);
				}
			}
		}
	}
	while(!leafQueue.empty()) {
        minHeight.push_back(leafQueue.front());
        leafQueue.pop();
	}
}

void dfsSerch(int vertex, int currentDepth) {
    timer++;
    depth[vertex] = currentDepth;
    isVisited[vertex] = true;
    maxDepth = currentDepth > maxDepth ? currentDepth : maxDepth;
    for(int i = 0; i < (int)adjMatrix[vertex].size(); i++) {
        if (isVisited[adjMatrix[vertex][i]] == false) {
            dfsSerch(adjMatrix[vertex][i], currentDepth + 1);
        }
    }
}

void getRootsForMaxDepth() {
    depth.resize(vertexCount + 1);
    isVisited.resize(vertexCount + 1);

    timer = 0;
    maxDepth = 0;
    clearIsVisitedVector();
    dfsSerch(leafQueue.front(), 0);
    for(int i = 1; i < (int)depth.size(); i++) {
        if(depth[i] == maxDepth) maxHeight.push_back(i);
    }

    timer = 0;
    maxDepth = 0;
    clearIsVisitedVector();
    dfsSerch(maxHeight[0], 0);
    for(int i = 1; i < (int)depth.size(); i++) {
        if(depth[i] == maxDepth) maxHeight.push_back(i);
    }
}

int main() {
	std::cin >> vertexCount;

	vertexDegree.resize(vertexCount + 1);
	adjMatrix.resize(vertexCount + 1);

	for(int i = 0; i < vertexCount - 1; i++) {
		int end1, end2;
		std::cin >> end1 >> end2;
		vertexDegree[end1]++;
		vertexDegree[end2]++;
		adjMatrix[end1].push_back(end2);
		adjMatrix[end2].push_back(end1);
	}

    clearAndPopulateLeafQueue();
	getRootsForMinDepth();
	clearAndPopulateLeafQueue();
    getRootsForMaxDepth();

	std::sort(minHeight.begin(), minHeight.end());
    std::sort(maxHeight.begin(), maxHeight.end());

    minHeight.erase( std::unique(minHeight.begin(), minHeight.end()), minHeight.end());
    maxHeight.erase( std::unique(maxHeight.begin(), maxHeight.end()), maxHeight.end());

    std::cout << "Shortest: ";
    for(int i = 0; i < (int)minHeight.size(); i++) {
        if (i == ((int)minHeight.size() - 1)) std::cout << minHeight[i] << std::endl;
        else std::cout << minHeight[i] << " ";
    }
    std::cout << "Tallest: ";
    for(int i = 0; i < (int)maxHeight.size(); i++) {
        if (i == ((int)maxHeight.size() - 1)) std::cout << maxHeight[i] << std::endl;
        else std::cout << maxHeight[i] << " ";
    }

	return 0;
}
