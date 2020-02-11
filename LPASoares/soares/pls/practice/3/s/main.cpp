#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <queue>

std::vector< std::vector<int> > adj;
std::vector< std::pair<int, int> > edges;
std::vector< int > orderedDags;
int nTests, vCount, eCount, dfsTimer, sccCount;
int *scc, *dfs, *low, *sccDegree, *weight, *sccTime;
std::stack<int> s;
bool *onStack;

void tarjan(int v) {
    dfsTimer++;
    dfs[v] = dfsTimer;
    low[v] = dfsTimer;
    s.push(v);
    onStack[v] = true;

    for(int i = 0; i < (int)adj[v].size(); i++) {
        int u = adj[v][i];

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
            sccTime[sccCount] += weight[w];
            s.pop();
        } while(w != v);
        sccCount++;
    }
}

void allocData() {
    scc = (int*) malloc((vCount + 1) * sizeof(int));
    dfs = (int*) malloc((vCount + 1) * sizeof(int));
    low = (int*) malloc((vCount + 1) * sizeof(int));
    sccDegree = (int*) malloc((vCount + 1) * sizeof(int));
    sccTime = (int*) malloc((vCount + 1) * sizeof(int));
    onStack = (bool*) malloc((vCount + 1) * sizeof(bool));
    weight = (int*) malloc((vCount + 1) * sizeof(int));
    adj.resize(vCount + 1);
}

void initData() {
    dfsTimer = 0;
    sccCount = 1;
    for(int i = 1; i <= vCount; i++) {
        scc[i] = -1;
        dfs[i] = -1;
        low[i] = -1;
        sccDegree[i] = 0;
        onStack[i] = false;
    }
}

void clearData() {
    adj.clear();
    edges.clear();
    orderedDags.clear();
    free(scc);
    free(dfs);
    free(low);
    free(sccDegree);
    free(sccTime);
    free(onStack);
    free(weight);
}

void getDegrees() {
    for(int i = 0; i < eCount; i++) {
        if(scc[edges[i].first] != scc[edges[i].second]) {
            sccDegree[scc[edges[i].first]]++;
        }
    }
}

void readInput() {
    for(int i = 1; i <= vCount; i++) {
        int vWeight;
        std::cin >>  vWeight;
        weight[i] = vWeight;
    }
    for(int i = 0; i < eCount; i++) {
        int end1, end2;
        std::cin >> end1 >> end2;
        adj[end1].push_back(end2);
        edges.push_back(std::make_pair(end1, end2));
    }
}

void getDag() {
    for(int i = 1; i <= vCount; i++) {
        if(dfs[i] == -1) {
            tarjan(i);
        }
    }
}

void topologicalOrder() {
    std::queue<int> leafs;
    for(int i = 1 ; i < sccCount; i++) {
        if(sccDegree[i] == 0) {
            leafs.push(i);
        }
    }

    while(!leafs.empty()) {
        int n = leafs.front();
        leafs.pop();
        orderedDags.push_back(n);

    }
}

int main() {
    std::cin >> nTests;

    for(int i = 0; i < nTests; i++) {
        std::cin >> vCount >> eCount;
        clearData();
        allocData();
        initData();
        readInput();
        getDag();
        getDegrees();
        topologicalOrder();

    }

	return 0;
}
