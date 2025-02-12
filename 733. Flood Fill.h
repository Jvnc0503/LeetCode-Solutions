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
    int rows, cols;

    int index(int i, int j) {
        return i * cols + j;
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        const int original = image[sr][sc];
        if (original == color) {
            return image;
        }
        rows = image.size();
        cols = image[0].size();

        DisjointSet ds(rows * cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (image[i][j] == original) {
                    if (j + 1 < cols && image[i][j + 1] == original) {
                        ds.unionSets(index(i, j), index(i, j +1));
                    }
                    if (i + 1 < rows && image[i + 1][j] == original) {
                        ds.unionSets(index(i, j), index(i + 1, j));
                    }
                }
            }
        }

        int rep = ds.findSet(index(sr, sc));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (image[i][j] == original && ds.findSet(index(i, j)) == rep) {
                    image[i][j] = color;
                }
            }
        }

        return image;
    }
};