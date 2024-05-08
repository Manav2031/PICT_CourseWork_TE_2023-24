#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
  int n, e;
  vector<vector<pair<int, int>>> adj;

  Graph(int n, int e) : n(n), e(e)
  {
    adj.resize(n + 1);
    input();
  }

  void input()
  {
    cout << "Enter building number 1, building number 2, and distance for " << e << " paths" << endl;
    int a, b, d;
    for (int i = 0; i < e; i++)
    {
      cin >> a >> b >> d;
      adj[a].push_back({b, d});
      adj[b].push_back({a, d});
    }
  }

  void dijkstra(int s, int e)
  {
    vector<int> dis(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    dis[s] = 0;
    while (!pq.empty())
    {
      int d = pq.top().first;
      int v = pq.top().second;
      pq.pop();
      if (v == e)
        break;
      for (auto it : adj[v])
      {
        if (d + it.second < dis[it.first])
        {
          dis[it.first] = d + it.second;
          parent[it.first] = v; 
          pq.push({dis[it.first], it.first});
        }
      }
    }
    if (dis[e] == INT_MAX)
    {
      cout << "No path exists from Building " << s << " to Building " << e << endl;
      return;
    }
    cout << "Cost for travelling from Building " << s << " to Building " << e << ": " << dis[e] << endl;
    cout << "Path: ";
    printPath(s, e, parent);
    cout << endl;
  }

  void printPath(int s, int e, vector<int> &parent)
  {
    if (s == e)
    {
      cout << s;
      return;
    }
    printPath(s, parent[e], parent);
    cout << " -> " << e;
  }
};

int main()
{
  int n, e;
  cout << "Enter number of buildings in your society: ";
  cin >> n;
  cout << "Enter number of roads connecting buildings: ";
  cin >> e;
  Graph g(n, e);
  int source, destination;
  cout << "Enter source building: ";
  cin >> source;
  cout << "Enter destination building: ";
  cin >> destination;
  g.dijkstra(source, destination);
  return 0;
}