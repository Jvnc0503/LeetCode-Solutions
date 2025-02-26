#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class DisjointSet {
    int *parent, *rank;

public:
    explicit DisjointSet(const int &n): parent(new int[n]), rank(new int[n]) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }

    int findSet(const int &x) {
        if (parent[x] != x) {
            parent[x] = findSet(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(const int &x, const int &y) {
        const int xRoot = findSet(x);
        const int yRoot = findSet(y);

        if (xRoot == yRoot) {
            return false;
        }

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }

        return true;
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) {
            return -1;
        }
        DisjointSet ds(n);
        for (const auto& c: connections) {
            ds.unionSets(c[0], c[1]);
        }
        unordered_set<int> arboles;
        for (int i = 0; i < n; ++i) {
            if (!arboles.contains(ds.findSet(i))) {
                arboles.insert(ds.findSet(i));
            }
        }
        return arboles.size() - 1;
    }
};