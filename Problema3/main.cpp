#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define MAX_N 100

#define for10(it, res) for (int it = 0; it < res; it++)
#define for11(it, res) for (int it = 1; it <= res; it++)

int nVertex;
std::vector<std::vector<int>> matrix;

int dfs[MAX_N], apCount, low[MAX_N], parent[MAX_N], dfsTimer;
bool vIsAp[MAX_N];

void readInput()
{
}

void resetData()
{
    matrix.clear();
    matrix.resize(nVertex + 1);
    apCount = 0;
    dfsTimer = 0;
    for (int i = 1; i <= nVertex; i++)
    {
        dfs[i] = -1;
        vIsAp[i] = false;
    }
}


void ap(int v)
{
    dfsTimer++;
    dfs[v] = dfsTimer;
    low[v] = dfsTimer;

    for10(i, (int)matrix[v].size())
    {
        int w = matrix[v][i];
        if (dfs[w] == -1)
        {
            parent[w] = v;
            ap(w);
            low[v] = std::min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2)
            {
                if (!vIsAp[v])
                {
                    vIsAp[v] = true;
                    apCount++;
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v])
            {
                if (!vIsAp[v])
                {
                    vIsAp[v] = true;
                    apCount++;
                }
            }
        }
        else if (parent[v] != w)
        {
            low[v] = std::min(low[v], dfs[w]);
        }
    }
}

int getApCount()
{
    for (int i = 1; i <= nVertex; i++)
    {
        if (dfs[i] == -1)
        {
            ap(i);
        }
    }
    return apCount;
}


int main()
{
    int input, counter = 0;
    while (scanf("%d", &input) != EOF)
    {
        if (input != 0){
            printf("Loop %d", counter++);
            int vertexA, vertexB, cost;
            printf("Input: %d\n", input);
            nVertex = input;
            resetData();
            for (int i = 0; i < nVertex; i++)
            {
                scanf("%d %d %d", &vertexA, &vertexB, &cost);
                printf("Cost: %d\n", cost);
                matrix[vertexA].push_back(vertexB);
                matrix[vertexB].push_back(vertexA);
                //matrix[vertexA][vertexB] = cost;
            }
            printf("Number of Servers: %d\n", getApCount());
        }
       
    }

    return 0;
}