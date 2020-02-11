#include <bits/stdc++.h>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define INF 0x3f3f3f3f
#define println(v) cout << v << endl
int number_vertices;

void floyd_warshall(int **matrix) {
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
    int value, a,b;

    cin >> number_vertices;

    int **matrix = (int **)malloc(number_vertices * sizeof(int *));
    for (int i=0; i<number_vertices; i++)
        matrix[i] = (int *)malloc(number_vertices * sizeof(int));

    FOR(i,number_vertices){
        FOR(j,number_vertices){
            cin >> value;
            if(value == -1){
                matrix[i][j] = INF;
            }else{
                matrix[i][j] = value;
            }
        }
    }

    floyd_warshall(matrix);
    while(cin >> a >> b){
        println(matrix[a-1][b-1]);
    }
}