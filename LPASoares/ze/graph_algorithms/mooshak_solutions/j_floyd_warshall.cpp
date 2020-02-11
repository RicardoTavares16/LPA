#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define INF 0x3f3f3f3f
#define println(v) cout << v << endl

void floyd_warshall(vector< vector<int> > &graph, int number_vertices) {
    int i, j, k;

    for (i = 0; i < number_vertices; i++){
        for (j = 0; j < number_vertices; j++)
        {
            if(graph[i][j])
                graph[i][j] = graph[i][j];
            else if(i == j){
                graph[i][j] = 0;
            }
            else
                graph[i][j] = INF;
        }
    }

    for (k = 0; k < number_vertices; k++) {
        for (i = 0; i < number_vertices; i++) {
            for (j = 0; j < number_vertices; j++) {
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
/*
    FOR(l,26){
        FOR(h,26) {
            if(graph[l][h] != INF)
                printf("%d\t", graph[l][h]);
            else
                printf("INF\t");
        }
        printf("\n");
    }
    printf("\n\n");
    */
}

bool is_sub_path(vector < vector < int > > &graph1, vector < vector < int > > &graph2) {
    FOR(i,26) {
        FOR(j,26){
            if(graph1[i][j] != INF && graph2[i][j] == INF) {
                return false;
            }
            else if(graph1[i][j] == INF && graph2[i][j] != INF) {
                return false;
            }
        }
    }
    return true;
}

int main(){
    int number_test_cases, n_1,n_2;
    char v_a,v_b;

    cin >> number_test_cases;
    FOR(i,number_test_cases){

        cin >> n_1;
        vector< vector<int> > f1(26, vector<int>(26));
        FOR(j,n_1){
            cin >> v_a >> v_b;
            f1[v_a-65][v_b-65] =  1;
            /*printf("A entrada %c tem valor %d e liga ao %c com valor %d (total = %d)\n"
                    ,v_a,v_a,v_b,v_b,v_a+v_b);*/
        }

        cin >> n_2;
        //alloc memory for matrix
        vector< vector<int> > f2(26, vector<int>(26));
        FOR(j,n_2){
            cin >> v_a >> v_b;
            f2[v_a-65][v_b-65] =  1;
            /*printf("A entrada %c tem valor %d e liga ao %c com valor %d (total = %d)\n"
                    ,v_a,v_a,v_b,v_b,v_a+v_b);*/
        }
        floyd_warshall(f1,26);
        floyd_warshall(f2,26);
        if(is_sub_path(f1,f2))
        {
            println("YES");
            if(i!= number_test_cases-1)
                if(i!= number_test_cases-1)
                    println("");
        }
        else
        {
            println("NO");
            if(i!= number_test_cases-1)
                println("");
        }

    }

}