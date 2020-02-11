#include <iostream>
#include <limits>
#include <cstdlib>


#define INF std::numeric_limits<int>::max()/2

#define for11(it, res) for(int it = 1; it <= res; it++)

int vCount, eCount;
int **dist;

void alloc() {
    dist = (int**) malloc((vCount + 1) * sizeof(int*));
    for11(i, vCount) {
        dist[i] = (int*) malloc((vCount + 1) * sizeof(int));
    }
}

void unAlloc() {
    for11(i, vCount) {
        free(dist[i]);
    }
    free(dist);
}

void floydwarshall() {
    for11(k, vCount) {
        for11(i, vCount) {
            for11(j, vCount) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void readInput() {
    for11(i, vCount) {
        for11(j, vCount) {
            int data;
            std::cin >> data;
            if(data == -1) {
                dist[i][j] = INF;
            }
            else dist[i][j] = data;
        }
    }
}

void readQueries() {
    int s, t;
    while(std::cin >> s >> t) {
        std::cout << dist[s][t] << std::endl;
    }
}

int main() {
    std::cin >> vCount;
    alloc();
    readInput();
    floydwarshall();
    readQueries();
    unAlloc();
	return 0;
}
