#include <iostream>
#include <vector>
#include <algorithm>

#define for10(it, res) for(int it = 0; it < res; it++)

#define MAX_N 100

std::vector< std::vector<int> > adj;
enum type{NONE, BLACK, RED};
int vCount;
type vType[MAX_N];

bool bfs(int v) {
    std::vector<int> vQ;
    vQ.push_back(v);
    vType[v] = RED;
    while(!vQ.empty()) {
        int t = vQ.back();
        vQ.pop_back();
        for10(i, (int)adj[t].size()) {
            int u = adj[t][i];
            if(vType[u] == NONE) {
                vQ.push_back(u);
                if(vType[t] == RED) vType[u] = BLACK;
                else if(vType[t] == BLACK) vType[u] = RED;
            }
            else {
                if(vType[t] == vType[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool checkColoring() {
    for10(i, vCount) {
        if(vType[i] == NONE) {
            if(bfs(i) == false) return false;
        }
    }
    return true;
}

int main() {
    std::cin >> vCount;
    adj.resize(vCount);

    for10(i, vCount) {
        vType[i] = NONE;
        for10(j, vCount) {
            int end1;
            std::cin >> end1;
            if(end1) adj[i].push_back(j);
        }
    }

    std::cout << (checkColoring() ? "True" : "False") << std::endl;

    return 0;
}
