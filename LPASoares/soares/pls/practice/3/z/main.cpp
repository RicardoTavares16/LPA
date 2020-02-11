#include <iostream>
#include <cstdlib>
#include <vector>

int vCount, width, height, **matrix;
bool *isVisited;

std::vector< std::vector<int> > adj;

void allocData() {
    isVisited = (bool*) malloc((height * width + 1) * sizeof(bool));
    adj.resize(height * width + 1);
    vCount = 0;
    matrix = (int**) malloc((height + 1)* sizeof(int*));
    for(int i = 0; i < height; i++) {
        matrix[i] = (int*) malloc((width +1) * sizeof(int));
        for(int j = 0; j < width; j++) {
            matrix[i][j] = -1;
        }
    }
}

void readInput() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            char chr;
            std::cin >> chr;
            if(chr == 43) {
                matrix[i][j] = vCount;
                if(i == 0) {
                    if(j > 0 && j < width - 1) {
                        if(matrix[i][j-1] != -1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                    else if ((j == width - 1) && width != 1) {
                        if(matrix[i][j-1] != -1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                }
                else if (i > 0 && i < height - 1) {
                    if(j == 0) {
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if((matrix[i-1][j+1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i-1][j+1]);
                            adj[matrix[i-1][j+1]].push_back(vCount);
                        }
                    }
                    else if(j > 0 && j < width - 1) {
                        if(matrix[i-1][j-1] != -1) {
                            adj[vCount].push_back(matrix[i-1][j-1]);
                            adj[matrix[i-1][j-1]].push_back(vCount);
                        }
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if(matrix[i-1][j+1] != -1) {
                            adj[vCount].push_back(matrix[i-1][j+1]);
                            adj[matrix[i-1][j+1]].push_back(vCount);
                        }
                        if(matrix[i][j-1] != -1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                    else if (j == width - 1) {
                        if((matrix[i-1][j-1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i-1][j-1]);
                            adj[matrix[i-1][j-1]].push_back(vCount);
                        }
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if((matrix[i][j-1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                }
                else if (i == height - 1) {
                    if(j == 0) {
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if((matrix[i-1][j+1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i-1][j+1]);
                            adj[matrix[i-1][j+1]].push_back(vCount);
                        }
                    }
                    else if(j > 0 && j < width - 1) {
                        if(matrix[i-1][j-1] != -1) {
                            adj[vCount].push_back(matrix[i-1][j-1]);
                            adj[matrix[i-1][j-1]].push_back(vCount);
                        }
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if(matrix[i-1][j+1] != -1) {
                            adj[vCount].push_back(matrix[i-1][j+1]);
                            adj[matrix[i-1][j+1]].push_back(vCount);
                        }
                        if(matrix[i][j-1] != -1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                    else if (j == width - 1) {
                        if((matrix[i-1][j-1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i-1][j-1]);
                            adj[matrix[i-1][j-1]].push_back(vCount);
                        }
                        if(matrix[i-1][j] != -1) {
                            adj[vCount].push_back(matrix[i-1][j]);
                            adj[matrix[i-1][j]].push_back(vCount);
                        }
                        if((matrix[i][j-1] != -1) && width != 1) {
                            adj[vCount].push_back(matrix[i][j-1]);
                            adj[matrix[i][j-1]].push_back(vCount);
                        }
                    }
                }
                vCount++;
            }
        }
    }
}

void dfs(int v) {
    isVisited[v] = true;
    for(int i = 0; i < (int)adj[v].size(); i++) {
        int u = adj[v][i];
        if(!isVisited[u]) {
            dfs(u);
        }
    }
}

int countComponents() {
    int nComp = 0;
    for(int i = 0; i < vCount; i++) {
        isVisited[i] = false;
    }
    for(int i = 0; i < vCount; i++) {
        if(!isVisited[i]) {
            nComp++;
            dfs(i);
        }
    }
    return nComp;
}

int main() {
    std::cin >> height >> width;
    allocData();
    readInput();
    std::cout << countComponents() << std::endl;
	return 0;
}
