#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)

using namespace std;

double **adj;
vector < pair < int, int > > vertices;
vector < pair < double, pair < int, int > >  > edges;
int v_set[750], v_rank[750];

void make_set(int number_vertices) {
    FOR(i, number_vertices) {
        v_set[i] = i;
        v_rank[i] = 0;
    }
}

int find_set(int a) {
    if(v_set[a] != a) {
        v_set[a] = find_set(v_set[a]);
    }
    return v_set[a];
}

void link(int a, int b) {
    if (v_rank[a] > v_rank[b]) {
        v_set[b] = a;
    }
    else {
        v_set[a] = b;
        if(v_rank[a]==v_rank[b]) {
            v_rank[b]++;
        }
    }
}

void union_set(int a, int b) {
    link(find_set(a), find_set(b));
}



double calculate_distance(int x1, int x2, int y1, int y2){
    return (double) sqrt( fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2));
}

double kruskal(int number_vertices){

    double minimum_path = 0;
    make_set(number_vertices);
    sort(edges.begin(),edges.end());

    for(int i=0; i < (int)edges.size(); i++){
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        double w = edges[i].first;

        if(find_set(u)!= find_set(v)){
            union_set(u,v);
            minimum_path += w;
        }
    }
    return minimum_path;
}

int main(){

    int number_vertices, number_connections, x, y, a,b;


    while(cin >> number_vertices){

        adj = (double**) malloc(number_vertices * sizeof(double*));
        for(int i = 0; i < number_vertices; ++i){
            adj[i] = (double*) malloc(number_vertices * sizeof(double));
        }

        for(int i = 0 ; i < number_vertices; ++i){
            cin >> x >> y;
            vertices.push_back(make_pair(x,y));
        }
        int x1, x2, y1, y2;
        for(int i=0; i < number_vertices; ++i){
            for(int j=i+1; j < number_vertices; ++j){

                x1 = vertices[i].first;
                y1 = vertices[i].second;
                x2 = vertices[j].first;
                y2 = vertices[j].second;
                double distance = calculate_distance(x1,x2,y1,y2);
                adj[i][j] = distance;
                adj[j][i] = distance;
            }
        }

        cin >> number_connections;

        for(int i=0 ; i < number_connections; ++i){
            cin >> a >> b;
            adj[a-1][b-1] = 0.0;
            adj[b-1][a-1] = 0.0;
        }

        for(int i=0; i < number_vertices; ++i){
            for(int j=i+1; j <number_vertices; ++j){
                if(i!=j){
                    edges.push_back(make_pair(adj[i][j],make_pair(i,j)));
                }
            }
        }

        printf("%.2lf\n",kruskal(number_vertices));

        for(int i = 0; i < number_vertices; ++i){
            free(adj[i]);
        }
        free(adj);
        vertices.clear();
        edges.clear();

    }
}