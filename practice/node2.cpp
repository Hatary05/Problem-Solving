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

const int MAXN = 101010;
vector<int> p(MAXN, -1);
int find(int x){
    if(p[x] < 0) return x;
    return p[x] = find(p[x]);
}
void merge(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;
    p[a] += p[b];
    p[b] = a;
}
struct eg{
    int u, v, w;
    bool operator<(const eg &rhs) const{
        return w < rhs.w;
    }
}; vector<eg> egs;
ll Mst(){
    sort(all(egs));
    int ret = 0;
    for(auto i : egs){
        if(find(i.u) == find(i.v)) continue;
        ret += i.w;
        merge(i.u, i.v);
    }
    return ret;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m; cin >> n >> m;
    rep(_, m){
        int u, v, w; cin >> u >> v >> w;
        egs.push_back({u, v, w});
    }
    cout << Mst();
}
