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

    int n = 1e6;
    const ll MOD = 1e9 + 7;
    auto exp = [&](ll x, ll e) -> ll {
        ll ret = 1;
        while(e){
            if(e & 1) ret = ret * x % MOD;
            x = x * x % MOD; e >>= 1;
        }
        return ret;
    };
    vector<ll> factorial(n + 2), rev(n + 2);
    factorial[0] = 1;
    for(int i = 1; i <= n + 1; i++) factorial[i] = factorial[i - 1] * i % MOD;
    rev[n + 1] = exp(factorial[n + 1], MOD - 2);
    for(int i = n + 1; i >= 1; i--) rev[i - 1] = rev[i] * i % MOD;
    auto comb = [&](int n, int r) -> ll {
        if(r < 0 || n < r) return 0LL;
        ll perm = factorial[n] * rev[n - r] % MOD;
        return perm * rev[r] % MOD;
    };

    cout << comb(5, 3) << endl;
    cout << comb(100, 2) << endl;
    return 0;
}
