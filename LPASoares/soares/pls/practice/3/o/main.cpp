#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>

#define INF std::numeric_limits<int>::max()/2

#define for1(it, res) for(int it = 0; it < res; it++)

std::vector< std::vector < std::pair<int, int> > > adjMatix;

bool belmannFord(int vCount, int source) {
    int *dist = (int*) malloc(vCount * sizeof(int));
    for1(i, vCount) dist[i] = INF;
    dist[source] = 0;
    for1(i, vCount) {
        for1(v, vCount) {
            int u, w;
            for1(k, (int)adjMatix[v].size()) {
                u = adjMatix[v][k].first;
                w = adjMatix[v][k].second;
                if(dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    for1(v, vCount) {
        int u, w;
        for1(k, (int)adjMatix[v].size()) {
            u = adjMatix[v][k].first;
            w = adjMatix[v][k].second;
            if(dist[v] > dist[u] + w) {
                free(dist);
                return false;
            }
        }
    }
    free(dist);
    return true;
}

void resetMatrix(int vCount) {
    adjMatix.clear();
    adjMatix.resize(vCount);
}

void readInput(int eCount) {
    for1(i, eCount) {
        int end1, end2, weight;
        std::cin >> end1 >> end2 >> weight;
        adjMatix[end1].push_back(std::make_pair(end2, weight));
    }
}

int main() {
    int testsCount;
    std::cin >> testsCount;

    int vCount, eCount;
    for1(i, testsCount) {
        std::cin >> vCount >> eCount;
        resetMatrix(vCount);
        readInput(eCount);
        std::cout << (belmannFord(vCount, 0) == true ? "not possible" : "possible") << std::endl;
    }

    return 0;
}
