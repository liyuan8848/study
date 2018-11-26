/*
Given a directed graph, find out whether the graph is strongly connected or not. A directed graph is strongly connected if there is a path between any two pair of vertices.

It is easy for undirected graph, we can just do a BFS and DFS starting from any vertices, if BFS of DFS visits all vertices, then the given undirected graph is connected. This approach won't work for a directed graph. 

How to do for directed graph?

A simple idea is to use a all pair shortest path algorithm like Floyd Warshall or dind Transitive Closure of graph. Time complexity of this method would be O(v3).

A better idea can be strongly connected components(SCC) algorithm. We can find all SCCs in O(V+E) time. if number of SCCs is one, then graph is strongly connected. The algorithm for SCC does extra work as it finds all SCCs.

Following is Kosaraju's DFS based simple algorithm that does two DFS traversals of Graph:
1) initialize all vertices as not visited.
2) Do a DFS traversal of graph starting from any arbitrary vertex. v. If DFS traversal doesn't visit all vertices, then return false
3) Reverse all arcs ( or find transpose or reverse of graph)
4) Mark all vertices as not-visited in reversed Graph
5) Do a DFS traversal of reversed graph starting from the same vretex v(same as step 2). If DFS traversal doesn't visit all vertices, then return false. Otherwise return ture. 

The idea is, if every node can be reached from a vertex v, and every node can reach v. then the graph is strongly connected. In step 2, we check if all vertices are reachable from v, In step 4, we check if all vertices can reach v. (In reversed graph, if all vertices are reachable from v, then all all vertices can reach v in original graph)

*/

#include <iostream>
#include <list>
#include <stack>

using namespace std;

class Graph
{
    int V;
    list<int> *adj;

    // A recursive fundtion to print DFS starting from v
    void DFSUtil(int v, bool visited[]);

    public:
    Graph(int V) { this->V = V, adj = new list<int>[V]; }
    ~Graph () { delete [] adj; }

    //Method to add an edge
    void addEdge(int v, int w);

    // The main function that returns true if the graph is strong connected, otherwise false
    bool isSC();

    // Function that returns reverse (or transpose ) of this graph
    Graph getTranspose();
};

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // recur for all the vertices adjacent to this vertex
    list<int>::iterator ir;
    for(ir = adj[v].begin(); ir != adj[v].end(); ir++)
        if (!visited[*ir])
            DFSUtil(*ir, visited);
}

// Function that returns reverse (or transpose ) of this graph
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator ir;
        for(ir=adj[v].begin(); ir!= adj[v].end(); ir++)
        {
            g.adj[*ir].push_back(v);
        }


    }

    return g;


}



void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

// The main function that returns true if graph is strongly connected
bool Graph::isSC()
{
// step 1 : mark all vertices as not visited
bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

// step 2: do DFS traversal starting from first vertex
DFSUtil(0, visited);

// if DFS traversal doesn't visit all vertices, then return false
    for (int i = 0; i < V; i++)
    {
        if(visited[i]==false)
            return false;
    }
 // step 3, create a reversed graph
    Graph gr = getTranspose();

    // step 4: mark all the verices as not visited( for second DFS)
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // step 5: Do DFS for reversed graph starting from first vertice
    gr.DFSUtil(0, visited);

    // if all vertices are not visited in second DFS, then return false
    for (int i = 0; i < V; i++)
    {
        if(visited[i]==false)
            return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    // Driver program to test above functions 

 
    Graph g1(5); 
    g1.addEdge(0, 1); 
    g1.addEdge(1, 2); 
    g1.addEdge(2, 3); 
    g1.addEdge(3, 0); 
    g1.addEdge(2, 4); 
    g1.addEdge(4, 2); 
    g1.isSC()? cout << "Yes\n" : cout << "No\n"; 
  
    Graph g2(4); 
    g2.addEdge(0, 1); 
    g2.addEdge(1, 2); 
    g2.addEdge(2, 3); 
    g2.isSC()? cout << "Yes\n" : cout << "No\n"; 
  
    return 0; 

}
