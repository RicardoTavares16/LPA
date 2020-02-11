#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int vertexCount;
int timer;
int stage;
std::vector<int> dfs;
std::vector<int> low;
std::vector< std::vector<int> > adjMatrix;
std::vector< std::vector<int> > adjDepend;
std::vector< std::vector<int> > stronglyConnectedGroups;
std::vector< int > vertexStronglyConnectedGroup;
std::vector< std::pair<int, int> > stronglyConnectedGroupsDegree;
std::vector<int> vertexStack;
std::vector< std::vector<int> > solution;

bool decrease(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	if(a.first == b.first) {
		if(a.second == b.second) {
            return true;
		}
		else return (a.second < b.second);
	}
	else return (a.first > b.first);
}

void tarjan(int v) {
    timer++;
    dfs[v] = timer;
    low[v] = timer;
    vertexStack.push_back(v);
    for(int i = 0; i < (int)adjMatrix[v].size(); i++) {
        if(dfs[adjMatrix[v][i]] == -1) {
            tarjan(adjMatrix[v][i]);
            low[v] = std::min(low[v], low[adjMatrix[v][i]]);
        }
        else {
            for(int j = 0; j < (int)vertexStack.size(); j++) {
                if (vertexStack[j] == adjMatrix[v][i]) {
                    low[v] = std::min(low[v], dfs[adjMatrix[v][i]]);
                }
            }
        }
    }
    if (low[v] == dfs[v]) {
        int i = stronglyConnectedGroups.size();
        stronglyConnectedGroups.resize(i + 1);
        int tempVertex;
        do {
            tempVertex = vertexStack[vertexStack.size()-1];
            vertexStack.pop_back();
            stronglyConnectedGroups[i].push_back(tempVertex);
        } while (tempVertex != v);
    }
}

void getStronglyConnectedGroups() {
    timer = 0;
    for(int i = 1; i <= vertexCount; i++) {
        dfs[i] = -1;
    }
    for(int i = 1; i <= vertexCount; i++) {
        if(dfs[i] == -1) {
            tarjan(i);
        }
    }
    vertexStronglyConnectedGroup.resize(vertexCount + 1);
    for(int i = 0; i < (int)stronglyConnectedGroups.size(); i++) {
        for(int j = 0; j < (int)stronglyConnectedGroups[i].size(); j++) {
            vertexStronglyConnectedGroup[stronglyConnectedGroups[i][j]] = i;
        }
    }
}

void getStronglyConnectedGroupsDegree() {
    std::vector< int > stronglyConnectedGroupDegree;
    stronglyConnectedGroupDegree.resize(stronglyConnectedGroups.size());
    for(int i = 1; i <= vertexCount; i++) {
        for(int j = 0; j < (int)adjMatrix[i].size(); j++) {
            if(vertexStronglyConnectedGroup[i] != vertexStronglyConnectedGroup[adjMatrix[i][j]]) {
                stronglyConnectedGroupDegree[vertexStronglyConnectedGroup[i]]++;
            }
        }
    }
    stronglyConnectedGroupsDegree.resize(stronglyConnectedGroupDegree.size());

    for(int i = 0; i < (int)stronglyConnectedGroupDegree.size(); i++) {
        stronglyConnectedGroupsDegree[i].first = stronglyConnectedGroupDegree[i];
        stronglyConnectedGroupsDegree[i].second = i;
    }
    std::sort(stronglyConnectedGroupsDegree.begin(), stronglyConnectedGroupsDegree.end(), decrease);
}

void popBackAndUpdateDegree() {
    int temp = stronglyConnectedGroupsDegree[(int)stronglyConnectedGroupsDegree.size() - 1].second;
    stronglyConnectedGroupsDegree.pop_back();
    std::sort(stronglyConnectedGroupsDegree.begin(), stronglyConnectedGroupsDegree.end(), decrease);
    for(int i = 0; i < (int)stronglyConnectedGroups[temp].size(); i++) {
        for(int k = 0; k < (int)adjDepend[stronglyConnectedGroups[temp][i]].size(); k++) {
        int group = vertexStronglyConnectedGroup[adjDepend[stronglyConnectedGroups[temp][i]][k]];
            for(int j = 0; j < (int)stronglyConnectedGroupsDegree.size(); j++) {
                if (stronglyConnectedGroupsDegree[j].second == group) {
                    stronglyConnectedGroupsDegree[j].first--;
                    break;
                }
            }
        }
    }
    std::sort(stronglyConnectedGroupsDegree.begin(), stronglyConnectedGroupsDegree.end(), decrease);
}

void parseSolution() {
    int numberOfPops = 0;
    while(stronglyConnectedGroupsDegree.empty() == false) {
    int solutionSize = solution.size();
    solution.resize(solutionSize + 1);
        for(int i = (int)stronglyConnectedGroupsDegree.size() - 1; i >= 0; i--) {
            if(stronglyConnectedGroupsDegree[i].first == 0) {
                numberOfPops++;
                for(int j = 0; j < (int)stronglyConnectedGroups[stronglyConnectedGroupsDegree[i].second].size(); j++) {
                        solution[solutionSize].push_back(stronglyConnectedGroups[stronglyConnectedGroupsDegree[i].second][j]);
                }
                if(stronglyConnectedGroupsDegree.size() == 1) {
                stronglyConnectedGroupsDegree.pop_back();
                }
            }
            else {
                for(int j = 0; j < numberOfPops; j++) popBackAndUpdateDegree();
                numberOfPops = 0;
                break;
            }
        }
    }
    for(int i = 0; i < (int)solution.size(); i++) {
        std::sort(solution[i].begin(), solution[i].end());
    }

}

void printSolution() {
    for(int i = 0; i < (int)solution.size(); i++) {
        std::cout << "Stage " << i+1 << ":" << std::endl;
        for(int j = 0; j < (int)solution[i].size()-1; j++) {
            std::cout << solution[i][j] << " ";
        }
        std::cout << solution[i][solution[i].size()-1] << std::endl;
    }
}

int main() {
    std::cin >> vertexCount;

    adjMatrix.resize(vertexCount + 1);
    adjDepend.resize(vertexCount + 1);
    dfs.resize(vertexCount + 1);
    low.resize(vertexCount + 1);

    for(int i = 0; i < vertexCount; i++) {
        int j;
        std::cin >> j;
        int temp;
        std::cin >> temp;
        while (temp != 0) {
            adjDepend[temp].push_back(j);
            adjMatrix[j].push_back(temp);
            std::cin >> temp;
        }
    }

    getStronglyConnectedGroups();

    getStronglyConnectedGroupsDegree();

    parseSolution();

    printSolution();

	return 0;
}
