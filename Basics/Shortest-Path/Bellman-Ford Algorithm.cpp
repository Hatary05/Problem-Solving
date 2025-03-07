// 갱신 조건 (d[u] + w < d[v])에서
// 만약 st가 포함된 그래프에서만 negative cycle detected를 하고 싶으면
// (d[u] != INF && d[u] + w < d[v])로 바꿔 주어야함
// 지금 코드는 서로 연결되어있지 그래프에서도 음수 사이클을 검사함
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

int n, m;
const int MAXN = 505;
const int INF = 1e9 + 7;
struct edge{int u, v, w;};
vector<edge> edges;
int d[MAXN];
bool bellman_ford(int st){
    fill(d + 1, d + n + 1, INF);
    d[st] = 0;
    rep(_, n - 1){
        for(auto[u, v, w] : edges){
            if(d[u] + w < d[v]) d[v] = d[u] + w;
        }
    }

    for(auto[u, v, w] : edges){
        if(d[u] + w < d[v]) return true;
    }
    return false;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    rep(_, m){
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    if(bellman_ford(1)) cout << "Negative Cycle Detected";
    else{
        for(int i = 1; i <= n; i++){
            if(d[i] == INF) cout << "INF" << '\n';
            else cout << d[i] << '\n';
        }
    }
    return 0;
}
