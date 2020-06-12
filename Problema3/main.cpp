#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <iomanip>

#define MAX 1000

std::vector<std::vector<std::pair<int, int>>> matrix;

int nVertex, apCount, dfs[MAX], low[MAX], parent[MAX], dfsTimer;
bool isAP[MAX];
int **adjency;

std::vector<std::pair<long double, std::pair<int, int>>> edges;
int vSet[MAX], vRank[MAX];

int parent2[MAX];

int find(int i)
{
    while (parent2[i] != i)
        i = parent2[i];
    return i;
}

void union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent2[a] = b;
}

int kruskal()
{
    int mincost = 0;

    for (int i = 1; i <= nVertex; i++)
        parent2[i] = i;

    int edge_count = 0;
    while (edge_count < nVertex - 1)
    {
        int min = std::numeric_limits<int>::max() / 2, a = -1, b = -1;
        for (int i = 1; i <= nVertex; i++)
        {
            for (int j = 1; j <= nVertex; j++)
            {
                if (find(i) != find(j) && adjency[i][j] < min)
                {
                    min = adjency[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);

        edge_count++;
        mincost += min;
    }
    return mincost;
}

void freeArray()
{
    for (int i = 1; i <= nVertex; i++)
    {
        free(adjency[i]);
    }
    free(adjency);
    //printf("UNALLOC INPUT %d\n", nVertex);
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
        isAP[i] = false;
    }

    adjency = (int **)malloc((nVertex + 1) * sizeof(int *));
    for (int i = 1; i <= nVertex; i++)
    {
        adjency[i] = (int *)malloc((nVertex + 1) * sizeof(int));
    }

    edges.clear();
    edges.resize(nVertex + 1);
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

bool decrease(const std::pair<long double, std::pair<int, int>> &a, const std::pair<long double, std::pair<int, int>> &b)
{
    if (a.first == b.first)
    {
        if (a.second.first == b.second.first)
        {
            return (a.second.second < b.second.second);
        }
        else
            return (a.second.first < b.second.first);
    }
    else
        return (a.first > b.first);
}

void readInput()
{
    std::string str;
    while (getline(std::cin, str))
    {
        //Get new line
        char *cstr;
        cstr = new char[str.size() + 1];
        strcpy(cstr, str.c_str());
        char *token;

#ifdef DEBUG
        printf("String: %s\n", cstr);
#endif

        //Read first int
        token = strtok(cstr, " ");

        int vertexA = atoi(token);
        if (vertexA == 0)
        {
            break;
        }
        //Second int
        token = strtok(NULL, " ");
        int vertexB = atoi(token);
        //Third int
        token = strtok(NULL, " ");
        int cost = atoi(token);


        //printf("Input %d %d Cost: %d\n", vertexA, vertexB, cost);

        //Make adjancy matrix with costs
        adjency[vertexA][vertexB] = cost;
        matrix[vertexA].push_back(std::make_pair(vertexB, cost));
        matrix[vertexB].push_back(std::make_pair(vertexA, cost));

        edges.push_back(std::make_pair(adjency[vertexA][vertexB], std::make_pair(vertexA, vertexB)));

        std::sort(edges.begin(), edges.end(), decrease);
    }
}

void floydWarshall()
{
    int i, j, k;

    for (i = 1; i <= nVertex; i++)
    {
        for (j = 1; j <= nVertex; j++)
        {
            if (adjency[i][j])
                adjency[i][j] = adjency[i][j];
            else if (i == j)
            {
                adjency[i][j] = 0;
            }
            else
                adjency[i][j] = std::numeric_limits<int>::max() / 2;
        }
    }

    for (k = 1; k <= nVertex; k++)
    {
        for (i = 1; i <= nVertex; i++)
        {
            for (j = 1; j <= nVertex; j++)
            {
                adjency[i][j] = std::min(adjency[i][j], adjency[i][k] + adjency[k][j]);
            }
        }
    }
}

void printMatrix()
{
    for (int i = 1; i <= nVertex; i++)
    {
        for (int j = 1; j <= nVertex; j++)
        {
            printf("Matrix -> A: %d B: %d Cost: %d\n", i, j, adjency[i][j]);
        }
    }
    printf("\n");
}

int main()
{
    int input;
    std::string str;

    while (getline(std::cin, str))
    {
        input = std::atoi(str.c_str());
        nVertex = input;

#ifdef DEBUG
        printf("Input: %d\n", input);
#endif

        resetData(); //Clear matrix, reset counters
        readInput(); //Start reading input

        //Number of servers
        int serverNumber = articulationCount();

        if (serverNumber == 0)
        {
            printf("no server\n");
            //printMatrix();
        }
        else if (serverNumber == 1)
        {
            printf("%d %d %d\n", serverNumber, 0, 0);
            printMatrix();

#ifdef DEBUG
            for (int i = 0; i < nVertex; i++)
            {
                printf("Vertex %d: AP: %d \n", i, isAP[i]);
            }
#endif
        }
        else
        {

            int linkServersCost = 0;
            int treeCost = 0;

            floydWarshall();
            treeCost = kruskal();

            for (int i = 1; i <= nVertex; i++)
            {
                if (isAP[i])
                {
                    for (int j = i; j <= nVertex - i; j++)
                    {
                        if (isAP[j])
                        {
                            if (adjency[i][j] != std::numeric_limits<int>::max() / 2)
                            {
                                linkServersCost += adjency[i][j];
                            }
                        }
                    }
                }
            }
            // for (int i = 1; i <= nVertex; i++)
            // {
            //     for (int j = 1; j <= nVertex; j++)
            //     {
            //         if (adjency[i][j] != 0 && adjency[i][j] != std::numeric_limits<int>::max() / 2)
            //         {
            //             printf("Adjency after Warshall: %d %d cost: %d\n", i, j, adjency[i][j]);
            //         }
            //     }
            // }

            printf("%d %d %d\n", serverNumber, linkServersCost, treeCost);
        }
        freeArray();
    }

    return 0;
}