//boj - 11408 열혈강호 5
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

const int MAXN = 444 << 1;
const int INF = 1e9 + 7;
struct MCMF{
    struct edge{int to, cap, w, rev;};
    int n, s, t;
    vector<edge> adj[MAXN];
    int d[MAXN], p[MAXN], pe[MAXN];
    void add(int u, int v, int cap, int cost){
        adj[u].push_back({v, cap, cost, sz(adj[v])});
        adj[v].push_back({u, 0, -cost, sz(adj[u]) - 1});
    }
    bool dijkstra(){
        fill(d, d + MAXN, INF); fill(p, p + MAXN, -1);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({d[s] = 0, s});
        while(!pq.empty()){
            auto[w, cur] = pq.top(); pq.pop();
            if(d[cur] < w) continue;

            rep(i, sz(adj[cur])){
                edge &e = adj[cur][i];
                if(e.cap <= 0) continue;
                int nw = w + e.w;
                if(nw < d[e.to]){
                    pq.push({d[e.to] = nw, e.to});
                    p[e.to] = cur; pe[e.to] = i;
                }
            }
        }
        return (p[t] != -1);
    }
    pii exe(){
        int mnf = 0, mnc = 0;
        while(dijkstra()){
            int f = INF;
            for(int v = t; v != s; v = p[v]){
                f = min(f, adj[p[v]][pe[v]].cap);
            }
            for(int v = t; v != s; v = p[v]){
                edge &e = adj[p[v]][pe[v]];
                e.cap -= f;
                adj[v][e.rev].cap += f;
                mnc += e.w * f;
            }
            mnf += f;
        }
        return {mnf, mnc};
    }
};
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m; cin >> n >> m;
    int s = 0, t = n + m + 1;
    MCMF mcmf = {t + 1, s, t};

    for(int i = 1; i <= n; i++){
        mcmf.add(s, i, 1, 0);
    }
    for(int i = 1; i <= n; i++){
        int q; cin >> q;
        rep(_, q){
            int a, b; cin >> a >> b;
            mcmf.add(i, n + a, 1, b);
        }
    }
    for(int i = 1; i <= m; i++){
        mcmf.add(n + i, t, 1, 0);
    }

    auto[flow, cost] = mcmf.exe();
    cout << flow << '\n' << cost << endl;
    return 0;
}
