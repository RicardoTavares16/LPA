#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

using namespace std;
// A class that represents an undirected graph
class Graph
{
    int V; // No. of vertices
    vector<int> *adj; //vector of adjacency lists
    void APUtil(int u, bool visited[], int disc[], int low[],int parent[], bool ap[]);
public:
    // Constructor
    Graph(int V){

        this->V = V;
        this->adj = new vector<int>[V];
    }

    ~Graph(){
            delete[] adj;

    }
    void addEdge(int v, int w); // function to add an edge to graph
    void AP(); // prints articulation points
};


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v); // Note: the graph is undirected
}

// A recursive function that find articulation points using DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
// ap[] --> Store articulation points
void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[])
{
    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static int time = 0;

    // Count of children in DFS Tree
    int children = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to this
    vector<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i; // v is current adjacent of u

        // If v is not visited yet, then make it a child of u
        // in DFS tree and recur for it
        if (!visited[v])
        {
            children++;
            parent[v] = u;
            APUtil(v, visited, disc, low, parent, ap);

            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u] = min(low[u], low[v]);

            // u is an articulation point in following cases

            // (1) u is root of DFS tree and has two or more chilren.
            if (parent[u] ==-1 && children > 1)
                ap[u] = true;

            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if (parent[u] !=  && low[v] >= disc[u])
                ap[u] = true;
        }

            // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

// The function to do DFS traversal. It uses recursive function APUtil()
void Graph::AP()
{
    // Mark all the vertices as not visited

    bool is_ap_none = true;
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V]; // To store articulation points

    // Initialize parent and visited, and ap(articulation point) arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = ;
        visited[i] = false;
        ap[i] = false;
    }

    // Call the recursive helper function to find articulation points
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++)
        if (!visited[i])
            APUtil(i, visited, disc, low, parent, ap);

    for (int i = 0; i < V; i++){
        if (ap[i]){
            is_ap_none = false;
            vector<int>::iterator j;
            for (j = adj[i].begin(); j != adj[i].end(); ++j) {
                int pos = j - adj[i].begin();

                if (low[i] > low[adj[i].at(static_cast<unsigned int>(pos))]) {
                    if(i < adj[i].at(static_cast<unsigned int>(pos))) printf("%d %d\n", i,adj[i].at(static_cast<unsigned int>(pos)));
                    else printf("%d %d\n",adj[i].at(static_cast<unsigned int>(pos)),i);
                }
            }
        }
    }
    if(is_ap_none){
        printf("No road\n");
    }
}

// Driver program to test above function
int main()
{
    int number_positions, number_edges, vertex_a,vertex_b;

    while(cin >> number_positions >> number_edges){
        Graph graph(number_positions);
        FOR(i,number_edges){
            cin >> vertex_a >> vertex_b;
            graph.addEdge(vertex_a,vertex_b);

        }
        graph.AP();
    }
    return 0;
}
