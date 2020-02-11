#include <bits/stdc++.h>

using namespace std;

#define FOR(i,n) for(int i=0; i < n; i++)
#define println(v) cout << v << endl;


int max_depth = 0;
int dfsTimer =0;
vector < vector < int > > adj;
vector < bool > visited;

void depth_first_search(int u){
    visited[u] = true;
    dfsTimer ++;
    if(dfsTimer > max_depth){
        max_depth = dfsTimer;
    }
    vector<int>::iterator i;
    for(i = adj[u].begin(); i!= adj[u].end();++i){
        if(!visited[*i])
            depth_first_search(*i);
    }
}

int main(){
    int number_vertices;
    int number_edges;
    string user_name, user1, user2;
    map<string,int> database;
    cin >> number_vertices >> number_edges;
    adj.resize(number_vertices);
    visited.resize(number_vertices,false);
    FOR(i,number_vertices){
        cin >> user_name;
        database[user_name] = i;
    }

    FOR(j,number_edges){
        cin >> user1 >> user2;
        adj[database[user1]].push_back(database[user2]);
        adj[database[user2]].push_back(database[user1]);

    }

    FOR(i,number_vertices){
        if(!visited[i]){
            dfsTimer =0;
            depth_first_search(i);
        }
    }

    println(max_depth);


}