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

const ll INF = 2e18;
struct line {
    ll m, c;
    ll f(ll x) {return m*x + c;}
};
struct node {
    int l, r;
    ll s, e;
    line L;
};
struct lichao {
    vector<node> t;
    lichao(ll s, ll e) {t.push_back({-1, -1, s, e, {0, -INF}});}
    void update(int i, line v) {
        ll s = t[i].s, e = t[i].e;

        line lo = t[i].L, hi = v;
        if(lo.f(s) > hi.f(s)) swap(lo, hi);
        if(lo.f(e) <= hi.f(e)) {
            t[i].L = hi; return;
        }

        ll m = (s + e) / 2;
        if(lo.f(m) < hi.f(m)) {
            t[i].L = hi;
            if(t[i].r == -1) {
                t[i].r = sz(t);
                t.push_back({-1, -1, m + 1, e, lo});
            }
            update(t[i].r, lo);
        }
        else {
            t[i].L = lo;
            if(t[i].l == -1) {
                t[i].l = sz(t);
                t.push_back({-1, -1, s, m, hi});
            }
            update(t[i].l, hi);
        }
    }
    ll query(int i, ll x) {
        if(i == -1) return -INF;
        ll m = (t[i].s + t[i].e) / 2;
        if(x <= m) return max(t[i].L.f(x), query(t[i].l, x));
        else return max(t[i].L.f(x), query(t[i].r, x));
    }
};
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int q; cin >> q;
    lichao seg(-2e12, 2e12);
    while(q--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll m, c; cin >> m >> c;
            seg.update(0, {m, c});
        }
        else if(cmd == 2) {
            ll x; cin >> x;
            cout << seg.query(0, x) << '\n';
        }
    }

    return 0;
}
