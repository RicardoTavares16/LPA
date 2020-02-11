#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

typedef std::pair<int, int> edge;
typedef std::pair<int, edge> edgeW;

class compare {
	public:
		int operator() (const edgeW& a, const edgeW& b) {
			if(a.first == b.first) {
				if(a.second.first == b.second.first) {
					if(a.second.second == b.second.second) {
						return false;
					}
					else return (a.second.second > b.second.second);
				}
				else return (a.second.first > b.second.first);
			}
			else return (a.first > b.first);
		}
};

std::priority_queue<edgeW, std::vector<edgeW>, compare> edges;

int main() {

    edges.push(std::make_pair(2, std::make_pair(-2, 882)));
	edges.push(std::make_pair(12, std::make_pair(1, 2)));
    edges.push(std::make_pair(2, std::make_pair(3, 2)));
    edges.push(std::make_pair(2, std::make_pair(2, 2)));
    edges.push(std::make_pair(1, std::make_pair(1, 4)));
    edges.push(std::make_pair(-5, std::make_pair(3, 4)));
    edges.push(std::make_pair(2, std::make_pair(12, 2)));
    edges.push(std::make_pair(2, std::make_pair(-2, 2)));
    edges.push(std::make_pair(2, std::make_pair(-2, 1122)));


	while(!edges.empty()) {
		edgeW popedEdge = edges.top();
		std::cout << popedEdge.first << " ";
		std::cout << popedEdge.second.first << " ";
		std::cout << popedEdge.second.first << std::endl;
		edges.pop();
	}

	return 0;
}
