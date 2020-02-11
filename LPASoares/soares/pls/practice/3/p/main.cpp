#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <limits>

#define for10(it, res) for(int it = 0; it < res; it++)

#define MAX_ELV 5
#define MAX_FLOOR 100

int nElv, source, target, vCount, elvSpeed[MAX_ELV], *dist;
bool hasElev[MAX_FLOOR], *isVisited;

#define INF std::numeric_limits<int>::max() / 2

std::vector<int> targetV;
std::vector< std::vector< int > > floorV;
std::vector< std::vector< std::pair< int, int> > > adj;

void alloc() {
    dist = (int*) malloc((vCount + 1) * sizeof(int));
    isVisited = (bool*) malloc((vCount + 1) * sizeof(bool));
}

void resetData() {
    floorV.clear();
    adj.clear();
    targetV.clear();
    vCount = 1;
    for10(i, MAX_FLOOR) {
        hasElev[i] = 0;
    }
}

void readInput() {
    std::string str;
    getline(std::cin, str);
    std::istringstream iss(str);
    for(int i = 0; i < nElv; i++) {
        iss >> elvSpeed[i];
    }
    for10(i, nElv) {
        getline(std::cin, str);
        std::istringstream iss(str);
        int floor, lastFloor;
        bool firstElevFloor = true;
        while(iss >> floor) {
            if(floor == target) {
                targetV.push_back(vCount);
            }
            if(!firstElevFloor) {
                if(lastFloor == 0) {
                    adj[vCount].push_back(std::make_pair(0, (floor - lastFloor) * elvSpeed[i]));
                    adj[0].push_back(std::make_pair(vCount, (floor - lastFloor) * elvSpeed[i]));
                }
                else{
                    adj[vCount-1].push_back(std::make_pair(vCount, (floor - lastFloor) * elvSpeed[i]));
                    adj[vCount].push_back(std::make_pair(vCount - 1, (floor - lastFloor) * elvSpeed[i]));
                }
            }
            if(hasElev[floor] == true && floor != 0 && floor) {
                for10(j, (int)floorV[floor].size()) {
                    adj[vCount].push_back(std::make_pair(floorV[floor][j], 60));
                    adj[floorV[floor][j]].push_back(std::make_pair(vCount, 60));
                }
            }
            floorV[floor].push_back(vCount);
            hasElev[floor] = true;
            if(floor !=0 )vCount++;
            lastFloor = floor;
            firstElevFloor = false;
        }
    }
}

void printGraph() {
    for10(i, vCount) {
        std::cout << i << " ";
        for10(j, (int)adj[i].size()) {
            std::cout << "(" << adj[i][j].first << "," << adj[i][j].second << ") ";
        }
        std::cout << std::endl;
    }
    std::cout  << "targets - ";
    for10(i, (int)targetV.size()) {
        std::cout << targetV[i] << " ";
    }
     std::cout << "vcout " << vCount;
    std::cout << std::endl;
}

int lowestDistV() {
    int minDist = ((INF) + 1), minDistV;
    for(int i = 0; i < vCount; i++) {
        if(dist[i] < minDist && !isVisited[i]) {
            minDist = dist[i];
            minDistV = i;
        }
    }
    return minDistV;
}

int dijkstra(){
    bool targetFlag = false;
    for(int i = 0; i < vCount; i++) {
        dist[i] = INF;
        isVisited[i] = false;
    }
    dist[0] = 0;
    int u;
    for(int i = 0; i < vCount; i++) {
        u = lowestDistV();
        isVisited[u] = true;
        for10(j, (int)targetV.size()) {
            if(u == targetV[j]) {
                targetFlag = true;
                break;
            }
        }
        if (targetFlag) break;
        for(int j = 0; j < (int)adj[u].size(); j++) {
            int v = adj[u][j].first;
            int w = adj[u][j].second;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    if(targetFlag) return dist[u];
    else return -1;
}

int main() {
    std::string str;
    while(getline(std::cin, str)) {
        std::istringstream iss(str);
        iss >> nElv;
        iss >> target;
        floorV.resize(MAX_FLOOR);
        adj.resize(MAX_FLOOR * MAX_ELV);
        resetData();
        readInput();
        //printGraph();
        alloc();
        int res = dijkstra();
        if(res == -1) std::cout << "IMPOSSIBLE" << std::endl;
        else std::cout << res << std::endl;
    }
	return 0;
}
