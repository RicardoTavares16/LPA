#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <stdio.h>

#define for10(it, res) for(int it = 0; it < res; it++)
#define for11(it, res) for(int it = 1; it <= res; it++)

long double **w;
int vCount, eCount;
std::pair <int, int> *vCoord;
std::vector< std::pair<long double, std::pair<int, int> > > edges;
std::vector< std::vector<int> > adj;
int vSet[750], vRank[750];

void makeSet() {
    for11(i, vCount) {
        vSet[i] = i;
        vRank[i] = 0;
    }
}

int findSet(int a) {
    if(vSet[a] != a) {
        vSet[a] = findSet(vSet[a]);
    }
    return vSet[a];
}

void link(int a, int b) {
    if (vRank[a] > vRank[b]) {
        vSet[b] = a;
    }
    else {
        vSet[a] = b;
        if(vRank[a]==vRank[b]) {
            vRank[b]++;
        }
    }
}

void unionSet(int a, int b) {
    link(findSet(a), findSet(b));
}

long double kruskal() {
    long double w, weight = 0;
    makeSet();
    int u, v;
    while(!edges.empty()) {
        u = edges.back().second.first;
        v = edges.back().second.second;
        w = edges.back().first;
        if(findSet(u) != findSet(v)) {
            weight += w;
            unionSet(u, v);
        }
        edges.pop_back();
    }
    return weight;
}

bool decrease(const std::pair<long double, std::pair<int, int> > &a, const std::pair<long double, std::pair<int, int> > &b) {
	if(a.first == b.first) {
		if(a.second.first == b.second.first) {
        	return (a.second.second < b.second.second);
		}
		else return (a.second.first < b.second.first);
	}
	else return (a.first > b.first);
}

void readInput() {

}

int main() {
    int nTests;
    std::cin >> nTests;
    while(nTests != 0) {

        nTests--;
    }
}
