#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>

std::vector<std::vector<int>> adj;
bool isAp[100];
int vCount, apCount, dfsTmp;
int dfs[100], low[100], parent[100];

void ap(int v)
{
    dfsTmp++;
    dfs[v] = dfsTmp;
    low[v] = dfsTmp;

    for (int i = 0; i < (int)adj[v].size(); i++)
    {
        int w = adj[v][i];
        if (dfs[w] == -1)
        {
            parent[w] = v;
            ap(w);
            low[v] = std::min(low[v], low[w]);
            if (dfs[v] == 1 && dfs[w] != 2)
            {
                if (!isAp[v])
                {
                    isAp[v] = true;
                    apCount++;
                }
            }
            if (dfs[v] != 1 && low[w] >= dfs[v])
            {
                if (!isAp[v])
                {
                    isAp[v] = true;
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
    for (int i = 1; i <= vCount; i++)
    {
        if (dfs[i] == -1)
        {
            ap(i);
        }
    }
    return apCount;
}

void readNodes()
{
    std::string str;

    while (getline(std::cin, str))
    {
        char *cstr;
        cstr = new char[str.size() + 1];
        strcpy(cstr, str.c_str());

        int end2, end1 = atoi(strtok(cstr, " "));
        if (end1 == 0){
            break;
        }
        char *end2C = strtok(NULL, " ");

        do
        {
            end2 = atoi(end2C);
            adj[end1].push_back(end2);
            adj[end2].push_back(end1);
            end2C = strtok(NULL, " ");

        } while (end2C);
    }
}

void reset()
{
    adj.clear();
    adj.resize(vCount + 1);

    apCount = 0;
    dfsTmp = 0;

    for (int i = 1; i <= vCount; i++)
    {
        dfs[i] = -1;
        isAp[i] = false;
    }
}

int main()
{
    std::string str;

    while (getline(std::cin, str))
    {
        vCount = std::atoi(str.c_str());
        if (vCount == 0)
        {
            break;
        }
        
        reset();
        readNodes();
        std::cout << getApCount() << "\n";
    }
    return 0;
}