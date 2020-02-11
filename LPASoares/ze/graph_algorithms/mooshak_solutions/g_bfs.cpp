#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

int bfs(vector < vector < int > > adj, vector < bool > &visited, int u){

    queue<int> q;

    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        FOR_ITERATOR(i,f) {
            if (!visited[*i]) {
                q.push(*i);
                visited[*i] = true;
            }
            else if(visited[*i] && *i == u){
                return u;
            }
        }
    }
    return -1;
}

int main(){
    int number_vertices, number_functions,function_number;

    cin >> number_vertices;
    vector< vector <int > > adj(number_vertices);
    FOR(i,number_vertices){
        cin >> number_functions;
        FOR(j,number_functions) {
            cin >> function_number;
            adj[i].push_back(function_number);
        }
    }

    vector < int > result;

    FOR(i,number_vertices){
        vector < bool > visited(number_vertices,false);
        int vertex = bfs(adj,visited,i);
        if(vertex!=-1){
            result.push_back(vertex);
        }
    }

    sort(result.begin(),result.end());

    vector<int>::iterator i;
    for(i = result.begin(); i!= result.end(); i++){
        int t = *i;
        println(t);
    }
}