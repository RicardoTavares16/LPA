#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

void bfs(vector < vector < int > > adj, vector < bool > visited, int u)
{
    queue<int> q;

    q.push(u);
    visited[u] = true;
    println(u);
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        // Enqueue all adjacent of f and mark them visited
        FOR_ITERATOR(i,f) {
            if (!visited[*i]) {
                q.push(*i);
                visited[*i] = true;
                println(*i);
            }
        }
    }
}

int main(){
    int number_vertices, number_edges;
    int edge_a, edge_b;

    cin >> number_vertices;
    vector< vector <int > > adj(number_vertices);
    vector<bool> visited(number_vertices, false);
    FOR(i,number_edges){
        cin >> edge_a >> edge_b;
        adj[edge_a].push_back(edge_b);
    }

    bfs(adj,visited,1);
}
