#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <algorithm>


typedef std::pair<int, int> edge;

typedef std::pair<int, edge> edgeW;

edgeW newEdgeW;

std::vector< std::vector<edgeW> > adjMatW;

std::vector< std::vector<int> > adjMat;

bool sortWdecrease(const std::pair<int, edge> &a, const std::pair<int, edge> &b) {
	if(a.first == b.first) {
		if(a.second.first == b.second.first) {
			if(a.second.second == b.second.second) {
				return false;
        	}
        	else return (a.second.second < b.second.second);
		}
		else return (a.second.first < b.second.first);
	}
	else return (a.first > b.first);
}

int main() {

	adjMat.resize(6);
	adjMat[0].push_back(-1);
	adjMat[1].push_back(1);
	adjMat[1].push_back(2);
	adjMat[1].push_back(3);
	adjMat[2].push_back(5);
	adjMat[2].push_back(4);
	adjMat[2].push_back(7);
	adjMat[3].push_back(23);
	adjMat[4].push_back(71);
	adjMat[4].push_back(8);
	adjMat[5].push_back(9);

	for (int i = 0; i < (int)adjMat.size(); i++) {
        for (int j = 0; j < (int)adjMat[i].size(); j++)
            std::cout << adjMat[i][j] << " ";
        std::cout << std::endl;
    }

	std::sort(adjMat[2].begin(), adjMat[2].end());
	std::cout << std::endl;

	for (int i = 0; i < (int)adjMat.size(); i++) {
        for (int j = 0; j < (int)adjMat[i].size(); j++)
            std::cout << adjMat[i][j] << " " ;
		std::cout << std::endl;
    }
    std::cout << std::endl;


	/*W*/

	adjMatW.resize(3);

	adjMatW[0].push_back(std::make_pair(12, std::make_pair(1, 2)));

	return 0;
}
