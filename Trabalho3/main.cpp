#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

int t, vCount;
std::vector<std::vector<std::pair<int, int>>> adjMatrix;
std::vector<int> dfs;
std::vector<int> low;
std::vector<int> vertexStack;
std::vector<std::vector<int>> stronglyConnectedComponents;
std::vector<std::pair<long double, std::pair<int, int>>> edges;
int set[1000], rank[1000];

void makeSet()
{
    for (int i = 1; i <= vCount; i++)
    {
        set[i] = i;
        rank[i] = 0;
    }
}

int find(int a)
{
    if (set[a] != a)
    {
        set[a] = find(set[a]);
    }
    return set[a];
}

void link(int a, int b)
{
    if (rank[a] > rank[b])
    {
        set[b] = a;
    }
    else
    {
        set[a] = b;
        if (rank[a] == rank[b])
        {
            rank[b]++;
        }
    }
}

void unionSet(int a, int b)
{
    link(find(a), find(b));
}

long double kruskal()
{
    long double w, weight = 0;
    int a, b;
    makeSet();
    while (!edges.empty())
    {
        a = edges.back().second.first;
        b = edges.back().second.second;
        w = edges.back().first;
        if (find(a) != find(b))
        {
            weight += w;
            unionSet(a, b);
        }
        edges.pop_back();
    }
    return weight;
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

void countStronglyConnectedComponents()
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
    int maxKruskal = 0;

    for (int i = 0; i < (int)stronglyConnectedComponents.size(); i++)
    {
        //check number of circuits
        if ((int)stronglyConnectedComponents[i].size() > 1)
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

            if (questions > 2)
            {
                for (int j = 0; j < (int)stronglyConnectedComponents[i].size(); j++)
                {
                    if ((int)stronglyConnectedComponents[i].size() > 1)
                    {

                        int a = stronglyConnectedComponents[i][j]; // vertex a

                        for (int k = 0; k < (int)adjMatrix[stronglyConnectedComponents[i][j]].size(); k++)
                        {
                            for (int h = 0; h < (int)stronglyConnectedComponents[i].size(); h++)
                            {
                                if ((int)stronglyConnectedComponents[i].size() > 1)
                                {
                                    if (adjMatrix[stronglyConnectedComponents[i][j]][k].first == stronglyConnectedComponents[i][h])
                                    {
                                        int b = adjMatrix[stronglyConnectedComponents[i][j]][k].first;  // vertex b
                                        int c = adjMatrix[stronglyConnectedComponents[i][j]][k].second; // cost

                                        edges.push_back(std::make_pair(c, std::make_pair(a, b)));
                                    }
                                }
                            }
                        }
                    }
                }

                std::sort(edges.begin(), edges.end(), decrease);
                int answer3tmp = kruskal();

                if (answer3tmp > maxKruskal)
                {
                    maxKruskal = answer3tmp;
                }

                if (questions > 3)
                {
                    answers[3] += answer3tmp;
                }
            }
        }
    }

    answers[1] = maxPOICount;
    answers[2] = maxKruskal;

    switch (questions)
    {
    case 1:
        printf("%d\n", answers[0]);
        break;
    case 2:
        printf("%d %d\n", answers[0], answers[1]);
        break;
    case 3:
        printf("%d %d %d\n", answers[0], answers[1], answers[2]);
        break;
    case 4:
        printf("%d %d %d %d\n", answers[0], answers[1], answers[2], answers[3]);
        break;
    default:
        break;
    }
}
void clearData()
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
        int numberOfConnections, questions;
        std::cin >> vCount >> numberOfConnections >> questions;

        clearData();

        for (int j = 0; j < numberOfConnections; j++)
        {
            int A, B, weight;
            std::cin >> A >> B >> weight;
            adjMatrix[A].push_back(std::make_pair(B, weight));
        }

        //printf("Test Case: %d POIs: %d Conn: %d Questions: %d\n", i + 1, vCount, numberOfConnections, questions);

        countStronglyConnectedComponents();

        printAnswers(questions);
    }
    return 0;
}