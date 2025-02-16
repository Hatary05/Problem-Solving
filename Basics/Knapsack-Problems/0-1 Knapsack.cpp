//boj12865 - 평범한 배낭
//무게와 가치가 주어지고 각각 한번씩만 사용가능
//*point 역순 갱신
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
    vector<int> w(n), val(n);
    rep(i, n) cin >> w[i] >> val[i];

    vector<int> dp(k + 1);
    rep(i, n) for(int j = k; j >= w[i]; j--){
        dp[j] = max(dp[j], dp[j - w[i]] + val[i]);
    }
    cout << dp[k];
    return 0;
}
