#include <iostream>
#include <vector>
#include <queue>

#define for10(it, res) for(int it = 0; it < res; it++)
#define for11(it, res) for(int it = 1; it <= res; it++)

int vCount, eCount, source, target;
int depth[11];
std::vector< std::vector<int> > adj;

int bfs(int v) {
	std::queue<int> q;
	depth[v] = 0;
	q.push(v);
	while(!q.empty()) {
		int t = q.front();
		q.pop();
		for10(i, (int)adj[t].size()) {
			int u = adj[t][i];
			if(depth[u] == -1) {
				depth[u] = depth[t] + 1;
				q.push(u);
			}
			if(u == target) {
				return depth[u];
			}
		}
	}
	return 0;
}

int main() {
	std::cin >> vCount >> eCount;
	std::cin >> source >> target;
	adj.resize(vCount + 1);
	for10(i, eCount) {
		int s, t;
		std::cin >> s >> t;
		adj[s].push_back(t);
	}
	for11(i, vCount) {
		depth[i] = -1;
	}
	std::cout << bfs(source) << std::endl;
	return 0;
}
