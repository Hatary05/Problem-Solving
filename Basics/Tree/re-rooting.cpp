//그래프 내 모든 정점과의 거리가 최소인 노드 찾기 O(n)
// boj - 27730
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

int n;
const int MAXN = 1e5 + 15;
vector<pll> adj[MAXN];
ll down[MAXN], all[MAXN], sz[MAXN];
void dfs1(int u, int p){
    sz[u] = 1; down[u] = 0;
    for(auto [v, w] : adj[u]){
        if(v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        down[u] += down[v] + sz[v] * w;
    }
}
void dfs2(int u, int p){
    for(auto [v, w] : adj[u]){
        if(v == p) continue;
        all[v] = all[u] - sz[v]*w + (n - sz[v])*w;
        dfs2(v, u);
    }
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    rep(i, n - 1){
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    dfs1(0, -1);
    all[0] = down[0];
    dfs2(0, -1);
    
    const ll INF = 1e18;
    ll minE = INF, szE = n, idxE = -1;
    rep(i, n) if(all[i] < minE) {minE = all[i]; idxE = i + 1;}

    rep(i, MAXN) adj[i].clear();
    fill(down, down + MAXN, 0);
    fill(all, all + MAXN, 0);
    fill(sz, sz + MAXN, 0);

    cin >> n;
    rep(i, n - 1){
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    dfs1(0, -1);
    all[0] = down[0];
    dfs2(0, -1);
    
    ll minW = INF, szW = n, idxW = -1;
    rep(i, n) if(all[i] < minW) {minW = all[i]; idxW = i + 1;}

    cout << idxE << ' ' << idxW << '\n';
    ll ans = szW * minE + szE * minW + szE*szW;
    cout << ans << '\n';
    return 0;
}
