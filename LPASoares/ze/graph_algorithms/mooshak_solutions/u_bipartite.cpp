#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

vector < vector < int > > adj;

bool bfs(vector < int > &color_array, int u){

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

bool is_bipartite(vector < int > &color_array, int number_vertices) {
    FOR(j, number_vertices) {
        if (color_array[j] == -1) {
            if (!bfs(color_array, j)) {
                return false;
            }
        }
    }
    return true;
}

int main(){
    int number_vertices,value;
    cin >> number_vertices;
    adj.resize(number_vertices);
    vector < int > color_array(number_vertices,-1);
    FOR(i,number_vertices){
        FOR(j,number_vertices){
            cin >> value;
            if(value!=0){
                adj[i].push_back(j);
            }
        }
    }

    if(is_bipartite(color_array,number_vertices))
        println("True");
    else
        println("False");
}
