#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>

#define INF std::numeric_limits<int>::max()/2

#define for10(it, res) for(int it = 0; it < res; it++)

int vCount, source, target, dist[20], adj[20][20];

int bellmanFord() {
	for10(k, vCount - 1) {
		for10(i, vCount) {
			for10(j, vCount) {
				if(adj[i][j] != 0) {
					if(dist[j] > dist[i] + adj[i][j]) {
						dist[j] = dist[i] + adj[i][j];
					}
				}
			}
		}
	}
	for10(i, vCount) {
		for10(j, vCount) {
			if(adj[i][j] != 0) {
				if(dist[j] > dist[i] + adj[i][j]) {
					return -1;
				}
			}
		}
	}
	return dist[target];
}

int main() {
	std::cin >> vCount >> source >> target;
	for10(i, vCount) {
		dist[i] = INF;
		for10(j, vCount) {
			int weight;
			std::cin >> weight;
			adj[i][j] = weight;
		}
	}
	dist[source] = 0;
	int res = bellmanFord();
	if(res == -1) std::cout << "Negative Cycle" << std::endl;
	else std::cout << res << std::endl;
	return 0;
}
