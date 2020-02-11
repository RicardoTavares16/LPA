#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

void dfs(vector < vector <int> > adj, vector < bool> &visited,  int u){
    visited[u] = true;
    printf("%d < --- ",u);
    for(unsigned int i=0; i < visited.size(); i++){
        printf("visited[%d] = %s ",i, visited[i] ? "true" : "false");
    }
    println("");
    FOR_ITERATOR(i,u){
        if (!visited[*i]){
            dfs(adj,visited,*i);
        }
    }
}

int main(){
    int number_vertices, number_edges;
    int edge_a, edge_b;

    cin >> number_vertices >> number_edges;

    vector< vector <int > > adj(number_vertices);
    vector< bool > visited(number_vertices, false);

    FOR(i,number_edges){
        cin >> edge_a >> edge_b;
        adj[edge_a].push_back(edge_b);
    }

    dfs(adj,visited,0);

}