#include <cinttypes>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_set>

using namespace std;

#define N 760000
vector<pair<int64_t, int64_t>> p(N);
vector<int64_t> r(N);
int64_t c = 0;

void make_set(int v) {
    c++;
    p[v] = make_pair(v, 0);
    r[v] = 0;
}

pair<int, int> find_set(int v) {
    if (v != p[v].first) {
        int len = p[v].second;
        p[v] = find_set(p[v].first);
        p[v].second += len;
    }
    return p[v];
}

void union_sets(int a, int b) {
    a = find_set(a).first;
    b = find_set(b).first;
    if (a != b) {
        --c;
        if (r[a] < r[b])
            swap(a, b);
        p[b] = make_pair(a, 1);
        if (r[a] == r[b])
            ++r[a];
    }
}

int32_t main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    int64_t n, q, a, b, e, k;
    unordered_set <int64_t> set;
    stack <int64_t> s;
    stack <int64_t> out;
    vector<pair<int64_t, int64_t>> edges;
    input >> n >> e >> q;
    
    for (int32_t i = 1; i <= n; i++){
        make_set(i);
    }
    
    for (int32_t i = 1; i <= e; i++){
        input >> a >> b;
        edges.push_back({a, b});
    }

    for (int32_t i = 1; i <= q; i++){
        input >> k;
        set.insert(k);
        s.push(k);
    }

    for (int32_t i = 0; i < e; i++){
        if (set.find(i+1) == set.end()){
            union_sets(edges[i].first, edges[i].second);
        }
    }
    
    while(not s.empty()){
        auto index = s.top() - 1;
        out.push(c);
        union_sets(edges[index].first, edges[index].second);
        s.pop();
    }

    while(not out.empty()){
        auto temp =  out.top();
        output << ((temp == 1) ? 1 : 0);
        out.pop();
    }


    return 0;
}