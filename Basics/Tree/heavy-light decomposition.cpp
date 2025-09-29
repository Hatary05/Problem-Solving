//거꾸로 된 u 생각하면 path_update, query부분 이해가 쉬움
 . . .
.   . .
  .    .
//heavy[u]는 자식 중에서 heavy인 node
//head는 같은 chain인 것들 중 가장 위에 있는 조상
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define rep(i, n) for(int i = 0; i < (n); i++)
#define all(x) (x).begin(), (x).end()
#define compress(x) (x).erase(unique(all(x)), x.end())
#define fr first
#define sc second

const ll MOD = (1LL << 32) - 1;
struct lazyseg {
    struct Node {ll sum, m, c;};
    int n;
    vector<Node> t;
    lazyseg(int m) {
        n = 1 << (int)ceil(log2(m));
        t.assign(n << 1, Node(0, 1, 0));
    }
    void apply(int i, int l, int r, ll mul, ll add) {
        mul &= MOD, add &= MOD;
        auto &[s, m, c] = t[i];
        s = (s * mul + (add * (r - l + 1) & MOD)) & MOD;
        m = (m * mul) & MOD;
        c = (c * mul + add) & MOD;
    }
    void push(int i, int nl, int nr) {
        auto &[s, m, c] = t[i];
        if(m == 1 && c == 0) return;

        int mid = (nl + nr) / 2;
        apply(i << 1, nl, mid, m, c);
        apply(i << 1 | 1, mid + 1, nr, m, c);
        m = 1, c = 0;
    }
    void range_update(int i, int l, int r, int nl, int nr, ll mul, ll add) {
        if(nr < l || r < nl) return;
        if(l <= nl && nr <= r) {apply(i, nl, nr, mul, add); return;}
        push(i, nl, nr);
        int mid = (nl + nr) / 2;
        range_update(i << 1, l, r, nl, mid, mul, add);
        range_update(i << 1 | 1, l, r, mid + 1, nr, mul, add);
        t[i].sum = (t[i << 1].sum + t[i << 1 | 1].sum) & MOD;
    }
    ll query(int i, int l, int r, int nl, int nr) {
        if(nr < l || r < nl) return 0;
        if(l <= nl && nr <= r) return t[i].sum;
        push(i, nl, nr);
        int mid = (nl + nr) / 2;
        ll L = query(i << 1, l, r, nl, mid);
        ll R = query(i << 1 | 1, l, r, mid + 1, nr);
        return (L + R) & MOD;
    }
    void update(int l, int r, ll mul, ll add) {
        range_update(1, l, r, 0, n - 1, mul, add);
    }
    ll query(int l, int r) {
        return query(1, l, r, 0, n - 1);
    }
};
const int MAXN = 5e5 + 55;
vector<int> adj[MAXN];
int in[MAXN], id = 0;
int par[MAXN], dep[MAXN], sz[MAXN];
int hev[MAXN], head[MAXN];
void dfs1(int u, int p) {
    sz[u] = 1, hev[u] = -1;

    int best = 0;
    for(auto v : adj[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs1(v, u);
        sz[u] += sz[v];
        if(best < sz[v]) {
            best = sz[v];
            hev[u] = v;
        }
    }
}
void dfs2(int u, int h) {
    head[u] = h;
    in[u] = id++;
    if(hev[u] != -1) {
        dfs2(hev[u], h);
        for(auto v : adj[u]) {
            if(v == par[u] || v == hev[u]) continue;
            dfs2(v, v);
        }
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, q; cin >> n >> q;
    rep(_, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(0, -1);
    dfs2(0, 0);

    lazyseg seg(MAXN);
    auto path_update = [&](int u, int v, ll mul, ll add) {
        while(head[u] != head[v]) {
            if(dep[head[u]] < dep[head[v]]) swap(u, v);
            seg.update(in[head[u]], in[u], mul, add);
            u = par[head[u]];
        }
        if(dep[u] > dep[v]) swap(u, v);
        seg.update(in[u], in[v], mul, add);
    };
    auto path_query = [&](int u, int v) {
        ll res = 0;
        while(head[u] != head[v]) {
            if(dep[head[u]] < dep[head[v]]) swap(u, v);
            res = (res + seg.query(in[head[u]], in[u])) & MOD;
            u = par[head[u]];
        }
        if(dep[u] > dep[v]) swap(u, v);
        res = (res + seg.query(in[u], in[v])) & MOD;
        return res;
    };
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            ll x, v; cin >> x >> v;
            x--;
            seg.update(in[x], in[x] + sz[x] - 1, 1, v);
        }
        else if(op == 2) {
            ll x, y, v; cin >> x >> y >> v;
            x--, y--;
            path_update(x, y, 1, v);
        }
        else if(op == 3) {
            ll x, v; cin >> x >> v;
            x--;
            seg.update(in[x], in[x] + sz[x] - 1, v, 0);
        }
        else if(op == 4) {
            ll x, y, v; cin >> x >> y >> v;
            x--, y--;
            path_update(x, y, v, 0);
        }
        else if(op == 5) {
            ll x; cin >> x;
            x--;
            cout << seg.query(in[x], in[x] + sz[x] - 1) << '\n';
        }
        else {
            ll x, y; cin >> x >> y;
            x--, y--;
            cout << path_query(x, y) << '\n';
        }
    }
    return 0;
}
