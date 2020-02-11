#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <algorithm>


typedef std::pair<int, int> edge;
typedef std::pair<int, edge> edgeW;

std::vector<edgeW> edges;

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


    edges.push_back(std::make_pair(2, std::make_pair(-2, 882)));
	edges.push_back(std::make_pair(12, std::make_pair(1, 2)));
    edges.push_back(std::make_pair(2, std::make_pair(3, 2)));
    edges.push_back(std::make_pair(2, std::make_pair(2, 2)));
    edges.push_back(std::make_pair(1, std::make_pair(1, 4)));
    edges.push_back(std::make_pair(-5, std::make_pair(3, 4)));
    edges.push_back(std::make_pair(2, std::make_pair(12, 2)));
    edges.push_back(std::make_pair(2, std::make_pair(-2, 2)));
    edges.push_back(std::make_pair(2, std::make_pair(-2, 1122)));

	std::sort(edges.begin(), edges.end(), sortWdecrease);

	for(int i = 0; i < (int)edges.size(); i++) {
		std::cout << edges[i].first << " " << edges[i].second.first << " " << edges[i].second.second << std::endl;
	}

	return 0;
}
