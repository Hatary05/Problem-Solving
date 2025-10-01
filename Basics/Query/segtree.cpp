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

struct segtree {
    int n;
    vector<ll> t;
    segtree(const vector<ll>& a) {
        n = 1 << (int)ceil(log2(sz(a)));
        t.assign(n << 1, 0);
        rep(i, sz(a)) t[i + n] = a[i];
        for(int i = n - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void update(int i, ll v) {
        i += n;
        t[i] = v;
        for(i >>= 1; i >= 1; i >>= 1) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    ll query(int l, int r) {
        ll ret = 0;
        for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) ret += t[l++];
            if(~r & 1) ret += t[r--];
        }
        return ret;
    }
};
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    segtree seg(a);
    int q = m + k;
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            ll i, v; cin >> i >> v;
            i--;
            seg.update(i, v);
        }
        else if(op == 2) {
            ll l, r; cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r) << '\n';
        }
    }
    return 0;
}
