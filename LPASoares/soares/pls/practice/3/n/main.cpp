#include <iostream>
#include <queue>
#include <cstdlib>
#include <limits>

#define INF std::numeric_limits<int>::max() / 2

int vCount, eCount, **dist;
std::vector< std::vector< std::pair<int,int> > > adj;

void alloc() {
    dist = (int**) malloc((vCount + 1) * sizeof(int*));
    for(int i = 0; i <= vCount; i++) {
        dist[i] = (int*) malloc((vCount + 1) * sizeof(int));
    }
    adj.resize(vCount + 1);
}

void readInput() {
    int end1, end2, weight;
    std::cin >> vCount >> eCount;
    alloc();
    for(int i = 0; i < eCount; i++) {
        std::cin >> end1 >> end2 >> weight;
        adj[end1].push_back(std::make_pair(end2, weight));
    }
}

void floydWarshall(){
    for(int i = 1; i <= vCount; i++) {
        for(int j = 1; j <= vCount; j++) {
            dist[i][j] = INF;
        }
    }
    for(int i = 1; i <= vCount; i++) {
        dist[i][i] = 0;
        for(int j = 0; j < (int)adj[i].size(); j++) {
            int u = adj[i][j].first;
            dist[i][u] = adj[i][j].second;
        }
    }
    for(int k = 1; k <= vCount; k++) {
        for(int i = 1; i <= vCount; i++) {
            for(int j = 1; j <= vCount; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void processQuery() {
    int nQueries, source, target;
    std::cin >> nQueries;
    for(int i = 0; i < nQueries; i++) {
        std::cin >> source >> target;
        if (dist[source][target] == INF) {
            std::cout << "Impossible!" << std::endl;
        }
        else {
            std::cout << dist[source][target] << std::endl;
        }
    }
}

int main() {
	readInput();
	floydWarshall();
    processQuery();
	for(int i = 0; i <= vCount; i++) {
        free(dist[i]);
    }
	free(dist);
	return 0;
}
