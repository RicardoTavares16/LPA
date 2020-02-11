#include <iostream>
#include <queue>
#include <vector>

#define for1(it, res) for(int it = 0; it < res; it++)

#define MAX_ID 500

std::vector< std::vector<int> > adjMatrix;
bool isVisited[MAX_ID];
enum colour {RED, BLACK, NONE};
colour vColor[MAX_ID];
int vCount;

bool bfs(int v) {
    std::queue<int> vQueue;
    isVisited[v] = true;
    vColor[v] = RED;
    vQueue.push(v);
    while(vQueue.empty() == false) {
        int t = vQueue.front();
        vQueue.pop();
        for1(i, (int)adjMatrix[t].size()) {
            int u = adjMatrix[t][i];
            if(isVisited[u] == false) {
                isVisited[u] = true;
                if(vColor[t] == RED) vColor[u] = BLACK;
                else if(vColor[t] == BLACK) vColor[u] = RED;
                vQueue.push(u);
            }
            else {
                if(vColor[t] == vColor[u]) return false;
            }
        }
    }
    return true;
}

void resetTables() {
    adjMatrix.clear();
    adjMatrix.resize(vCount + 1);
    for1(i, vCount + 1) {
        isVisited[i] = false;
        vColor[i] = NONE;
    }
}

void readInput() {
    int eCount;
    std::cin >> eCount;
    int end1, end2;

    for1(i, eCount) {
        std::cin >> end1 >> end2;

        adjMatrix[end1].push_back(end2);
        adjMatrix[end2].push_back(end1);
    }
}

bool checkColoring() {
    for1(i, vCount) {
        if(isVisited[i] == false) {
            if(bfs(i) == false) return false;
        }
    }
    return true;
}

int main() {

    while(std::cin >> vCount) {
        resetTables();
        readInput();
        std::cout << (checkColoring() ? "No" : "Yes") << std::endl;
    }

	return 0;
}
