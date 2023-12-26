#include <bits/stdc++.h>
using namespace std;
class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;

    void addEdge(int, int);

    void DFS(int);
    void BFS(int);
};
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
void Graph::BFS(int v){

}
void Graph::DFS(int v)
{
    visited[v] = true;
    cout << v <<' ';
    for (int i : adj[v])
        if (!visited[i])
            DFS(i);
    return;
}
int main()
{
    char f = 10;
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Following is Depth First Traversal,"
            " (starting from vertex 2) \n";

    g.DFS(2);
    return 0;
}