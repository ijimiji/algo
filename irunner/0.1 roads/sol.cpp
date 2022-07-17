#include <cinttypes>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

#define N 510000
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
    int64_t n, q, a, b;
    input >> n >> q;
    
    for (int32_t i = 1; i <= n; i++){
        make_set(i);
    }

    while (input >> a >> b) {
        union_sets(a, b);
        output << c << "\n";
    }

    return 0;
}