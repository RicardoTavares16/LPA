#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define for10(it, res) for(int it = 0; it < res; it++)
#define for11(it, res) for(int it = 1; it <= res; it++)

#define MAX_N 100

std::vector< std::vector<int> > adj;
int vCount, dfs[MAX_N], apCount, low[MAX_N], parent[MAX_N], dfsTimer;
bool vIsAp[MAX_N];

void resetData() {
    adj.clear();
    adj.resize(vCount + 1);
    apCount = 0;
    dfsTimer = 0;
    for11(i, vCount) {
        dfs[i] = -1;
        vIsAp[i] = false;
    }

}

void readInput() {
    std::string str;

    while(getline(std::cin, str)) {
        char *cstr;
        cstr = new char[str.size()+1];
        strcpy(cstr, str.c_str());

        int end2, end1 = atoi(strtok(cstr, " "));
        if (end1 == 0) break;
        char *end2C = strtok(NULL, " ");

        do{
            end2 = atoi(end2C);
            adj[end1].push_back(end2);
            adj[end2].push_back(end1);
            end2C = strtok(NULL, " ");

        } while(end2C);
    }
}

void ap(int v) {
    dfsTimer++;
    dfs[v] = dfsTimer;
    low[v] = dfsTimer;

    for10(i, (int)adj[v].size()) {
        int w = adj[v][i];
        if(dfs[w] == -1) {
            parent[w] = v;
            ap(w);
            low[v] = std::min(low[v], low[w]);
            if(dfs[v] == 1 && dfs[w] != 2) {
                if(!vIsAp[v]) {
                    vIsAp[v] = true;
                    apCount++;
                }
            }
            if(dfs[v] != 1 && low[w] >= dfs[v]) {
                if(!vIsAp[v]) {
                    vIsAp[v] = true;
                    apCount++;
                }
            }
        }
        else if(parent[v] != w) {
            low[v] = std::min(low[v], dfs[w]);
        }
    }
}

int getApCount() {
    for11(i, vCount) {
        if(dfs[i] == -1) {
            ap(i);
        }
    }
    return apCount;
}

int main() {
    std::string str;

    while(getline(std::cin, str)) {
        vCount = std::atoi(str.c_str());
        if (vCount == 0) break;
        resetData();
        readInput();
        std::cout << getApCount() << std::endl;

    }
    return 0;
}
