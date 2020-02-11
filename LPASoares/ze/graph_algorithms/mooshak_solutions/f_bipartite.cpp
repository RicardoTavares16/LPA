#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

vector < vector < int > > adj;
vector < int > color_array;

bool bfs(int u){

    queue<int> q;

    q.push(u);
    color_array[u] = 1;
    while (!q.empty()) {
        int f = q.front();
        q.pop();

        FOR_ITERATOR(i,f) {
            if (color_array[*i] == -1) {
                q.push(*i);
                color_array[*i] = 1 - color_array[f];
            }
            else if(color_array[*i] == color_array[f]){
                return false;
            }
        }
    }
    return true;
}

bool is_bipartite(int number_vertices) {
    FOR(j, number_vertices) {
        if (color_array[j] == -1) {
            if (!bfs(j)) {
                return false;
            }
        }
    }
    return true;
}

int main(){
   int number_vertices, number_edges, a, b;


    while(cin >> number_vertices >> number_edges){
        adj.clear();
        adj.resize(number_vertices);
        color_array.clear();
        color_array.resize(number_vertices,-1);
        FOR(i,number_edges){
            cin >> a >> b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        if(is_bipartite(number_vertices))
            println("NOT SURE");
        else
            println("NO");
    }
}