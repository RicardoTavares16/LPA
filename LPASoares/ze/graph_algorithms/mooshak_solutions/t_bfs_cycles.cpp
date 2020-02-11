#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl
#define INF 0x3f3f3f3f

using namespace std;

int bfs(vector < vector < int > > &adj, vector < int > &depth, int u){

    queue<int> q;
    q.push(u);
    depth[u] = 1;
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        FOR_ITERATOR(i,f) {

            if(depth[*i] == 0) {
                depth[*i] = depth[f] + 1;
                q.push(*i);
            }
            else if(*i == u){
                return depth[f];
            }
        }
    }
    return INF;
}

int main() {
    int number_vertices, value;
    cin >> number_vertices;
    vector < vector < int > > adj(number_vertices);

    FOR(i, number_vertices) {
        FOR(j, number_vertices) {
            cin >> value;
            if (value != 0) {
                adj[i].push_back(j);
            }
        }
    }
    int result = 0;
    int shortest_cycle_number = INF;
    FOR(i,number_vertices){

        vector<int> depth(number_vertices, 0);
        result = bfs(adj,depth,i);
        if(result < shortest_cycle_number)
            shortest_cycle_number = result;
    }
    if(shortest_cycle_number == INF){
        println("0");
    }
    else{
        println(shortest_cycle_number);
    }
    return 0;
}
