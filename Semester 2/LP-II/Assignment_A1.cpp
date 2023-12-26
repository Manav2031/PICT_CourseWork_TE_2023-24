#include <bits/stdc++.h>
using namespace std;
class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;

    void addEdge(int, int);

    void DFS(int);
    void BFS(int v, queue<int> &q);
};
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
void Graph::BFS(int v, queue<int> &q)
{
    if (q.empty())
        return;

    v = q.front();
    q.pop();

    if (!visited[v])
    {
        visited[v] = true;
        cout << v << ' ';

        for (int i : adj[v])
        {
            if (!visited[i])
            {
                q.push(i);
            }
        }
    }

    BFS(v, q);
}
void Graph::DFS(int v)
{
    visited[v] = true;
    cout << v << ' ';
    for (int i : adj[v])
        if (!visited[i])
            DFS(i);
    return;
}
int main()
{
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(1, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    while(true)
    {
        cout<<"1. DFS"<<endl;
        cout<<"2. BFS"<<endl;
        cout<<"3. Exit"<<endl;
        int choice;
        cin>>choice;
        if(choice==1)
        {
            cout<<"Following is Depth First Traversal: "<<endl;
            g.DFS(2);
            cout<<endl;
        }
        else if(choice==2)
        {
            cout<<"Following is Breadth First Traversal: "<<endl;
            queue<int> q;
            q.push(1);
            g.BFS(1, q);
            cout<<endl;
        }
        else if(choice==3)
        {
            cout<<"Program exited successfully."<<endl;
            break;
        }
        else
        cout<<"Invalid choice. Please enter a valid choice from 1 to 3."<<endl;
    }
    return 0;
}