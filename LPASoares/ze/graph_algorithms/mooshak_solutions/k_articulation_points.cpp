#include <bits/stdc++.h>

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

using namespace std;

int number_critical_points;
int dfsTime = 0;

void articulation_points(int v, vector< vector < int > > &adj,vector<int> &dfs, vector <int> &low, vector<int> &parent, vector <bool> &is_ap ) {
    dfsTime++;
    dfs[v] = low[v] = dfsTime;
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        int w = *i;
        if (dfs[w] == -1) {
            parent[w] = v;
            articulation_points(w,adj,dfs,low,parent,is_ap);
            low[v] = min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    number_critical_points++;
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v]) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    number_critical_points++;
                }
            }
        } else if (parent[v] != w) {
            low[v] = min(low[v], dfs[w]);
        }
    }
}

int main() {
    string line;
    int number_vertices;
    int tt;
    int vertex;

    while(getline(cin,line)){
        istringstream iss(line);

        iss >> number_vertices;
        vector < vector < int > > adj(number_vertices);
        vector < int > dfs(number_vertices,-1);
        vector < int > low(number_vertices);
        vector < int > parent(number_vertices);
        vector < bool > is_ap(number_vertices,false);
        number_critical_points = 0;
        dfsTime = 0;

        if(number_vertices == 0){
            break;
        }
        while(getline(cin,line)){
            istringstream iss(line);
            iss>>vertex;
            if(vertex == 0){
                break;
            }
            while (iss >> tt) {
                adj[vertex-1].push_back(tt-1);
                adj[tt-1].push_back(vertex-1);

            }
        }

        FOR(j,number_vertices){
            if (dfs[j]==-1){
                articulation_points(j,adj,dfs,low,parent,is_ap);
            }
        }
        println(number_critical_points);

    }
    return 0;
}
