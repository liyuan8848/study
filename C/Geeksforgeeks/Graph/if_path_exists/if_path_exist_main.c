/*
  Given a Directed Graph and two vertices in it, check whether there is a path from the first given vertex to second. 
  We can use BFS or DFS to find path between two vertices. Take the first vertex as sources in BFS (of DFS), follow the standard BFS (of DFS). If we see the second vertex in our traversal, then return true. Else, return false.




*/

#include <iostream>
#include <list>

using namespace std;

class Graph
{
    int V; 
    list<int> *adj;

    public:
    Graph (int V);

    void addEdge(int v, int w);
    bool isReachable(int s, int d);

};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

// A BFS based function to check whether d is reachable from s

bool Graph::isReachable(int s, int d)
{
    // base case
    if (s == d)
     return true;

    // mark all the vertices unvisited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // create a queue for BFS
    list<int> queue;

    queue.push_back(s);
    visited[s] = true;
    list<int>::iterator ir;
    
    while(!queue.empty())
    {
       s = queue.front();
       queue.pop_front();

       // Get all adjacent vertices of the dequeued vertex s 
       // if a adjacent has not been visited, then mark it as visited and enqueue it

       for (ir = adj[s].begin(); ir != adj[s].end(); ir++)
       {

           // if this adjacent node is the destination node, then return true
           if (*ir == d)
            return true;
          
          // else , continue to BFS
          if (!visited[*ir])
            {
                visited[*ir] = true;
                queue.push_back(*ir);
            }


       }
    }

    // if BFS is complete without visiting d
    return false;
    


}  

int main(int argc, char const *argv[])
{
    /* code */

    Graph g(4);

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,3);

    int u = 1, v = 3;
    if(g.isReachable(u,v))
        cout<<"\n There is a path from " << u << " to " << v << endl;
    else
        cout<< "\n There is no path from " << u << " to " << v << endl;

    u = 3;
    v = 1;
    if(g.isReachable(u,v))
        cout<<"\n There is a path from " << u << " to " << v << endl; 
    else
        cout<< "\n There is no path from " << u << " to " << v << endl;    
    return 0;
}
