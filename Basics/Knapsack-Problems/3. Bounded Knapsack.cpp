//boj12920 - 평범한 배낭 2
//0-1과 unbounded의 절충 cnt(사용 가능한 개수)가 주어짐
//O(nmk) : (n = 종류, m = 가방 최대무게, k = 종류별 개수)
//k부분을 최적화 시키는 것이 중요 --> O(nm logk)
// 13 = 1 + 2 + 4 + 6 이런식으로 쪼갬
// 2^i (0 <= i < k)는 all x, (x < 2^k)를 만들 수 있으므로
// remainder부분은 2^k이하가 보장되므로 ㄱㅊ음
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

    int n, m; cin >> n >> m;
    vector<int> c, val;
    rep(i, n){
        int w, v, cnt; cin >> w >> v >> cnt;
        for(int i = 1; cnt > 0; i <<= 1){
            int k = min(cnt, i);
            c.push_back(w * k);
            val.push_back(v * k);
            cnt -= k;
        }
    }

    n = sz(c);
    vector<int> dp(m + 1);
    rep(i, n) for(int j = m; j >= c[i]; j--){
        dp[j] = max(dp[j], dp[j - c[i]] + val[i]);
    }
    cout << dp[m];
    return 0;
}
