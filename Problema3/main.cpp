#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <limits>


#define MAX 1000
#define for11(it, res) for(int it = 1; it <= res; it++)
#define INF std::numeric_limits<int>::max() / 2;

std::vector< std::vector< std::pair<int,int> > > matrix;

int nVertex, apCount, dfs[MAX], low[MAX], parent[MAX], dfsTimer;
bool isAP[MAX];
int APs[MAX];

int **dist;

void alloc() {
    dist = (int**) malloc((nVertex + 1) * sizeof(int*));
    for11(i, nVertex) {
        dist[i] = (int*) malloc((nVertex + 1) * sizeof(int));
    }
        //printf("ALLOC INPUT %d\n", nVertex);

}

void unAlloc() {
    for11(i, nVertex) {
        free(dist[i]);
    }
    free(dist);
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
    alloc();
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

        dist[vertexA][vertexB] = cost;

        //printf("%d %d cost: %d\n", vertexA, vertexB, cost);
        //printf("VertexA %d first: %d second: %d\n", vertexA, matrix[vertexA][vertexB].first, matrix[vertexA][vertexB].second);
    }
}

void floydWarshall() {
    int i, j, k;

    for (i = 1; i <= nVertex; i++){
        for (j = 1; j <= nVertex; j++)
        {
            if(dist[i][j])
                dist[i][j] = dist[i][j];
            else if(i == j){
                dist[i][j] = 0;
            }
            else
                dist[i][j] = INF;
        }
    }

    for (k = 1; k <= nVertex; k++) {
        for (i = 1; i <= nVertex; i++) {
            for (j = 1; j <= nVertex; j++) {
                dist[i][j] = std::min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

void readQueries() {
    int s, t;
    while(std::cin >> s >> t) {
        std::cout << dist[s][t] << std::endl;
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
            //   for (int i = 1; i <= nVertex; i++)
            // {
            //     for (int j = 1; j <= nVertex; j++)
            //     {
            //         printf("%d %d cost: %d\n", i, j, dist[i][j]);
            //     }
            // }
        }
        else if(serverNumber == 1){
            printf("%d %d %d\n", serverNumber, 0, 0);
            
            #ifdef DEBUG
            for(int i = 0; i < nVertex; i++){
                printf("Vertex %d: AP: %d \n", i, isAP[i]);
            }
            #endif
            //  for (int i = 1; i <= nVertex; i++)
            // {
            //     for (int j = 1; j <= nVertex; j++)
            //     {
            //         printf("%d %d cost: %d\n", i, j, dist[i][j]);
            //     }
            // }
        }
        else{
              

            floydWarshall();
            int linkServersCost = 0;
            
            for(int i = 1; i <= nVertex; i++){
                if(isAP[i]){
                    for(int j = i; j <= nVertex-i; j++){
                        if(isAP[j]){
                            if(dist[i][j] != std::numeric_limits<int>::max() / 2){
                                linkServersCost += dist[i][j];
                            }
                        }
                    }
                }
            }
            //  for (int i = 1; i <= nVertex; i++)
            // {
            //     for (int j = 1; j <= nVertex; j++)
            //     {
            //         if(dist[i][j] != 0 && dist[i][j] != std::numeric_limits<int>::max() / 2){
            //         printf("%d %d cost: %d\n", i, j, dist[i][j]);
            //         }
            //     }
            // }

            printf("%d %d %d\n", serverNumber, linkServersCost, 0);
         
        }
        //readQueries();
        unAlloc();
    }

    return 0;
}