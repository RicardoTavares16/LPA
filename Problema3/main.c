#include <stdio.h>
#include <stdlib.h>

int nVertex;
int adj [50][50];

void readInput() {
 
}


int main()
{
    int input, i;
    while (scanf("%d", &input) != EOF)
    {
        if (input == 0) break;
        int vertexA, vertexB, cost;
        printf("%d\n", input);
        nVertex = input;
        for (i = 0; i < nVertex; i++)
        {
             scanf("%d %d %d", &vertexA, &vertexB, &cost);
             printf("%d", cost);
             adj[vertexA][vertexB] = cost;
        }

    }

    return 0;
}