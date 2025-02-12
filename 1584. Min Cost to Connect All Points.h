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
    struct Edge {
        int u;
        int v;
        int weight;

        Edge(const int& u, const int& v, const int& weight): u(u), v(v), weight(weight) {}

        bool operator <(const Edge& other) const {
            return weight < other.weight;
        }
    };

    int manhattan(const vector<int>& x, const vector<int>& y) {
        return std::abs(x[0] - y[0]) + std::abs(x[1] - y[1]);
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        const int n = points.size();
        vector<Edge> edges;
        DisjointSet ds(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int weight = manhattan(points[i], points[j]);
                edges.emplace_back(i, j, weight);
            }
        }

        std::sort(edges.begin(), edges.end());
        int cost = 0;
        int unions = 0;

        for (const auto& edge: edges) {
            if (ds.unionSets(edge.u, edge.v)) {
                cost += edge.weight;
                ++unions;
                if (unions == (n - 1)) {
                    return cost;
                }
            }
        }
        return cost;
    }
};