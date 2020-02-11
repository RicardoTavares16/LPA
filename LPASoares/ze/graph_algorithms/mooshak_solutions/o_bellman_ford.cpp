#include <bits/stdc++.h>

using namespace std;


#define INF 0x3f3f3f3f
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector< pair < int, int > >::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl


bool bellman_ford( vector< vector < pair<int, int> > > &adj,int number_vertices,vector< pair<int, int> > &shortestDistances) {

    FOR(i, number_vertices) {
        shortestDistances[i].first = INF;
        shortestDistances[i].second = -1;
    }
    shortestDistances[0].first = 0;
    shortestDistances[0].second = 0;

    FOR(i, number_vertices) {
        FOR(j, number_vertices) {

            FOR_ITERATOR(k, j) {
                if (k->second + shortestDistances[j].first < shortestDistances[k->first].first) {
                    shortestDistances[k->first].first = k->second + shortestDistances[j].first;
                    shortestDistances[k->first].second = j;
                }
            }
        }
    }

    FOR(j, number_vertices) {
        FOR_ITERATOR(k, j) {
            if (k->second + shortestDistances[j].first < shortestDistances[k->first].first) {
                return true;
            }
        }
    }
    return false;
}

int main(){
        int number_teste_cases, number_vertices, number_edges,a,b,value;

        cin >> number_teste_cases;

        FOR(i,number_teste_cases){
            cin >> number_vertices >> number_edges;
            vector < vector < pair < int, int >  > > adj(number_vertices);
            vector< pair<int, int> > shortestDistances(number_vertices);

            FOR(j,number_edges){
                cin >> a >> b >> value;
                adj[a].push_back(make_pair(b,value));
            }
            if(bellman_ford(adj,number_vertices,shortestDistances)){
                println("possible");
            } else{
                println("not possible");
            }
        }
}