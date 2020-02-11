#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>

int vCount, *vDeg, *disc, *low, *parent, timer;
bool *isAp;
std::vector < std::vector < int > > adj;

void allocData() {
    vDeg = (int*) malloc((vCount + 1) * sizeof(int));
    disc = (int*) malloc((vCount + 1) * sizeof(int));
    isAp = (bool*) malloc((vCount + 1) * sizeof(bool));
    parent = (int*) malloc((vCount + 1) * sizeof(int));
    low = (int*) malloc((vCount + 1) * sizeof(int));
    adj.resize(vCount + 1);
    timer = 1;
    for(int i = 1; i <= vCount; i++) {
        disc[i] = -1;
        isAp[i] = false;
        vDeg[i] = 0;
    }
}

void resetData() {
    timer = 1;
    free(vDeg);
    free(disc);
    free(isAp);
    free(low);
    free(parent);
    adj.clear();
}

void readInput() {
    for(int i = 1; i <= vCount; i++) {
        int vEdgCount;
        std::cin >> vEdgCount;
        for(int j = 0; j < vEdgCount; j++) {
            int end1;
            std::cin >> end1;
            adj[i].push_back(end1);
            vDeg[i]++;
        }
    }
}

void aps(int v) {
    disc[v] = timer;
    low[v] = timer;
    timer++;
    for(int i = 0; i < (int)adj[v].size(); i++){
        int w = adj[v][i];
        if(disc[w] == -1) {
            parent[w] = v;
            aps(w);
            low[v] = std::min(low[v], low[w]);
            if(disc[v] == 1 && disc[w] != 2) {
                isAp[v] = true;
            }
            if(disc[v] != 1 && low[w] >= disc[v]) {
                isAp[v] = true;
            }
        }
        else if(parent[v] != w) {
            low[v] = std::min(low[v], disc[w]);
        }
    }
}

void getAps() {
    for(int i = 1; i <= vCount; i++) {
        if(disc[i] == -1) {
            aps(i);
        }
    }
}

int maxDeg() {
    int maxDeg = 0;
    for(int i = 1; i <= vCount; i++) {
        if(isAp[i] ) {
            if(vDeg[i] > maxDeg) {
                maxDeg = vDeg[i];
            }
        }
    }
    return maxDeg;
}

int main() {
    while(std::cin >> vCount) {
        resetData();
        allocData();
        readInput();
        getAps();
        int res = maxDeg();
        if(res == 0) {
            std::cout << "Strong network" << std::endl;
        }
        else {
            std::cout << res << std::endl;
        }
    }
	return 0;
}
