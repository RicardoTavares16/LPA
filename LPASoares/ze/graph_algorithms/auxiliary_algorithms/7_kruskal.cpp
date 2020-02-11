#include <bits/stdc++.h>

#define FOR(i,n) for(int i = 0; i < n; ++i)


using namespace std;

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
/*
double kruskal(int number_vertices, vector < vector < double > > &values) {
    double w, weight = 0;
    make_set(number_vertices);

    int u, v;
    while(!values.empty()) {
        u = values.back().first;
        v = values.back().second;
        w = values.back().first;
        if(find_set(u) != find_Set(v)) {
            weight += w;
            union_set(u, v);
        }
        values.pop_back();
    }
    return weight;


}*/

int main(){
    int number_vertices, number_edges, x, y, a, b;
    while(cin >> number_vertices){
        vector < pair < int, int > > coordinates(number_vertices);
        vector < vector < double > > values(number_vertices, vector< double >(number_vertices));
        vector < vector < int > > adj(number_vertices);
        FOR(i,number_vertices){
            cin >> x >> y;
            coordinates[i].first = x;
            coordinates[i].second = y;
            printf("x: %d y: %d\n",x,y);
        }
        cin >> number_edges;
        FOR(j,number_edges){
            cin >> a >> b;
            //adj[a-1].push_back(b-1);
            //adj[b-1].push_back(a-1);
            int x1, x2 , y1, y2;
            x1 = coordinates[a-1].first;
            x2 = coordinates[b-1].first;
            y1 = coordinates[a-1].second;
            y2 = coordinates[b-1].second;
            printf("x1 : %d x2: %d y1: %d y2: %d\n",x1,x2,y1,y2);
            values[b-1][a-1] = values[a-1][b-1] = sqrt( fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2));
        }
        //double result = kruskal(number_vertices);
        //printf("%.2lf\n", result);
    }


}