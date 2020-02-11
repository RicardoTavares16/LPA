#include <iostream>
#include <vector>
#include <cstdlib>

#define for11(it, res) for(int it = 1; it <= res; it++)
#define for10(it, res) for(int it = 0; it < res; it++)

std::vector< std::vector<int> > adj;
int vCount, timer;
int *disc, *low, *parent, *vWeight;
bool *isAp, areAps;

void allocData() {
    timer = 1;
    adj.resize(vCount + 1);
    disc = (int*) malloc((vCount + 1) * sizeof(int));
    low = (int*) malloc((vCount + 1) * sizeof(int));
    isAp = (bool*) malloc((vCount + 1) * sizeof(bool));
    vWeight = (int*) malloc((vCount + 1) * sizeof(int));
    parent = (int*) malloc((vCount + 1) * sizeof(int));
    for11(i, vCount) {
        disc[i] = -1;
        vWeight[i] = 0;
        isAp[i] = false;
    }
    areAps = false;
}

void clearData() {
    timer = 0;
    adj.clear();
    free(disc);
    free(isAp);
    free(low);
    free(vWeight);
    free(parent);
}

void readInput() {
    for11(end1, vCount) {
        int nEdges;
        std::cin >> nEdges;
        for11(j, nEdges) {
            int end2, weight;
            std::cin >> end2 >> weight;
            adj[end1].push_back(end2);
            vWeight[end1] += weight;
        }
    }
}

void aps(int v) {
    disc[v] = timer;
    low[v] = timer;
    timer++;
    for10(i, (int)adj[v].size()) {
        int w = adj[v][i];
        if(disc[w] == -1) {
            parent[w] = v;
            aps(w);
            low[v] = std::min(low[v], low[w]);
            if(disc[v] == 1 && disc[w] != 2) {
                isAp[v] = true;
                areAps = true;

            }
            if(disc[v] != 1 && low[w] >= disc[v]) {
                isAp[v] = true;
                areAps = true;
            }
        }
        else if(parent[v] != w) {
            low[v] = std::min(low[v], disc[w]);
        }
    }
}

void getAps() {
    for11(i, vCount) {
        if(disc[i] == -1) {
            aps(i);
        }
    }
}

int getMaxApWeight() {
    if(!areAps) return -1;
    int maxWeight = 0;
    for11(i, vCount) {
        if(isAp[i] == true) {
            if(vWeight[i] > maxWeight) {
                maxWeight = vWeight[i];
            }
        }
    }
    return maxWeight;
}

int main() {
    while(std::cin >> vCount) {
        allocData();
        readInput();
        getAps();
        int res = getMaxApWeight();
        if(res == -1) std::cout << "Well designed city!" << std::endl;
        else std::cout << res << std::endl;
        clearData();
    }
	return 0;
}
