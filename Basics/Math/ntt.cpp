#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define rep(i, n) for(int i = 0; i < (n); i++)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define compress(x) (x).erase(unique(all(x)), x.end())
#define fr first
#define sc second

ll exp_mod(ll x, ll e, ll MOD) {
    ll ret = 1;
    while(e) {
        if(e & 1) ret = ret * x % MOD;
        x = x * x % MOD; e >>= 1;
    }
    return ret;
}
void ntt(vector<ll> &a, bool inv, ll MOD, ll root) {
    int n = sz(a);
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        ll wlen = exp_mod(root, (MOD - 1) / len, MOD);
        if(inv) wlen = exp_mod(wlen, MOD - 2, MOD);

        for(int i = 0; i < n; i += len) {
            ll w = 1;
            for(int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if(inv) {
        ll inv_n = exp_mod(n, MOD - 2, MOD);
        for(auto &x : a) x = x * inv_n % MOD;
    }
}
vector<ll> convolution(vector<ll> &a, vector<ll> &b, ll MOD, ll root) {
    vector<ll> fa(a), fb(b);
    int m = sz(a) + sz(b) - 1;
    int n = 1 << (int)ceil(log2(m) - 1e-9);
    fa.resize(n), fb.resize(n);

    ntt(fa, false, MOD, root), ntt(fb, false, MOD, root);
    rep(i, n) fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, true, MOD, root);

    fa.resize(m);
    return fa;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    rep(i, n + 1) cin >> a[i];
    rep(j, m + 1) cin >> b[j];

    const ll P1 = 998244353;
    const ll ROOT1 = 3;
    const ll P2 = 1004535809;
    const ll ROOT2 = 3;
    const ll INV_P1_MOD_P2 = 669690699;

    auto c1 = convolution(a, b, P1, ROOT1);
    auto c2 = convolution(a, b, P2, ROOT2);

    ll ans = 0;
    int k = sz(c1);
    for(int i = 0; i < k; i++) {
        ll t = (c2[i] - c1[i] + P2) % P2;
        t = t * INV_P1_MOD_P2 % P2;
        ll ck = c1[i] + P1 * t;

        ans ^= ck;
    }
    cout << ans << '\n';
    return 0;
}
