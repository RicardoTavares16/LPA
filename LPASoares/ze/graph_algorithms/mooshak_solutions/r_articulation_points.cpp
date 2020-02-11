#include <bits/stdc++.h>

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

using namespace std;

int max_number_associates = 0;
int dfsTime = 0;

void articulation_points(int v, vector< vector < int > > &adj,vector<int> &dfs, vector <int> &low, vector<int> &parent, vector <bool> &is_ap) {
    dfsTime++;
    dfs[v] = low[v] = dfsTime;
    vector< int >::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        int w = *i;
        if (dfs[w] == -1) {
            parent[w] = v;
            articulation_points(w,adj,dfs,low,parent,is_ap);
            low[v] = min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    if((int) adj[v].size() > max_number_associates){
                        max_number_associates = (int)adj[v].size();
                    }
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v]) {
                if(!is_ap[v]){
                    is_ap[v] = true;
                    if((int) adj[v].size() > max_number_associates){
                        max_number_associates = (int)adj[v].size();
                    }
                }
            }
        } else if (parent[v] != w) {
            low[v] = min(low[v], dfs[w]);
        }
    }
}

int main(){

    int number_vertices, number_associates,associate_id;

    while(cin >> number_vertices){
        dfsTime = 0;
        max_number_associates = 0;
        vector < vector < int  > > adj(number_vertices);
        vector < int > dfs(number_vertices,-1);
        vector < int > low(number_vertices);
        vector < int > parent(number_vertices);
        vector < bool > is_ap(number_vertices,false);
        FOR(i,number_vertices){
            cin >> number_associates;

            FOR(j,number_associates){
                cin >> associate_id;
                adj[i].push_back(associate_id-1);
                //adj[associate_id-1].push_back(make_pair(i,weight));
            }
        }
        FOR(j,number_vertices){
            if (dfs[j]==-1){
                articulation_points(j,adj,dfs,low,parent,is_ap);
            }
        }
        if(max_number_associates ==0){
            println("Strong network");
        }else{
            println(max_number_associates);
        }
    }


}