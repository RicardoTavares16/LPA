#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

using namespace std;
vector < vector < int > > adj;
vector < bool > visited;
int depthh;


pair<int,int> bfs(int u, vector < int > &depth){

    queue<int> q;
    q.push(u);
    depth[u] = 0;
    int highest_depth = 0;
    visited[u] = true;
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        FOR_ITERATOR(i,f) {
            if (!visited[*i]) {
                depth[*i] = depth[f] + 1;
                if(depth[*i]> highest_depth)
                    highest_depth = depth[*i];
                q.push(*i);
                visited[*i] = true;
            }

        }

    }
    return make_pair( highest_depth,u);
}

pair < int, int > dfs(int u, int depth){
    visited[u] = true;
    //depth_array[u] = depth;
    if(depthh < depth)
        depthh = depth;
    FOR_ITERATOR(i,u){
        if (!visited[*i]){

            dfs(*i,depth+1);

        }
    }
    //printf("vertex: %d depth: %d\n",u+1,depth);
    return make_pair(depthh,u);
}


int main(){
    int number_vertices,a,b;
    cin >> number_vertices;
    adj.resize(number_vertices);
    vector < pair < int, int > > shortest(number_vertices);
    vector < pair < int, int > > tallest(number_vertices);

    FOR(i,number_vertices-1){
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    FOR(j,number_vertices){
        visited.clear();
        visited.resize(number_vertices,false);
        vector < int > depth(number_vertices,0);
        depthh = 1;
        tallest.push_back(dfs(j,0));
        visited.clear();
        visited.resize(number_vertices,false);
        depth.clear();
        depth.resize(number_vertices,0);
        shortest.push_back(bfs(j,depth));
    }

    sort(tallest.begin(),tallest.end(),greater<pair <int, int > >());
    sort(shortest.begin(),shortest.end());


    vector < int > result_shortest;
    vector < int > result_tallest;

    vector < pair < int, int > >::iterator i;
    int aux=0;
    for(i = shortest.begin();i!=shortest.end();i++){
        if(i->first!=0 && aux==0){
            result_shortest.push_back(i->second+1);
            aux = i->first;
        }
        else if(i->first!=0 && i->first == aux){
            result_shortest.push_back(i->second+1);
        }
    }

    vector < pair < int, int > >::iterator j;
    aux = 0;
    for(j = tallest.begin();j!=tallest.end();j++){
        if(j->first!=0 && aux==0){
            result_tallest.push_back(j->second+1);
            aux = j->first;
        }
        else if(j->first!=0 && j->first == aux){
            result_tallest.push_back(j->second+1);
        }
    }

    sort(result_shortest.begin(),result_shortest.end());
    sort(result_tallest.begin(),result_tallest.end());


    printf("Shortest: ");
    FOR(k,(int)result_shortest.size()){
        if(k!=(int)result_shortest.size()-1)
            printf("%d ",result_shortest[k]);        else
            printf("%d\n",result_shortest[k]);
    }

    printf("Tallest: ");
    FOR(l,(int)result_tallest.size()){
        if(l!=(int)result_tallest.size()-1)
            printf("%d ",result_tallest[l]);
        else
            printf("%d\n",result_tallest[l]);
    }

}