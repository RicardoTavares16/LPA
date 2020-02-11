#include <bits/stdc++.h>

using namespace std;


int bellmanFord( vector< vector < pair<int, int> > > &adjacencyList,int vertices,int startVertex,vector< pair<int, int> > & shortestDistances)
{
    vector< pair<int, int> >::iterator traverse;
    int i, j;

    // Initialisation
    for (i = 0; i <= vertices; ++i) {
        shortestDistances[i].first = INT_MAX;
        shortestDistances[i].second = -1;
    }

    // Setting distance to source = 0
    shortestDistances[startVertex].first = 0;
    shortestDistances[startVertex].second = 0;

    // The Algorithm that computes Shortest Distances
    for (i = 1; i <= vertices - 1; ++i) {    // Runs 'vertices - 1' times = O(|V|)
        for (j = 1; j <= vertices; ++j) {    // Runs as many times as the edges = O(|E|)
            // The code ahead basically explores the whole of Adjcency List,
            // covering one edge once, so the runtime of the code in this
            // block is O(|E|)

            traverse = adjacencyList[j].begin();

            while (traverse != adjacencyList[j].end()) {
                if (shortestDistances[j].first == INT_MAX) {
                    // Important...!
                    //traverse = traverse->next;
                    ++traverse;
                    continue;
                }

                // Checking for Relaxation
                if ((*traverse).second + shortestDistances[j].first <
                    shortestDistances[(*traverse).first].first) {
                    // Relaxation
                    shortestDistances[(*traverse).first].first = (*traverse).second
                                                                 + shortestDistances[j].first;
                    shortestDistances[(*traverse).first].second = j;
                }

                ++traverse;
            }
        }
    }

    // Checking for Negative Cycles
    for (j = 1; j <= vertices; ++j) {
        traverse = adjacencyList[j].begin();

        while (traverse != adjacencyList[j].end()) {
            // Checking for further relaxation
            if ((*traverse).second + shortestDistances[j].first <
                shortestDistances[(*traverse).first].first) {
                // Negative Cycle found as further relaxation is possible
                return j;
            }

            ++traverse;
        }
    }

    return -1;
}