#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int **adjMatrix;
    int vertexCount;
    int edgeCount;
    map<string,int> cities;
    map<int,string> inv_cities;

    public:
    Graph()
    {
        cout<<"Enter number of vertices"<<endl;
        cin>>vertexCount;
        cout<<"Enter number of edges"<<endl;
        cin>>edgeCount;

        adjMatrix=new int*[vertexCount];
        for(int i=0;i<vertexCount;i++)
        {
            adjMatrix[i]=new int[vertexCount];
            for(int j=0;j<vertexCount;j++)
            adjMatrix[i][j]=0;
        }

        cout<<"Add cities in order:"<<endl;
        for(int i=0;i<vertexCount;i++)
        {
            string city;
            cin>>city;
            cities.insert({city,i});
            inv_cities.insert({i,city});
        }

        cout<<"Add the "<<edgeCount<<" edges"<<endl;
        for(int i=0;i<edgeCount;i++)
        {
            string u,v;
            int d;
            cout<<"City 1: ";
            cin>>u;
            cout<<"City 2: ";
            cin>>v;
            cout<<"Distance: ";
            cin>>d;
            add(u,v,d);
        }
    }

    void add(string city1, string city2, int dist)
    {
        adjMatrix[cities[city1]][cities[city2]]=dist;
        adjMatrix[cities[city2]][cities[city1]]=dist;
    }

    int minimum_key(int key[], bool mst[])
    {
        int minimum=INT_MAX,min;
        for(int i=0;i<vertexCount;i++)
        {
            if(mst[i]==0 && key[i]<minimum)
            {
                minimum=key[i];
                min=i;
            }
        }
        return min;
    }

    void prim(Graph g)
    {
        int n=g.vertexCount;
        int parent[n];
        int key[n];
        bool mst[n];
        for(int i=0;i<n;i++)
        {
            key[i]=INT_MAX;
            mst[i]=0;
        }
        key[0]=0;
        parent[0]=-1;
        for(int count=0;count<n-1;count++)
        {
            int min_edge_vertex=minimum_key(key,mst);
            mst[min_edge_vertex]=1;
            for(int vertex=0;vertex<n;vertex++)
            {
                if(g.adjMatrix[min_edge_vertex][vertex] && mst[vertex]==0 && g.adjMatrix[min_edge_vertex][vertex]<key[vertex])
                {
                    parent[vertex]=min_edge_vertex;
                    key[vertex]=g.adjMatrix[min_edge_vertex][vertex];
                }
            }
        }
        cout<<"MST of given graph is: "<<endl;
        cout<<"Edge \t Weight"<<endl;
        for(int i=1;i<n;i++)
        {
            cout<<inv_cities[parent[i]]<<"<->"<<inv_cities[i]<<"\t"<<g.adjMatrix[i][parent[i]]<<endl;
        }
        int cost=0;
        for(int i=1;i<n;i++)
        {
            cost+=g.adjMatrix[i][parent[i]];
        }
        cout<<"Cost: "<<cost<<endl;
    }
};

int main()
{
    Graph g;
    g.prim(g);
    return 0;
}