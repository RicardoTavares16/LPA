#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define MAX 1000
std::vector< std::vector< std::pair<int,int> > > matrix;

int nVertex, apCount, dfs[MAX], low[MAX], parent[MAX], dfsTimer;

bool isAP[MAX];

void resetData()
{
    matrix.clear();
    matrix.resize(nVertex + 1);
    apCount = 0;
    dfsTimer = 0;
    for (int i = 1; i <= nVertex; i++)
    {
        dfs[i] = -1;
        isAP[i] = false;
    }
}

void articulationPoints(int v)
{
    dfsTimer++;
    dfs[v] = dfsTimer;
    low[v] = dfsTimer;

    for (int i = 0; i < (int)matrix[v].size(); i++)
    {
        int w = matrix[v][i].first;
        if (dfs[w] == -1)
        {
            parent[w] = v;
            articulationPoints(w);
            low[v] = std::min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2)
            {
                if (!isAP[v])
                {
                    isAP[v] = true;
                    apCount++;
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v])
            {
                if (!isAP[v])
                {
                    isAP[v] = true;
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
            articulationPoints(i);
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
        matrix[vertexA].push_back(std::make_pair(vertexB,cost));
        matrix[vertexB].push_back(std::make_pair(vertexA,cost));
    }
}

int main()
{
    int input;
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