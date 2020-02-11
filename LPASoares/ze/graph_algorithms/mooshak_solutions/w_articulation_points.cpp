#include <bits/stdc++.h>

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

using namespace std;

int total_weight = 0;
int dfsTime = 0;

void articulation_points(int v, vector< vector < pair < int, int > > > &adj,vector<int> &dfs, vector <int> &low, vector<int> &parent, vector <bool> &is_ap) {
    dfsTime++;
    dfs[v] = low[v] = dfsTime;
    vector<pair <int, int> >::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        int w = i->first;
        int weight = 0;
        if (dfs[w] == -1) {
            parent[w] = v;
            articulation_points(w,adj,dfs,low,parent,is_ap);
            low[v] = min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    for(int k = 0;  k < (int)adj[v].size(); k++){
                        weight += adj[v][k].second;
                    }
                    if(weight > total_weight){
                        total_weight = weight;
                    }
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v]) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    for(int k = 0; k < (int)adj[v].size(); k++){
                        weight += adj[v][k].second;
                    }
                    if(weight > total_weight){
                        total_weight= weight;
                    }
                }
            }
        } else if (parent[v] != w) {
            low[v] = min(low[v], dfs[w]);
        }
    }
}

int main(){

    int number_vertices, number_crossings,weight,destination;

    while(cin >> number_vertices){
        dfsTime = 0;
        total_weight = 0;
        vector < vector < pair < int, int > > > adj(number_vertices);
        vector < int > dfs(number_vertices,-1);
        vector < int > low(number_vertices);
        vector < int > parent(number_vertices);
        vector < bool > is_ap(number_vertices,false);
        FOR(i,number_vertices){
            cin >> number_crossings;

            FOR(j,number_crossings){
                cin >> destination >> weight;
                adj[i].push_back(make_pair(destination-1,weight));
                //adj[destination-1].push_back(make_pair(i,weight));
            }
        }
        FOR(j,number_vertices){
            if (dfs[j]==-1){
                articulation_points(j,adj,dfs,low,parent,is_ap);
            }
        }
        if(total_weight ==0){
            println("Well designed city!");
        }else{
            println(total_weight);
        }
    }


}