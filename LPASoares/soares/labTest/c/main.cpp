#include <iostream>
#include <vector>
#include <cstdlib>

#define for10(it, res) for(int it = 0; it < res; it++)

int vCount, timer, apCount;
int dfs[21], low[21], parent[21];

bool isStrany;
bool isAp[21];

std::vector < std::vector<int > > adj;

void dfsRunner(int v) {
	timer++;
	dfs[v] = timer;
	if(timer == apCount) {
		isStrany = true;
	}
	for10(i, (int)adj[v].size()) {
		int u = adj[v][i];
		if((dfs[u] == -1) && isAp[u]) {
			dfsRunner(u);
		}
	}
}

void isSubGraph() {
	int firstAp = -1;
	for10(i, vCount) {
		if(isAp[i]) {
			firstAp = i;
			break;
		}
	}
	dfsRunner(firstAp);
}

void ap(int v) {
	timer++;
	dfs[v] = timer;
	low[v] = timer;
	for10(i, (int)adj[v].size()) {
		int w = adj[v][i];
		if(dfs[w] == -1) {
			parent[w] = v;
			ap(w);
			low[v] = std::min(low[v], low[w]);
			if(dfs[v] == 1 && dfs[w] != 2) {
				if(!isAp[v]) {
					isAp[v] = true;
					apCount++;
				}
			}
			if(dfs[v] != 1 && low[w] >= dfs[v]) {
				if(!isAp[v]) {
					isAp[v] = true;
					apCount++;
				}
			}
		}
		else if(parent[v] != w) {
			low[v] = std::min(low[v], dfs[w]);
		}
	}
}

int main() {
	std::cin >> vCount;
	adj.resize(vCount);
	for10(i, vCount) {
		isAp[i] = false;
		dfs[i] = -1;
		for10(j, vCount) {
			int conn;
			std::cin >> conn;
			if(conn == 1) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	apCount = 0;
	isStrany = false;
	timer = 0;
	ap(0);
	timer = 0;
	for10(i, vCount) {
		dfs[i] = -1;
	}
	isSubGraph();
	if (isStrany) {
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}
	return 0;
}
