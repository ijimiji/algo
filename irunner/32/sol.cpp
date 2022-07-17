#define var auto
#define let const auto
#define fn auto
#include <cinttypes>
#include <fstream>
#include <stack>
#include <vector>
#define maxN 100001

#include <cstdio>
#include <iostream>
#include <unordered_map>

using namespace std;

int32_t compN = 0;
int32_t n;
vector<vector<int32_t>> g(maxN);
vector<bool> used(maxN, false);
// vector<int32_t> comp(maxN);
unordered_map<int32_t, int32_t> comp;
stack<int32_t> ne;

void dfs(int v) {
    used[v] = true;
    // comp.push_back(v);
    comp[compN] = v;
    for (size_t k = 0; k < g[v].size(); ++k) {
        int to = g[v][k];
        if (!used[to])
            dfs(to);
    }
}

void DFS(int32_t v) { 
    stack<int32_t> s;
    s.push(v);
    while (!s.empty()){
        v = s.top();
        comp[v] = compN;
        s.pop();
        if (used[v]) 
            continue;
        used[v] = true;
        for(let u : g[v]){
            s.push(u);
        }
    }
}

void findComps() {
    for (int k = 0; k < n; ++k)
        if (!used[k]) {
            ++compN;
            DFS(k);
        }
}

fn main()->int32_t {
    ifstream input("equal-not-equal.in");
    ofstream output("equal-not-equal.out");
    int32_t m;
    input >> n >> m;

    string tempString, op;
    int32_t i, j;
    for (int32_t k = 0; k < m; ++k) {
        input >> tempString;
        sscanf(tempString.c_str(), "x%d", &i);
        // printf("%d\n", i);

        input >> op;
        input >> tempString;
        sscanf(tempString.c_str(), "x%d", &j);
        // printf("%d\n", j);

        if (op == "==") {
            g[i - 1].push_back(j - 1);
            g[j - 1].push_back(i - 1);
        } else {
            ne.push(i - 1);
            ne.push(j - 1);
        }
    }
    findComps();

    int32_t a, b;
    while (!ne.empty()) {
        a = ne.top();
        ne.pop();
        b = ne.top();
        ne.pop();
        if (comp[a] == comp[b]) {
            output << "No\n";
            return 0;
        }
    }

    output << "Yes\n";
    return 0;
}