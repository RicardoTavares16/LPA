#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> bridge;

std::vector<bridge> bridges;

bridge newBridge;

bool adj[1000][1000];
int vertexCount, edgeCount, dfsTimer;
int dfs[1000], low[1000], parent[1000];

void graphBridges(int v) {
	dfsTimer++;
	low[v] = dfsTimer;
	dfs[v] = dfsTimer;
	for(int w = 0; w < vertexCount; w++) {
		if(adj[v][w]) {
			if(dfs[w] == -1) {
				parent[w] = v;
				graphBridges(w);
				low[v] = std::min(low[v], low[w]);
				if (low[w] > dfs[v]) {
					if (v > w) {
						newBridge.first = w;
						newBridge.second = v;
					}
					else {
						newBridge.first = v;
                        newBridge.second = w;
					}
					bridges.push_back(newBridge);
				}
			}
			else if (parent[v] != w) {
				low[v] = std::min(low[v], dfs[w]);
			}
		}
	}
}


int main() {
	while(std::cin >> vertexCount >> edgeCount) {
		for(int i = 0; i < vertexCount; i++) {
			dfs[i] = -1;
		}
		for(int i = 0; i < edgeCount; i++) {
			int edgeEnd1, edgeEnd2;
			std::cin >> edgeEnd1 >> edgeEnd2;
			adj[edgeEnd1][edgeEnd2] = true;
			adj[edgeEnd2][edgeEnd1] = true;
		}

		dfsTimer = 0;
		for(int i = 0; i < vertexCount; i++) {
			if (dfs[i] == -1) {
				graphBridges(i);
			}
		}

		#ifdef DEBUG
		for (int i = 0; i < vertexCount; i++) {
			std::cout << i << " " << dfs[i] << " " << low[i] << std::endl;
		}
		#endif

		if(bridges.empty()) {
			std::cout << "No road" << std::endl;
		}
		else {
			std::sort(bridges.begin(), bridges.end());
			for(int i = 0; i < (int)bridges.size(); i++) {
				std::cout << bridges[i].first << " " << bridges[i].second << std::endl;
			}
		}

		bridges.clear();
		for(int i = 0; i < vertexCount; i++) {
			for(int j = 0; j < vertexCount; j++) {
				adj[i][j] = false;
			}
		}
	}
	return 0;
}
