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

const int MOD = 998244353;
const int ROOT = 3; //MOD의 원시근
ll exp(ll x, ll e){
    ll ret = 1;
    while(e){
        if(e & 1) ret = ret * x % MOD;
        x = x * x % MOD; e >>= 1;
    }
    return ret;
}
void ntt(vector<ll>& a, bool invert){
    int n = sz(a);
    for(int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        ll wlen = exp(ROOT, (MOD - 1) / len);
        if(invert) wlen = exp(wlen, MOD - 2);
        for(int i = 0; i < n; i += len){
            ll w = 1;
            for(int j = 0; j < len / 2; j++){
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v < MOD) ? u + v : u + v - MOD;
                a[i + j + len / 2] = (u - v >= 0) ? u - v : u - v + MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if(invert){
        ll n_inv = exp(n, MOD - 2);
        for(auto &x : a) x = x * n_inv % MOD;
    }
}
vector<ll> convolution(const vector<ll>& a, const vector<ll>& b){
    vector<ll> fa(all(a)), fb(all(b));
    int n = sz(a) + sz(b) - 1;
    int flag = 1;
    for(; flag < n; flag <<= 1);
    fa.resize(flag); fb.resize(flag);

    ntt(fa, false), ntt(fb, false);
    rep(i, flag) fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, true);

    fa.resize(n);
    return fa;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    reverse(all(a));
    b.insert(b.end(), all(b));
    vector<ll> conv = convolution(b, a);

    ll ans = 0;
    for(int i = n - 1; i <= 2*(n + 1); i++){
        if(i >= sz(conv)) break;
        ans = max(ans, conv[i]);
    }
    cout << ans << endl;
    return 0;
}
