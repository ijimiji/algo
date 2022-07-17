#include <cinttypes>
#include <cstdio>
#include <vector>
#define fn auto
#define let const auto
#define var auto

using namespace std;

fn main()-> int32_t {
    let m = 1000000007;
    let input = fopen("input.txt", "r") ;
    let output = fopen("output.txt", "w") ;
    int64_t t, k, n, ans;
    vector<int64_t> dp(300000, 0);
    fscanf(input, "%lld", &t);

    for (var z = 0; z < t; ++z){
        fscanf(input, "%lld", &n);
        fscanf(input, "%lld", &k);
        dp[0] = 1;
        dp[1] = dp[0];
        for(var i = 2; i<=k; ++i){
            dp[i] = ((2*(dp[i-1]%m))%m); 
        }
        for(var i = k+1; i<n; ++i){
            dp[i] = ((((2*(dp[i-1]%m))%m) - dp[i-k-1]%m)+m)%m; 
        }
        fprintf(output, "%lld\n", dp[n-1]%m);
    }
}