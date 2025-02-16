//boj2293 - 동전 1
//0-1knapsack은 생산 가능한 최대가치에 집중(한 번씩만 사용가능)
//unbounded knapsack은 특정 가치를 만드는 조합에 집중(여러번 사용가능)
//*point 정순 갱신
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

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> w(n);
    rep(i, n) cin >> w[i];

    vector<int> dp(k + 1);
    dp[0] = 1;
    rep(i, n) for(int j = w[i]; j <= k; j++){
        dp[j] += dp[j - w[i]];
    }
    cout << dp[k];
    return 0;
}
