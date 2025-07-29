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

struct lazyseg {
    int n;
    vector<ll> t, lazy;
    lazyseg(const vector<ll>& a) {
        n = 1 << (int)ceil(log2(sz(a)));
        t.assign(n << 1, 0); lazy.assign(n << 1, 0);

        for(int i = 0; i < sz(a); i++) t[i + n] = a[i];
        for(int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1]; 
    }
    void push(int i, int l, int r) {
        if(!lazy[i]) return;

        ll v = lazy[i];
        t[i] += v * (r - l + 1);
        if(l != r) {
            lazy[i << 1] += v; 
            lazy[i << 1 | 1] += v;
        }
        lazy[i] = 0;
    }
    void update(int l, int r, ll v) { update(l, r, 1, v, 0, n - 1);}
    void update(int l, int r, int i, ll v, int nl, int nr) {
        push(i, nl, nr);
        if(nr < l || r < nl) return;
        if(l <= nl && nr <= r) {
            lazy[i] += v;
            push(i, nl, nr);
            return;
        }

        int mid = (nl + nr) / 2;
        update(l, r, i << 1, v, nl, mid);
        update(l, r, i << 1 | 1, v, mid + 1, nr);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    ll sum(int l, int r) { return sum(l, r, 1, 0, n - 1);}
    ll sum(int l, int r, int i, int nl, int nr) {
        push(i, nl, nr);
        if(nr < l || r < nl) return 0;
        if(l <= nl && nr <= r) return t[i];
        int mid = (nl + nr) / 2;
        return sum(l, r, i << 1, nl, mid) + sum(l, r, i << 1 | 1, mid + 1, nr);
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
    int q = m + k;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    lazyseg seg(a);
    while(q--){
        int cmd; cin >> cmd;
        int l, r; cin >> l >> r;
        l--; r--;
        if(cmd == 1) {
            ll d; cin >> d;
            seg.update(l, r, d);
        }
        else if(cmd == 2) {
            cout << seg.sum(l, r) << '\n';
        }
    }
    return 0;
}
