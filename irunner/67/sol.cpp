#include <iostream>

using namespace std;

struct Node {
    int64_t max;
    int64_t min;
    int64_t maxProduct;
};

Node tree[500000];
int a[100001];

Node combine(Node &data1, Node &data2) {
    Node data;
    data.max = max(data1.max, data2.max);
    data.min = min(data1.min, data2.min);
    data.maxProduct = max(max(data1.maxProduct, data2.maxProduct),
                          max(data1.max * data2.max, data1.min * data2.min));
    return data;
}

void build(int32_t v, int32_t tl, int32_t tr) {
    if (tl == tr) {
        tree[v].max = a[tl];
        tree[v].min = a[tl];
        tree[v].maxProduct = INT64_MIN;
        return;
    }
    auto m = (tl + tr) / 2;
    build(2 * v + 2, m + 1, tr);
    build(2 * v + 1, tl, m);
    tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
}

void update(int v, int tl, int tr, int index, int value) {
    if (tl == tr) {
        tree[v].min = value;
        tree[v].max = value;
        return;
    }
    int m = (tl + tr) / 2;
    if (index <= m) {
        update(2 * v + 1, tl, m, index, value);
    } else {
        update(2 * v + 2, m + 1, tr, index, value);
    }
    tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
}

Node get(int v, int tl, int tr, int l, int r) {
    Node data;
    if (l <= tl && tr <= r) {
        return tree[v];
    }

    auto m = (tl + tr) / 2;

    if (l > m) {
        data = get(2 * v + 2, m + 1, tr, l, r);
    } else if (r <= m) {
        data = get(2 * v + 1, tl, m, l, r);
    } else {
        Node left = get(2 * v + 1, tl, m, l, r);
        Node right = get(2 * v + 2, m + 1, tr, l, r);
        data = combine(left, right);
    }
    return data;
}

int main() {
    int32_t n, q;
    cin >> n >> q;

    for (int32_t i = 0; i < n; ++i) {
        cin >> a[i];
    }

    build(0, 0, n - 1);
    for (int32_t i = 0; i < q; ++i) {
        string type;
        int32_t l, r;
        while (cin >> type) {
            cin >> l >> r;
            if (type == "?") {
                cout << get(0, 0, n - 1, l - 1, r - 1).maxProduct << "\n";
            } else {
                update(0, 0, n - 1, l - 1, r);
            }
        }
    }
}