#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define INF 0x3f3f3f3f
#define println(v) cout << v << endl


void floyd_warshall(int **matrix, int number_vertices) {
    int i, j, k;

    for (k = 0; k < number_vertices; k++) {
        for (i = 0; i < number_vertices; i++) {
            for (j = 0; j < number_vertices; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
}

int main(){
    int number_vertices, number_edges, number_values, a, b, cost, v_a,v_b;

    cin >> number_vertices;

    int **matrix = (int **)calloc(number_vertices,sizeof(int*));
    for(int i = 0; i < number_vertices; i++)
        matrix[i] = (int*)calloc(number_vertices,sizeof(int));



    cin >> number_edges;

    FOR(i,number_edges){
        cin >> a >> b >> cost;
        matrix[a-1][b-1] = cost;
    }

    for (int i = 0; i < number_vertices; i++){
        for (int j = 0; j < number_vertices; j++)
        {
            if(matrix[i][j])
                matrix[i][j] = matrix[i][j];
            else if(i == j){
                matrix[i][j] = 0;
            }
            else
                matrix[i][j] = INF;
        }
    }



    floyd_warshall(matrix, number_vertices);

    cin >> number_values;
    FOR(i, number_values){

        cin >> v_a >> v_b;
        if(matrix[v_a-1][v_b-1]!= INF)
            println(matrix[v_a-1][v_b-1]);
        else
            println("Impossible!");
    }

}