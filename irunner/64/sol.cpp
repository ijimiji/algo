#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void update(vector<int64_t> &t, int64_t v, int64_t tl, int64_t tr, int64_t pos, int64_t new_val) {
    if (tl == tr)
        t[v] = new_val;
    else {
        int64_t tm = (tl + tr) / 2;
        if (pos <= tm)
            update(t, v * 2, tl, tm, pos, new_val);
        else
            update(t, v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int sum(vector<int64_t> &t, int64_t v, int64_t tl, int64_t tr, int64_t l, int64_t r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int64_t tm = (tl + tr) / 2;
    return sum(t, v * 2, tl, tm, l, min(r, tm)) +
           sum(t, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

int32_t main() {
    const int64_t M = 1000000007;
    unordered_map<int64_t, int64_t> m;
    int64_t n;
    cin >> n;
    vector<int64_t> a(n);
    vector<int64_t> inversions(n);
    vector<int64_t> zeroes(4*n, 0);
    vector<int64_t> fact(n);

    for (int64_t i = 0; i < n; ++i) {
        cin >> a[i];
        m[a[i]] = i;
    }

    for (int64_t i = 1; i <= n; ++i) {
        update(zeroes, 1, 0, n-1, m[i], 1);
        inversions[m[i]] = sum(zeroes, 1, 0, n-1, m[i], n-1)-1;
    }

    fact[0] = 1;
    for (int64_t i = 1; i < n; ++i) {
        // fact[i] = fact[i - 1] * i;
        fact[i] = ((fact[i - 1]%M) * (i%M))%M;

    }

    int64_t res = 0;
    for (int64_t i = 0; i < n; ++i){
        // res += inversions[i] * fact[n-i-1];
        res = (res%M + ((inversions[i]%M) * (fact[n -i-1]%M))%M)%M;
    }
    cout << res+1 << "\n";

    // cout << "\n";
    // for (auto x : inversions){
    //     cout << x << " ";
    // }
    // cout << "\n";
    return 0;
}