#include <bits/stdc++.h>

using namespace std;
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl
void topological_sort_util(int v, bool visited[], stack<int>& stack, vector < vector < int > > adj)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topological_sort_util(*i, visited, stack, adj);

    // Push current vertex to stack which stores result
    stack.push(v);
}


void topological_sort(int number_vertices, vector < vector < int > > adj)
{
    stack<int> Stack;

    bool* visited = new bool[number_vertices];
    for (int i = 0; i < number_vertices; i++)
        visited[i] = false;

    for (int i = 0; i < number_vertices; i++)
        if (!visited[i])
            topological_sort_util(i, visited, Stack, adj);

    while(!Stack.empty()){
        println(Stack.top());
        Stack.pop();
    }
}

int main(){
    int number_vertices, number_functions,function_number;

    cin >> number_vertices;
    vector< vector <int > > adj(number_vertices);
    FOR(i,number_vertices){
        cin >> number_functions;
        FOR(j,number_functions) {
            cin >> function_number;
            adj[i].push_back(function_number);
        }
    }
    topological_sort(number_vertices,adj);
}