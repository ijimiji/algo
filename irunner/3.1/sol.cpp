#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#define var auto
#define let const auto
#define fn auto
using namespace std;
typedef vector<vector<int32_t>> Graph;

fn bfs(Graph &rGraph, int32_t s, int32_t t, vector<int32_t> &parent) {
    int32_t n = rGraph.size();
    vector<bool> visited(n);
    queue<int32_t> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (var v = 0; v < n; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
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

fn fordFulkerson(Graph &graph, int32_t s, int32_t t) {
    int32_t u, v;
    let n = graph.size();
    Graph rGraph(n);
    for (u = 0; u < n; u++) {
        rGraph[u].resize(n);
        for (v = 0; v < n; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }
    vector<int> parent(n);
    var maxFlow = 0;
    while (bfs(rGraph, s, t, parent)) {
        var pathFlow = INT_MAX;
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
    let input = fopen("input.in", "r");
    let output = fopen("output.out", "w");
    int32_t n, m, w, v;
    fscanf(input, "%d", &n);
    fscanf(input, "%d", &m);
    Graph graph(n);

    for (var i = 0; i < n; ++i) {
        graph[i].resize(n);
    }

    for (var i = 0; i < n; ++i) {
        while (fscanf(input, "%d", &v)) {
            if (v == 0) {
                break;
            }
            graph[i][v - 1] = 1;
            graph[v - 1][i] = 1;
        }
    }
    fscanf(input, "%d", &v);
    fscanf(input, "%d", &w);
    fprintf(output, "%d", fordFulkerson(graph, v - 1, w - 1));
}