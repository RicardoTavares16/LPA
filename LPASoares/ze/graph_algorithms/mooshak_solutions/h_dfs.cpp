#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;

int number_places = 0;
int counter = 0;

bool dfs(vector < vector <int> > &adj, vector < bool> &visited,  int u, int number_vertices){
    visited[u] = true;
    counter++;
    FOR_ITERATOR(i,u){
        if (!visited[*i]){
            dfs(adj,visited,*i,number_vertices);
        }
    }
    return counter == number_vertices;
}

int trying(vector < int> &teste,int number_vertices){

    FOR(i,number_vertices){
        if(teste[i] == 0){
            return 0;
        }
    }
    return 1;

}

int main(){
    int number_vertices, number_edges;
    int edge_a, edge_b;

    cin >> number_vertices >> number_edges;

    vector< vector <int > > adj(number_vertices);
    vector< int > teste(number_vertices,0);

    FOR(i,number_edges){
        cin >> edge_a >> edge_b;
        adj[edge_b-1].push_back(edge_a-1);
        teste[edge_a-1] = 1;
        teste[edge_b-1] = 1;
    }

    if(trying(teste,number_vertices) == 0){
        println(0);
    }
    else{
        FOR(i,number_vertices){
            counter = 0;
            vector< bool > visited(number_vertices, false);
            if(dfs(adj,visited,i,number_vertices)){
                number_places++;
            }
        }
        println(number_places);
    }
}