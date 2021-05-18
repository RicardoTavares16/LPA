#include <iostream>
#include <cstdlib>
#include <vector>

int t;
std::vector<std::vector<std::pair<int, int>>> adjMatrix;
std::vector<int> dfs;
std::vector<int> low;
std::vector<int> vertexStack;
std::vector<std::vector<int>> stronglyConnectedComponents;

void tarjan(int v)
{
    t++;
    low[v] = t;
    dfs[v] = t;
    vertexStack.push_back(v);
    for (int i = 0; i < (int)adjMatrix[v].size(); i++)
    {
        if (dfs[adjMatrix[v][i].first] == -1)
        {
            tarjan(adjMatrix[v][i].first);
            low[v] = std::min(low[v], low[adjMatrix[v][i].first]);
        }
        else
        {
            for (int j = 0; j < (int)vertexStack.size(); j++)
            {
                if (vertexStack[j] == adjMatrix[v][i].first)
                {
                    low[v] = std::min(low[v], dfs[adjMatrix[v][i].first]);
                }
            }
        }
    }
    if (low[v] == dfs[v])
    {
        int i = stronglyConnectedComponents.size();
        stronglyConnectedComponents.resize(i + 1);
        int tmpVertex;

        do
        {
            tmpVertex = vertexStack[vertexStack.size() - 1];
            vertexStack.pop_back();
            stronglyConnectedComponents[i].push_back(tmpVertex);
        } while (tmpVertex != v);
    }
}

void countStronglyConnectedComponents(int vCount)
{
    t = 0;
    for (int i = 1; i <= vCount; i++)
    {
        dfs[i] = -1;
    }
    for (int i = 1; i <= vCount; i++)
    {
        if (dfs[i] == -1)
        {
            tarjan(i);
        }
    }
}

void printAnswers(int questions)
{
    int answers[4] = {0};
    int maxPOICount = 0;

    for (int i = 0; i < (int)stronglyConnectedComponents.size(); i++)
    {
        //check number of circuits
        if (stronglyConnectedComponents[i].size() > 1)
        {
            answers[0]++;

            if (questions > 1)
            {
                //get max circuit size
                if ((int)stronglyConnectedComponents[i].size() > maxPOICount)
                {
                    maxPOICount = stronglyConnectedComponents[i].size();
                }
            }
        }
    }

    answers[1] = maxPOICount;

    for (int i = 0; i < questions; i++)
    {
        printf("%d ", answers[i]);
    }
    printf("\n");
}
void clearData(int vCount)
{
    adjMatrix.clear();
    adjMatrix.resize(vCount + 1);
    low.resize(vCount + 1);
    dfs.resize(vCount + 1);
    stronglyConnectedComponents.resize(vCount + 1);
}

int main()
{
    int testCases;
    std::cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int poiCount, numberOfConnections, questions;
        std::cin >> poiCount >> numberOfConnections >> questions;

        clearData(poiCount);

        for (int j = 0; j < numberOfConnections; j++)
        {
            int A, B, weight;
            std::cin >> A >> B >> weight;
            adjMatrix[A].push_back(std::make_pair(B, weight));
        }

        //printf("Test Case: %d POIs: %d Conn: %d Questions: %d\n", i + 1, poiCount, numberOfConnections, questions);

        countStronglyConnectedComponents(poiCount);

        printAnswers(questions);
    }
    return 0;
}
