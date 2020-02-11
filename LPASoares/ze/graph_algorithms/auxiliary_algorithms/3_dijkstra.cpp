#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

using namespace std;

void shortestPath(vector< vector <pair<int,int> > > adj, int v, int src, int finish)
{
    priority_queue < pair<int,int> , vector < pair <int, int> > , greater<pair < int, int > > > pq;
    vector<int> dist(v, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;

        pq.pop();
        vector< pair <int,int> >::iterator x;
        for (x = adj[u].begin(); x != adj[u].end(); ++x) {
            int vertex = x->first;
            int weight = x->second;

            if (dist[vertex] > dist[u] + weight) {
                dist[vertex] = dist[u] + weight;
                pq.push(make_pair(dist[vertex], vertex));
            }
        }
    }
    println(dist[finish-1]);
}

int main()
{
    int n;
    int finish,value;

    cin >> n >> finish;
    vector < vector < pair < int, int > > > adj(n,vector<pair < int, int> >(n));
    FOR(i,n){
        FOR(j,n+1){
            cin >> value;
            if(j!=0 && value != -1){
                adj[i].push_back(make_pair(j-1, value));
            }
        }
    }
    shortestPath(adj, n, 0,finish);
    return 0;
}

