#include <bits/stdc++.h>

using namespace std;


map <string,bool> vis;
map <string, vector<string>> adj;
queue<string> q;


void setVisitedtoZero()
{
    for(auto pair:adj)
    {
        vis[pair.first] = false;
    }
}



void DFS(string node)
{
    vis[node] = true;
    cout<<node<<" ";


    for (auto it:adj[node])
    {
        if(!vis[it])
        DFS(it);
    }
}



void BFS()
{
    if(q.empty())
        return;

    string node = q.front();

    q.pop();

    cout<<node<<" ";

    for(auto it:adj[node])
    {
        if(!vis[it])
        {
            vis[it] = true;
            q.push(it);
        }
    }

    BFS();
}




int main()
{

    int n,m;
    cout<<"Enter the number of routes and cities of the graph:\n";
    cin>>n>>m;

    string x,y;
    cout<<"Enter starting and ending cities of the routes:\n";
    
    for(int i=0; i<n; i++)
    {
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    while(true)
    {
        cout<<"1. DFS"<<endl;
        cout<<"2. BFS"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice:"<<endl;
        int choice;
        string node;
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter the city to start with:\n";
            cin>>node;
            cout<<"\nDFS:\n";
            setVisitedtoZero();
            DFS(node);
            cout<<endl;
        }
        else if(choice==2)
        {
            cout<<"Enter the city to start with:\n";
            cin>>node;
            q.push(node);
            cout<<"\nBFS:\n";
            setVisitedtoZero();
            vis[node] = true;
            BFS();
            cout<<endl;
        }
        else if(choice==3)
        {
            cout<<"Program exited successfully."<<endl;
            break;
        }
        else
        cout<<"Invalid choice. Please enter a valid number between 1 and 3."<<endl;
    }
    return 0;
}