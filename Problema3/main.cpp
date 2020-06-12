#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define MAX 1000

#define for10(it, res) for (int it = 0; it < res; it++)
#define for11(it, res) for (int it = 1; it <= res; it++)

int nVertex;
std::vector<std::vector<int>> matrix;

int dfs[MAX], apCount, low[MAX], parent[MAX], dfsTimer;
bool vIsAp[MAX];

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

int articulationCount()
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

void readInput()
{
    std::string str;

    while (getline(std::cin, str))
    {
        char *cstr;
        cstr = new char[str.size() + 1];
        strcpy(cstr, str.c_str());
        char *token;
        //printf("String: %s\n", cstr);
        token = strtok(cstr, " ");

        int vertexA = atoi(token);
        if (vertexA == 0)
        {
            break;
        }

        token = strtok(NULL, " ");
        int vertexB = atoi(token);

        token = strtok(NULL, " ");
        int cost = atoi(token);

        //printf("%d %d %d\n", vertexA, vertexB, cost);
        matrix[vertexA].push_back(vertexB);
        matrix[vertexB].push_back(vertexA);
        //matrix[vertexA][vertexB] = cost;
    }
}

int main()
{
    int input, counter = 0;
    std::string str;

    while (getline(std::cin, str))
    {
        input = std::atoi(str.c_str());
        if (input == 0)
            break;
        nVertex = input;
        //printf("Input: %d\n", input);

        resetData();
        readInput();

        int serverNumber = articulationCount();
        if(serverNumber == 0){
            printf("no server\n");
        }
        else{
            printf("%d %d %d\n", serverNumber, 0, 0);
        }
        //printf("Number of Servers: %d\n", articulationCount());
    }

    return 0;
}