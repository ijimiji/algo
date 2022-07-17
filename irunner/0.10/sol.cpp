#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <limits>

#define fast_io cout.tie(0), cin.tie(0), ios_base::sync_with_stdio(0)

using namespace std;

const long long INF = std::numeric_limits<long long>::max();

vector<long long> find_minimal_path_to_vertex(vector<vector<pair<int, int>>> graph, int start_vertex) {
    size_t n = graph.size();
    vector<long long> dist(n, INF);
    set<pair<long long, int>> queue;
    vector<bool> visited(n, false);

    dist[start_vertex] = start_vertex;
    queue.insert({0, start_vertex});

    while (!queue.empty()) {
        auto first = queue.begin();
        int vert = first->second;
        queue.erase(first);

        for (pair<int, int> next_vert : graph[vert]) {
            int length = next_vert.second;
            int v = next_vert.first;
            if (dist[vert] + length < dist[v]) {
                if (queue.find({dist[v], v}) != queue.end())
                    queue.erase(queue.find({dist[v], v}));
                dist[v] = dist[vert] + length;
                queue.insert({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    fast_io;

    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, m, start = 0;
    input >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v, p;
        input >> u >> v >> p;
        graph[u - 1].push_back({v - 1, p});
        graph[v - 1].push_back({u - 1, p});
    }

    output << find_minimal_path_to_vertex(graph, start)[n - 1];

    return 0;
}