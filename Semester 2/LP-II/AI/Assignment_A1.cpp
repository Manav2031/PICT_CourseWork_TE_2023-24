#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int n,e;
    unordered_map<string,vector<string>> adj;
    queue <pair<string,int>> q;
    public:
    Graph(int n1,int e1)
    {
        n=n1;
        e=e1;
        take_input();
    }
    void take_input()
    {
        cout<<"Enter starting and ending cities of the routes"<<endl;
        string a,b;
        for(int i=0;i<e;i++)
        {
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    void dfs(pair<string,int> p, unordered_map<string,int> &v)
    {
        string node=p.first;
        int level=p.second;
        v[node]=true;
        cout<<node<<" "<<level<<endl;
        for(auto it:adj[node])
        {
            if(!v[it])
            dfs({it,level+1},v);
        }
    }
    void DFS()
    {
        unordered_map<string,int> v;
        cout<<"Enter starting city for DFS"<<endl;
        string s;
        cin>>s;
        cout<<"DFS:"<<endl;
        dfs({s,0},v);
    }
    void bfs(unordered_map<string,int>& v)
    {
        if(q.empty())
        return;

        string node=q.front().first;
        int level=q.front().second;
        q.pop();
        cout<<node<<" "<<level<<endl;
        for(auto it:adj[node])
        {
            if(!v[it])
            {
                v[it]=true;
                q.push({it,level+1});
            }
        }
        bfs(v);
    }
    void BFS()
    {
        unordered_map<string,int> v;
        cout<<"Enter starting city for BFS"<<endl;
        string s;
        cin>>s;
        q.push({s,0});
        v[s]=1;
        cout<<"BFS"<<endl;
        bfs(v);
    }

    int main()
    {
        int n;
        cout << "Enter number of cities" << endl;
        cin >> n;
        int e;
        cout << "Enter number of routes" << endl;
        cin >> e;
        Graph g(n, e);
        g.BFS();
        g.DFS();
    }
}