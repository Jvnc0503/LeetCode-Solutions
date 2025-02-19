class Solution {
public:
    struct Edge {
        int neighbor;
        bool color;
        
        Edge(int n, bool c): neighbor(n), color(c) {}
    };
    
    struct State {
        int node;
        bool lastColor;
        int distance;
        
        State(int node, bool lastColor, int distance): node(node), lastColor(lastColor), distance(distance) {}
    };
    
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        //Adjacent list graph
        vector<vector<Edge>> graph(n);
        for (const auto& edge: redEdges) {
            graph[edge[0]].emplace_back(edge[1], 0);
        }
        for (const auto& edge: blueEdges) {
            graph[edge[0]].emplace_back(edge[1], 1);
        }
        
        //Result
        vector<int> result (n, -1);
        //Visited [node][color]
        vector<vector<bool>> visited(n, vector<bool>(2, false));
        
        queue<State> q;
        
        q.emplace(0, 0, 0);
        q.emplace(0, 1, 0);
        visited[0][0] = visited[0][1] = true;
        result[0] = 0;
        
        while (!q.empty()) {
            State curr = q.front();
            q.pop();
            
            for (const auto& edge: graph[curr.node]) {
                if (edge.color != curr.lastColor && !visited[edge.neighbor][edge.color]) {
                    visited[edge.neighbor][edge.color] = true;
                    int nextDistance = 1 + curr.distance;
                    q.emplace(edge.neighbor, edge.color, nextDistance);
                    if (result[edge.neighbor] == -1) {
                        result[edge.neighbor] = nextDistance;
                    }
                }
            }
        }
        return result;
    }
};