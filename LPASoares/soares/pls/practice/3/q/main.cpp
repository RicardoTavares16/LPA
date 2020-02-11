#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>

int vCount, *outDeg, *vLvl, mDepth, mDeg;
std::vector < std::vector < int > > adj;

void allocData() {
    outDeg = (int*) malloc((vCount + 1) * sizeof(int));
    vLvl = (int*) malloc((vCount + 1) * sizeof(int));
    adj.resize(vCount + 1);
    for(int i = 1; i <= vCount; i++) {
        vLvl[i] = -1;
    }
}

void resetData() {
    free(outDeg);
    free(vLvl);
    adj.clear();
}

void readInput() {
    for(int i = 1; i <= vCount; i++) {
        int vOutDeg;
        std::cin >> vOutDeg;
        outDeg[i] = vOutDeg;
        for(int j = 0; j < vOutDeg; j++) {
            int end1;
            std::cin >> end1;
            adj[i].push_back(end1);
        }
    }
}

int bfs(int s) {
    mDepth = 0;
    mDeg = outDeg[s];
    std::queue<int> q;
    vLvl[s] = 0;
    q.push(s);
    while(!q.empty()) {
        int t = q.front();
        q.pop();
        for(int i = 0; i < (int)adj[t].size(); i++) {
            int u = adj[t][i];
            if(vLvl[u] == -1) {
                vLvl[u] = vLvl[t] + 1;
                q.push(u);
                if(outDeg[u] > mDeg) {
                    mDeg = outDeg[u];
                    mDepth = vLvl[u];
                }
            }
        }
    }
    return mDepth;
}

int main() {
    while(std::cin >> vCount) {
        resetData();
        allocData();
        readInput();
        int res = bfs(1);
        if(res == 0) {
            std::cout << "King of popularity!" << std::endl;
        }
        else {
            std::cout << res << std::endl;
        }
    }
	return 0;
}
