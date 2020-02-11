#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>

#define for1(it, res) for(int it = 1; it <= res; it++)
#define for2(it1, it2, res) for(int it1 = 1; it1 <= res; it1++) for(int it2 = 1; it2 <= res; it2++)
#define for3(it1, it2, it3, res) for(int it1 = 1; it1 <= res; it1++) for(int it2 = 1; it2 <= res; it2++) for(int it3 = 1; it3 <= res; it3++)

std::vector< std::vector<int> > adjMatrix;
std::vector< std::pair<int, int> > edges;
int *scc, *dfs, *low, *sccDegree, dfsTimer = 0, sccCount = 1;
bool *onStack;
std::stack<int> s;

int vCount, eCount;

void tarjan(int v) {
    dfsTimer++;
    dfs[v] = dfsTimer;
    low[v] = dfsTimer;
    s.push(v);
    onStack[v] = true;

    for(int i = 0; i < (int)adjMatrix[v].size(); i++) {
        int u = adjMatrix[v][i];

        if(dfs[u] == -1) {
            tarjan(u);
            low[v] = std::min(low[v], low[u]);
        }

        else if(onStack[u]) {
            low[v] = std::min(low[v], dfs[u]);
        }
    }

    if(dfs[v] == low[v]) {
        int w;
        do {
            w = s.top();
            onStack[w] = false;
            scc[w] = sccCount;
            s.pop();
        } while(w != v);
        sccCount++;
    }
}

void getDegrees() {
    for(int i = 0; i < eCount; i++) {
        if(scc[edges[i].first] != scc[edges[i].second]) {
            sccDegree[scc[edges[i].first]]++;
        }
    }
}

int findV() {
    int group = 0;

    for1(i, (sccCount - 1)) {
        if(sccDegree[i] == 0) {
            if(group == 0) {
                group = i;
            }
            else {
                return 0;
            }
        }
    }
    return group;
}

void initTables() {
    adjMatrix.resize(vCount + 1);

    scc = (int*) malloc((vCount + 1) * sizeof(int));
    dfs = (int*) malloc((vCount + 1) * sizeof(int));
    low = (int*) malloc((vCount + 1) * sizeof(int));
    sccDegree = (int*) malloc((vCount + 1) * sizeof(int));
    onStack = (bool*) malloc((vCount + 1) * sizeof(bool));

    for1(i, vCount) {
        scc[i] = -1;
        dfs[i] = -1;
        low[i] = -1;
        sccDegree[i] = 0;
        onStack[i] = false;
    }
}

 void cleanUp() {
    free(scc);
    free(dfs);
    free(low);
    free(sccDegree);
    free(onStack);
 }

int main() {

    std::cin >> vCount >> eCount;

    if(eCount < (vCount - 1)) {
        std::cout << "0" << std::endl;
        return 0;
    }

    initTables();

    for1(i, eCount) {
        int end1, end2;
        std::cin >> end1 >> end2;
        adjMatrix[end1].push_back(end2);
        edges.push_back(std::make_pair(end1, end2));
    }

    for1(i, vCount) {
        if(dfs[i] == -1) {
            tarjan(i);
        }
    }

    getDegrees();

    int group = findV();

    if(group == 0) {
        std::cout << "0" << std::endl;
        cleanUp();
        return 0;
    }

    int gVcount = 0;

    for1(i, vCount){
        if(scc[i] == group) {
            gVcount++;
        }
    }
    std::cout << gVcount << std::endl;
    cleanUp();
    return 0;
}
