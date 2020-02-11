#include <iostream>
#include <vector>
#include <algorithm>

#define for1(it, res) for(int it = 0; it < res; it++)

#define MAX_V 100

std::vector< std::vector<int> > adjMatrix;
int vCount;
bool isVisited[MAX_V];
bool belongsLoop[MAX_V];
bool onStack[MAX_V];
std::vector<int> vStack;

void runDfs(int v) {
    isVisited[v] = true;
    onStack[v] = true;
    vStack.push_back(v);
    for1(i, (int)adjMatrix[v].size()) {
        int u = adjMatrix[v][i];
        if(isVisited[u] == false) {
            runDfs(u);
        }
        else if(onStack[u]) {
            for(int j = (int)vStack.size() -1; j >= 0; j--) {
                belongsLoop[vStack[j]] = true;
                if (vStack[j] == u) break;
            }
        }
    }
    vStack.pop_back();
    onStack[v] = false;
}

void resetDfs() {
    vStack.clear();
    for1(i, vCount) {
        isVisited[i] = false;
        onStack[i] = false;
    }
}

void findLoops() {
    for1(i, vCount) {
        if(!isVisited[i]) {
            resetDfs();
            runDfs(i);
        }
    }
}

void printSolution() {
    for1(i, vCount) {
        if(belongsLoop[i]) std::cout << i << std::endl;
    }
}

int main() {
    std::cin >> vCount;

    adjMatrix.resize(vCount);

    for1(i, vCount) {
        int eCount;
        std::cin >> eCount;

        for1(j, eCount) {
            int eEnd;
            std::cin >> eEnd;
            adjMatrix[i].push_back(eEnd);
        }
    }

    findLoops();

    printSolution();

    return 0;
}
