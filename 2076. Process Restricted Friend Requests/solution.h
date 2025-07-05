#include <numeric>

class Solution {
    vector<int> parent, rank;
    pair<vector<int>, vector<int>> prev;

    int findSet(const int& x) {
        return parent[x] == x ? x : (parent[x] = findSet(parent[x]));
    }

    void unionSet(const int& x, const int& y) {
        const int xRoot = findSet(x);
        const int yRoot = findSet(y);
        if (xRoot != yRoot) {
            if (rank[xRoot] < rank[yRoot]) {
                parent[yRoot] = xRoot;
            } else {
                parent[xRoot] = yRoot;
                if (rank[xRoot] == rank[yRoot]) {
                    rank[yRoot]++;
                }
            }
        }
    }

public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        // Initialization
        parent = vector<int>(n);
        rank = vector<int>(n, 0);
        std::iota(parent.begin(), parent.end(), 0);

        vector<bool> result(requests.size(), true);

        // Iterate all friend requests
        for (int i = 0; i < requests.size(); i++) {
            // Save previous state of graph
            prev.first = parent;
            prev.second = rank;
            // Do union-set between vertices
            const auto& request = requests[i];
            unionSet(request[0], request[1]);
            // Check all restrictions are met
            for (const auto& restriction: restrictions) {
                // If any restriction is infringed, rollback to previous state
                // and set request as not successful
                if (findSet(restriction[0]) == findSet(restriction[1])) {
                    result[i] = false;
                    parent = prev.first;
                    rank = prev.second;
                    break;
                }
            }
        }

        return result;
    }
};