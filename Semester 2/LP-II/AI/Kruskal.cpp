#include<bits/stdc++.h>
#define ll long long
using namespace std;


class DSU{
public:
    int* arr;
    int* rank;
    int n;
    DSU(int n){
        this->n = n;
        arr = new int[n+1];
        rank = new int[n+1];

        for (int i = 0; i<=n; i++){
            arr[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x){
        if(arr[x] == x) return x;
        else return arr[x] = find(arr[x]);
    }

    void uNion(int x, int y){
        int xRoot = find(y);
        int yRoot = find(x);
        if(xRoot == yRoot) return;
        
        if(rank[xRoot]> rank[yRoot]){
            arr[yRoot] = xRoot;
        }
        else if (rank[xRoot]<rank[yRoot]){
            arr[xRoot] = yRoot;
        }
        else{
            arr[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
};

class edge{
public:
    int src;
    int dest;
    int wt;

    edge(){
        this->src = 0;
        this->dest = 0;
        this->wt = 0;
    }

    edge(int a, int b, int w){
        this->src = a;
        this->dest = b;
        this->wt = w;
    }
};

bool sortedge (edge& e1, edge& e2){
    return e1.wt < e2.wt;
}

class graph{
public:
    int n;
    int m;
    edge* edges;
    graph(int n, int m){
        this->n = n;
        this->m = m;
        edges = new edge[m];
        for (int i = 0; i<m; i++){
            cout<<"enter src, dest and wt"<<endl;
            cin>>edges[i].src>>edges[i].dest>>edges[i].wt;
        }
    }

    void kruskal (){
        int edgecount = 0;
        sort(edges, edges+m,sortedge);
        DSU d1(n+1);
        int par[n+1] = {0};
        int ans = 0;
        for (int i = 0; edgecount<n-1 ; i++){
            int par1 = d1.find(edges[i].src);
            int par2 = d1.find(edges[i].dest);
            if(par1 != par2){
                par[edges[i].dest] = edges[i].src;
                d1.uNion(edges[i].src,edges[i].dest);
                ans += edges[i].wt;
                edgecount++;
            }
        }
        cout<<"the cost is "<<ans<<endl;
        for (int i = 1; i<=n; i++){
            cout<<i<<" "<<par[i]<<endl;
        }
    }

};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    graph g1(5,7);
    g1.kruskal();
}