#include <iostream>
#include <vector>
#include <algorithm>

#define for10(it, res) for(int it = 0; it < res; it++)

#define MAX_N 100

std::vector< std::vector<int> > adj;
int vCount, disc[MAX_N];

int bfs(int v) {
    int tick = 1;
    std::vector<int> vQ;
    vQ.push_back(v);
    disc[v] = tick++;
    while(!vQ.empty()) {
        int t = vQ.back();
        vQ.pop_back();
        for10(i, (int)adj[t].size()) {
            int u = adj[t][i];
            if(disc[u] == -1) {
                disc[u] = disc[t] + 1;
                vQ.push_back(u);
            }
            else {
                if(u == v) {
                    return disc[t];
                }
            }
        }
    }
    return MAX_N+10;
}

int main() {
    std::cin >> vCount;
    adj.resize(vCount);

    for10(i, vCount) {
        disc[i] = -1;
        for10(j, vCount) {
            int end1;
            std::cin >> end1;
            if(end1) adj[i].push_back(j);
        }
    }

    int temp, shortest = MAX_N+10;
    for10(i, vCount) {
        for10(j, vCount) {
            disc[j] = -1;
        }
        temp = bfs(i);
        if(temp < shortest) {
            shortest = temp;
        }
    }

    std::cout << shortest << std::endl;

    return 0;
}
