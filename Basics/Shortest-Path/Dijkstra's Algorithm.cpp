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

const int INF = 1e9 + 7;
const int MAXN = 101010;
vector<pii> adj[MAXN];
int d[MAXN];
void bfs(int st){
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({d[st] = 0, st});
    while(!pq.empty()){
        auto [w, cur] = pq.top(); pq.pop();
        if(d[cur] < w) continue;

        for(auto [dw, nxt] : adj[cur]){
            int nw = w + dw;
            if(nw < d[nxt]) pq.push({d[nxt] = nw, nxt});
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

    int n, m, st; cin >> n >> m >> st;
    rep(_, m){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }
    memset(d, INF, sizeof(d));
    bfs(st);
    for(int i = 1; i <= n; i++){
        cout << (d[i] != INF ? d[i] : -1) << ' ';
    }
    return 0;
}
