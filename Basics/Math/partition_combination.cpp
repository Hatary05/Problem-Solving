/*
자연수 n을 k개의 자연수로 분할하는 방법 P(n, k)
P(n, k) = P(n - 1, k - 1) + P(n - k, k) = comb(n - 1, k - 1)
n개의 star(*)의 내부 간격 n - 1개 중 k - 1개를 고르는 경우의 수
***|*|**|*|***

자연수 n을 k개의 음이 아닌 정수로 분할하는 방법 D(n, k)
D(n, k) = comb(n + k - 1, k - 1)
n개의 star(*)와 k - 1개의 bar(|)를 모두 합쳐서 순열
bar(|)를 기준으로 k개의 partitions으로 나누어지고
bar의 개수많큼 순열을 나누어서 중복을 제거해준다.
*/
//atcoder abc132 - D
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

    const ll MOD = 1e9 + 7;
    const int MAXN = 2020;
    vector<ll> fact(MAXN + 1), rev(MAXN + 1);
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;

    auto exp = [&](ll x, ll e) -> ll {
        ll ret = 1;
        while(e){
            if(e & 1) ret = ret * x % MOD;
            x = x * x % MOD; e >>= 1;
        }
        return ret;
    };
    rev[MAXN] = exp(fact[MAXN], MOD - 2);
    for(int i = MAXN; i > 0; i--) rev[i - 1] = rev[i] * i % MOD;

    auto comb = [&](ll n, ll r) -> ll {
        if(n < r || r < 0) return 0;
        ll perm = fact[n] * rev[n - r] % MOD;
        return perm * rev[r] % MOD;
    };

    int n, k; cin >> n >> k;
    for(int i = 1; i <= k; i++){
        ll ans = comb(k - 1, i - 1);
        int part = n - k - (i - 1);
        ans = ans * comb(part + i, i) % MOD;
        //D(part, i + 1) = comb(part + i, i);
        cout << ans << '\n';
    }
    return 0;
}
