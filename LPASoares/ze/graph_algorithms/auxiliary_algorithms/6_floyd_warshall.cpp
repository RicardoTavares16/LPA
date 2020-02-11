#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define INF 0x3f3f3f3f

void floyd_warshall(vector< vector<int> > graph, int number_vertices) {

    int dist[number_vertices][number_vertices], i, j, k;

    for (i = 0; i < number_vertices; i++){
        for (j = 0; j < number_vertices; j++)
        {
            if(graph[i][j])
                dist[i][j] = graph[i][j];
            else
                dist[i][j] = INF;
        }
    }

    for (k = 0; k < number_vertices; k++) {
        for (i = 0; i < number_vertices; i++) {
            for (j = 0; j < number_vertices; j++) {
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }

    FOR(l,number_vertices){
        FOR(h,number_vertices) {
            //printf("%d length", dist[l][h]);
        }
    }
}

int main(){
    int number_test_cases, n_1,n_2;
    char v_a,v_b;

    cin >> number_test_cases;
    FOR(i,number_test_cases){

        cin >> n_1;
        //alloc memory for matrix
        vector< vector<int> > f1(n_1, vector<int>(n_1));


        printf("\nGRAFO 1 :\n");
        FOR(j,n_1){
            cin >> v_a >> v_b;

           // f1[v_a-1][v_b-1] =  v_a + v_b;
            printf("A entrada %c tem valor %d e liga ao %c com valor %d (total = %d)\n"
                    ,v_a,v_a,v_b,v_b,v_a+v_b);
            }

        cin >> n_2;
        //alloc memory for matrix
        vector< vector<int> > f2(n_2, vector<int>(n_2));
        printf("\nGRAFO 2 :\n");
        FOR(j,n_2){
            cin >> v_a >> v_b;
            //f2[v_a-1][v_b-1] =  v_a + v_b;
            printf("A entrada %c tem valor %d e liga ao %c com valor %d (total = %d)\n"
                    ,v_a,v_a,v_b,v_b,v_a+v_b);
        }
        floyd_warshall(f1,n_1);
        floyd_warshall(f2,n_2);

    }

}