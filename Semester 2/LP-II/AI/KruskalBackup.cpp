#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

struct Subset {
    int parent;
    int rank;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSets(vector<Subset>& subsets, int x, int y) {
    int xRoot = find(subsets, x);
    int yRoot = find(subsets, y);
    
    if (subsets[xRoot].rank < subsets[yRoot].rank) {
        subsets[xRoot].parent = yRoot;
    } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
        subsets[yRoot].parent = xRoot;
    } else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

vector<Edge> kruskalMST(vector<Edge>& edges, int n) {
    vector<Edge> MST;
    sort(edges.begin(), edges.end(), compareEdges);
    
    vector<Subset> subsets(n);
    for (int i = 0; i < n; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    
    int edgeCount = 0;
    int i = 0;
    while (edgeCount < n - 1 && i < edges.size()) {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.from);
        int y = find(subsets, nextEdge.to);
        
        if (x != y) {
            MST.push_back(nextEdge);
            unionSets(subsets, x, y);
            edgeCount++;
        }
    }
    
    return MST;
}

int main() {
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {1, 0, 4}, {2, 0, 4}, {2, 1, 2},
        {2, 3, 3}, {2, 5, 2}, {2, 4, 4}, {3, 2, 3}, {4, 2, 4}, {5, 2, 2}
    };
    
    vector<Edge> MST = kruskalMST(edges, n);
    
    cout << "Edges of the minimum spanning tree:" << endl;
    for (auto edge : MST) {
        cout << edge.from << " - " << edge.to << " : " << edge.weight << endl;
    }
    
    return 0;
}