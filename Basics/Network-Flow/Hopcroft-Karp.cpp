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
struct HopcroftKarp{
    int n;
    vector<vector<int>> adj;
    vector<int> A, B, dist;
    HopcroftKarp(int n) : n(n), adj(n){
        A.assign(n, -1);
        B.assign(n, -1);
        dist.assign(n, 0);
    }
    void add(int u, int v){adj[u].push_back(v);}
    bool bfs(){
        queue<int> q;
        rep(u, n){
            if(A[u] == -1){
                dist[u] = 0; q.push(u);
            }
            else dist[u] = INF;
        }
        int d = INF;
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(dist[u] < d){
                for(auto v : adj[u]){
                    if(B[v] == -1){
                        d = dist[u] + 1;
                    }
                    else if(dist[B[v]] == INF){
                        dist[B[v]] = dist[u] + 1;
                        q.push(B[v]);
                    }
                }
            }
        }
        return d != INF;
    }
    bool dfs(int u, int d){
        if(dist[u] == d){
            dist[u] = INF;
            for(auto v : adj[u]){
                int w = B[v];
                if(w == -1 || (dist[w] == d + 1 && dfs(w, d + 1))){
                    A[u] = v, B[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int match(){
        int cnt = 0;
        while(bfs()){
            for(int u = 0; u < n; u++){
                if(A[u] == -1 && dfs(u, 0)) cnt++;
            }
        }
        return cnt;
    }
};
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int tc; cin >> tc;
    while(tc--){
        int n, m; cin >> n >> m;
        HopcroftKarp hk(n + 1);
        rep(_, m){
            int u, v; cin >> u >> v;
            hk.add(u, v);
        }
        int ans = hk.match();
        cout << ans << '\n';
    }
    return 0;
}
