#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define rep(i, n) for(int i = 0; i < (n); i++)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define compress(x) (x).erase(unique(all(x)), x.end())
#define fr first
#define sc second

int n, m; string a, b;
void _2D_dp(){
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) 
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
}
void _1D_dp(){ //optimization form
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) 
                curr[j] = prev[j - 1] + 1;
            else 
                curr[j] = max(prev[j], curr[j - 1]);
        }
        swap(prev, curr);
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    return 0;
}
