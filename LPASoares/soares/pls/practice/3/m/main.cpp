#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>

#define for10(it, res) for(int it = 0; it < res; it++)


std::vector< std::vector<int> > adj;
int vCount, *disc, timer;
bool *visited;

void readInput() {
    int eCount, end1, end2;
    std::map<std::string, int> lMap;
    std::cin >> vCount >> eCount;
    adj.resize(vCount);
    disc = (int*) malloc(vCount * sizeof(int));
    visited = (bool*) malloc(vCount * sizeof(bool));
    std::string str1, str2;
    for10(i, vCount) {
        std::cin >> str1;
        lMap[str1] = i;
    }
    for10(i, eCount) {
        std::cin >> str1 >> str2;
        end1 = lMap.find(str1)->second;
        end2 = lMap.find(str2)->second;
        adj[end1].push_back(end2);
        adj[end2].push_back(end1);
    }
}

void dfs(int v) {
    disc[v] = timer;
    visited[v] = true;
    timer++;
    for10(i, (int)adj[v].size()) {
        int u = adj[v][i];
        if (disc[u] == -1) {
            dfs(u);
        }
    }
}

int dfs_runner() {
    int maxDisc = 0;
    for10(i, vCount) {
        if(visited[i] == false) {
            timer = 0;
            for10(j, vCount) {
                disc[j] = -1;
            }
            dfs(i);
            maxDisc = timer > maxDisc ? timer : maxDisc;
        }
    }
    return maxDisc;
}

int main() {
    readInput();
    std::cout << dfs_runner() << std::endl;
	return 0;
}
