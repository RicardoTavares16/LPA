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

void resetData() {
    vCoord = (std::pair <int, int>*) malloc((vCount + 1) * sizeof(std::pair <int, int>));
    w = (long double**) malloc((vCount + 1) * sizeof(long double*));
    for11(i, vCount-1) {
        w[i] = (long double*) malloc((vCount - i + 1 ) * sizeof(long double));
    }
}

void readInput() {

    for11(i, vCount) {
        int x, y;
        std::cin >> x >> y;
        vCoord[i].first = x;
        vCoord[i].second = y;
    }

    for11(i, vCount - 1) {
        for(int j = i+1; j <= vCount; j++) {
            long double x1 = vCoord[i].first;
            long double y1 = vCoord[i].second;
            long double x2 = vCoord[j].first;
            long double y2 = vCoord[j].second;
            w[i][j-i] = (long double) std::sqrt( (long double)std::fabs(x1 - x2) * (long double)std::fabs(x1 - x2) + (long double)std::fabs(y1 - y2) * (long double)std::fabs(y1 - y2));
        }
    }

    std::cin >> eCount;
    for10(i, eCount){
        int end1, end2;
        std::cin >> end1 >> end2;
        if(end1 > end2) {
            w[end2][end1-end2] = (long double)0;
        }
        else w[end1][end2-end1] = (long double)0;
    }

    for11(i, vCount - 1) {
        for(int j = i+1; j <= vCount; j++) {
            #ifdef DDISTS
            std::cout << "dist points (" << i << "," << j << ") - " << w[i][j-i] << std::endl;
            #endif // DDISTS
            edges.push_back(std::make_pair(w[i][j-i], std::make_pair(i, j)));
        }
        free(w[i]);
    }

    free(w);
    free(vCoord);
    std::sort(edges.begin(), edges.end(), decrease);
}

int main() {
    while(std::cin >> vCount) {
        resetData();
        readInput();
        printf("%.2Lf\n", kruskal());
    }
}
