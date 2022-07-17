#define fn auto
#define var auto
#define let const auto
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<vector<int32_t>> Graph;

fn bfs(Graph &graph, int32_t s, int32_t t, vector<int32_t> &parent)->bool {
    let n = graph.size();
    vector<int32_t> visited(n);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        let u = q.front();
        q.pop();

        for (var v = 0; v < n; ++v) {
            if (not visited[v] && graph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

fn maxFlow(Graph &graph, int32_t s, int32_t t) {
    int32_t u, v;
    var rGraph(graph);

    vector<int32_t> parent(graph.size());
    var maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        var pathFlow = INT32_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

fn main()->int32_t {
    int32_t n, m, v, w, capacity;
    cin >> n >> m;
    Graph graph(n, vector<int32_t>(n));

    while (cin >> v >> w >> capacity) {
        graph[v - 1][w - 1] += capacity;
    }
    cout << maxFlow(graph, 0, n - 1);
}