#include <cinttypes>
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;
int32_t main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    int32_t n, m;
    int64_t temp;
    input >> n >> m;
    if (n < m) {
        output << "-1"
               << "\n";
        return 0;
    }
    vector<vector<int64_t>> a(n);
    vector<vector<int64_t>> dp(n);

    for (int32_t i = 0; i < n; ++i) {
        dp[i].resize(m);
        for (int32_t j = 0; j < m; ++j) {
            input >> temp;
            a[i].push_back(temp);
            dp[i][j] = INT32_MAX;
        }
    }
    for (int32_t i = 0; i < n; ++i) {
        dp[i][0] = a[i][0];
    }

    for (int32_t i = 1; i < n; ++i) {
        for (int32_t j = 0; j < m; ++j) {

            dp[i][j] = dp[i - 1][j] + a[i][j];

            if (dp[i-1][j-1] + a[i][j] < dp[i][j] and j > 0 ){
                dp[i][j] = dp[i - 1][j-1] + a[i][j];
            }

            if (dp[i-1][j+1] + a[i][j] < dp[i][j] and j < m-1 ){
                dp[i][j] = dp[i - 1][j+1] + a[i][j];
            }
        }
    }

    // for (int32_t i = 0; i < n; ++i) {
    //     for (int32_t j = 0; j < m; ++j) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    output << dp[n - 1][m - 1] << "\n";
    return 0;
}