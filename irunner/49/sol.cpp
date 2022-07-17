#include <cstdio>
#include <queue>
#include <vector>
#include <set>
#include <cinttypes>
#define var auto
#define let const auto
#define fn auto
using namespace std;

typedef vector<vector<int32_t>> Graph;

vector<int> p;
vector<int> s;

int32_t dsuGet(int32_t v) { return (v == p[v]) ? v : (p[v] = dsuGet(p[v])); }

fn makeSet (int v) {
	p[v] = v;
	s[v] = 1;
}
 
fn dsuUnite (int32_t a, int32_t b) {
	a = dsuGet (a);
	b = dsuGet (b);
	if (a != b) {
		if (s[a] < s[b])
			swap (a, b);
		p[b] = a;
		s[a] += s[b];
	}
}



struct Edge {
    int32_t a;
    int32_t b;
    int32_t i;
};
typedef vector<Edge> Edges;

fn span(Edges &edges, set<int32_t> &out){
    for (let &edge : edges){
        if (dsuGet(edge.a) != dsuGet(edge.b)) {
            dsuUnite(edge.a, edge.b);
        } else {
            out.insert(edge.i);
        }
    }
}

fn main()->int32_t {
    let input = fopen("input.txt", "r");
    let output = fopen("output.txt", "w");
    bool ok = true;
    set<int32_t> del;
    int32_t n, m, w, v, t;
    fscanf(input, "%d", &n);
    fscanf(input, "%d", &m);
    p.resize(n);
    s.resize(n);
    for (int32_t i = 0; i < n; ++i) {
        makeSet(i);
    }
    Edges royal, neutral, scum;

    for (var i = 0; i < m; ++i) {
        fscanf(input, "%d", &v);
        fscanf(input, "%d", &w);
        fscanf(input, "%d", &t);
        Edge edge = {v-1, w-1, i+ 1};
        if (t == 1) {
            royal.push_back(edge);
        }
        if (t == 2) {
            scum.push_back(edge);
        }
        if (t == 3) {
            neutral.push_back(edge);
        }
    }
    span(neutral, del);
    vector<int32_t> dupP(p);
    vector<int32_t> dupS(s);
    span(scum,  del);
    for (var i = 0; i < n-1; ++i){
        if (dsuGet(i) != dsuGet(i+1)){
            ok = false;
        }
    }

    for (int32_t i = 0; i < n; ++i){
        p[i] = dupP[i];
        s[i] = dupS[i];
    }
    span(royal, del);
    for (var i = 0; i < n-1; ++i){
        if (dsuGet(i) != dsuGet(i+1)){
            ok = false;
        }
    }

    let k = del.size();
    if (ok) {
        fprintf(output, "%lu\n", del.size());
        for (let &i : del) {
            fprintf(output, "%d ", i);
        }
    } else {
        fprintf(output, "-1\n");
    }
}