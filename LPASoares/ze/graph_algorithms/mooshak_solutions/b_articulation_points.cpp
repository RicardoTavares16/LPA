#include <bits/stdc++.h>

#define FOR(i, n) for(int i = 0; i < n; ++i)

using namespace std;



void art_points_utility(int u,  vector < int > &disc, vector < int > &low, vector < int > &parent, vector < bool > &art_points, vector < vector < int > > adj, vector < bool > visited) {
    static int time = 0;
    int children = 0;
    disc[u] = low[u] = ++time;
    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (!visited[v]) {
            children++;
            parent[v] = u;
            art_points_utility(v, disc, low, parent, art_points,adj,visited);
            low[u] = min(low[u], low[v]);
            if (parent[u] == -1 && children > 1)
                art_points[u] = true;

            if (parent[u] != -1 && low[v] >= disc[u])
                art_points[u] = true;
        } else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

void APUtil(int u,  vector < int > &disc, vector < int > &low, vector < int > &parent, vector < bool > &art_points, vector < vector < int > > &adj, vector < bool > &visited) {
    static int time = 0;
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (!visited[v]) {
            children++;
            parent[v] = u;
            APUtil(v, disc, low, parent, art_points, adj,visited);
            low[u] = min(low[u], low[v]);
            if (parent[u] == -1 && children > 1)
                art_points[u] = true;

            if (parent[u] != -1 && low[v] >= disc[u])
                art_points[u] = true;
        } else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}


void articulation_points(int number_vertices, vector < vector < int > > adj) {

    bool is_ap_none = true;
    vector < int > parent(number_vertices,-1);
    vector < bool > art_points(number_vertices,false);
    vector < int > disc(number_vertices);
    vector < int > low(number_vertices);
    vector < bool > visited(number_vertices, false);

    vector < pair < int, int > > solutions;

    for (int i = 0; i < number_vertices; i++)
        if (!visited[i])
            APUtil(i,disc, low, parent,art_points,adj,visited);

    for (int i = 0; i < number_vertices; i++) {
        if (art_points[i]) {
            is_ap_none = false;
            vector<int>::iterator j;
            for (j = adj[i].begin(); j != adj[i].end(); ++j) {

                int pos = j - adj[i].begin();
                if (low[i] > disc[adj[i][pos]]) {
                    if (i < adj[i][pos])
                    {
                        solutions.push_back(make_pair(i,adj[i][pos]));
                    }

                    else
                    {
                        solutions.push_back(make_pair(adj[i][pos],i));

                    }

                }
            }
        }
    }

    if (is_ap_none) {
        printf("No road\n");
    }else{
        sort(solutions.begin(),solutions.end()/*,greater< pair < int, int > > ()*/);
        vector< pair < int, int > >::iterator itr;
        for(itr = solutions.begin(); itr != solutions.end(); ++itr){
            cout << itr->first << " " << itr->second << endl;
        }
    }
}




int main() {
    int number_positions, number_edges, vertex_a, vertex_b;

    while (cin >> number_positions >> number_edges) {
        vector < vector < int > > adj(number_positions);
        FOR(i, number_edges) {
            cin >> vertex_a >> vertex_b;
            adj[vertex_a].push_back(vertex_b);
            adj[vertex_b].push_back(vertex_a);
        }
        articulation_points(number_positions,adj);
    }
    return 0;
}
