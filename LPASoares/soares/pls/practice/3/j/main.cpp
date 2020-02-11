#include <iostream>

#define for1(it1, res) for(int it1 = 0; it1 < res; it1++)
#define for2(it1, it2, res) for(int it1 = 0; it1 < res; it1++) for(int it2 = 0; it2 < res; it2++)
#define for3(it1, it2, it3, res) for(int it1 = 0; it1 < res; it1++) for(int it2 = 0; it2 < res; it2++) for(int it3 = 0; it3 < res; it3++)

#define INF 1000

#define ALPHABET_COUNT 26

//#define DEBUG_DIST
//#define DEBUG_CHECK_PATHS

int dist1[ALPHABET_COUNT][ALPHABET_COUNT];
int dist2[ALPHABET_COUNT][ALPHABET_COUNT];

void resetDists() {
    for1(i, ALPHABET_COUNT) {
        for1(j, ALPHABET_COUNT) {
            dist1[i][j] = INF;
            dist2[i][j] = INF;
        }
    }
}

void readInput() {
    int edgesCount;

    std::cin >> edgesCount;
    for1(i, edgesCount) {
        char end1, end2;
        std::cin >> end1 >> end2;

        dist1[end1 - 65][end2 - 65] = 1;
        dist1[end1 - 65][end1 - 65] = 0;
        dist1[end2 - 65][end2 - 65] = 0;
    }

    std::cin >> edgesCount;
    for1(i, edgesCount) {
       char end1, end2;
        std::cin >> end1 >> end2;

        dist2[end1 - 65][end2 - 65] = 1;
        dist2[end1 - 65][end1 - 65] = 0;
        dist2[end2 - 65][end2 - 65] = 0;
    }
}

void floydWarshall(int dist[][ALPHABET_COUNT]) {
    for3(k, i, j, ALPHABET_COUNT) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
        }
    }
    #ifdef DEBUG_DIST
    for2(i, j, ALPHABET_COUNT) {
        if(dist[i][j] == INF) {
            std::cout << "-1 ";
        }
        else if (dist[i][j] > 9) std::cout << dist[i][j] << " ";
        else std::cout << " " << dist[i][j] << " ";
        if(j == ALPHABET_COUNT - 1) std::cout << std::endl;
    }
    std::cout << std::endl;
    #endif // DEBUG

}

bool checkPaths() {
    for2(i, j, ALPHABET_COUNT) {
        if(dist1[i][j] != INF && dist2[i][j] == INF) {
            return false;
        }
        else if(dist1[i][j] == INF && dist2[i][j] != INF) {
            return false;
        }
    }
    return true;
}

int main() {
    int numberTests;
    std::cin >> numberTests;

    for1(i, numberTests) {
        resetDists();
        readInput();
        floydWarshall(dist1);
        floydWarshall(dist2);
        std::cout << (checkPaths() ? "YES" : "NO") << std::endl;
        if(i != (numberTests - 1)) std::cout << std::endl;
    }

    return 0;
}
