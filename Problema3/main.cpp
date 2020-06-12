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

        #ifdef DEBUG
        printf("%d %d %d\n", vertexA, vertexB, cost);
        #endif
        //Make adjancy matrix with costs
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
        nVertex = input;

        #ifdef DEBUG
        printf("Input: %d\n", input);
        #endif

        resetData(); //Clear matrix, reset counters
        readInput(); //Start reading input

        //Number of servers
        int serverNumber = articulationCount();

        if(serverNumber == 0){
            printf("no server\n");
        }
        else{
            printf("%d %d %d\n", serverNumber, 0, 0);
            
            #ifdef DEBUG
            for(int i = 0; i < nVertex; i++){
                printf("Vertex %d: AP: %d \n", i, isAP[i]);
            }
            #endif
        }
    }

    return 0;
}