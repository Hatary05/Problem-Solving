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

const int MAXN = 2e5 + 25;
const int INF = 1e9 + 7;
int n, k;
vector<pii> g[MAXN];
int sub[MAXN];
bool removed[MAXN];
int dfs_size(int u, int p) {
    sub[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p || removed[v]) continue;
        sub[u] += dfs_size(v, u);
    }
    return sub[u];
}
int find_centroid(int u, int p, int tot) {
    for(auto [v, w] : g[u]) if(v != p && !removed[v]) {
        if(sub[v] * 2 > tot) return find_centroid(v, u, tot);
    }
    return u;
}
void collect(int u, int p, ll dist, int cnt, vector<pii> &out) {
    if(dist > k) return;
    out.emplace_back(dist, cnt);
    for(auto [v, w] : g[u]) {
        if(v == p || removed[v]) continue;
        collect(v, u, dist + w, cnt + 1, out);
    }
}

int ans = INF;
const int MAXL = 1e6 + 16;
vector<int> best(MAXL, INF);
void process_centroid(int c) {
    vector<int> touched;
    if(best[0] == INF) {best[0] = 0, touched.push_back(0);}

    for(auto [v, w] : g[c]) {
        if(removed[v]) continue;
        
        vector<pii> paths;
        collect(v, c, w, 1, paths);

        for(auto [d, cnt] : paths) {
            if(d > k) continue;
            int need = k - d;
            if(need >= 0 && best[need] != INF) {
                ans = min(ans, best[need] + cnt);
            }
        }
        for(auto [d, cnt] : paths) {
            if(d > k) continue;
            if(cnt < best[d]) {
                if(best[d] == INF) touched.push_back(d);
                best[d] = cnt;
            }
        }
    }

    for(auto d : touched) best[d] = INF;
}
void decompose(int entry) {
    ll tot = dfs_size(entry, -1);
    int c = find_centroid(entry, -1, tot);
    removed[c] = true;

    process_centroid(c);
    for(auto [v, w] : g[c]) if(!removed[v]) {
        decompose(v);
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> k;
    rep(_, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    decompose(0);
    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}
