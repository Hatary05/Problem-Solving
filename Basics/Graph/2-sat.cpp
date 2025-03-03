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

struct TwoSat{
    int n;
    vector<vector<int>> g, gr;
    vector<bool> used;
    vector<int> order, comp;

    TwoSat(int n) : n(n){
        g.assign(n << 1, vector<int>());
        gr.assign(n << 1, vector<int>());
    }
    void add(int x, int y){
        g[x ^ 1].push_back(y);
        g[y ^ 1].push_back(x);
        gr[x].push_back(y ^ 1);
        gr[y].push_back(x ^ 1);
    }
    void dfs1(int v){
        used[v] = true;
        for(auto w : g[v]) if(!used[w]) dfs1(w);
        order.push_back(v);
    }
    void dfs2(int v, int cl){
        comp[v] = cl;
        for(auto w : gr[v]) if(comp[w] == -1) dfs2(w, cl);
    }

    bool solve(vector<bool>& assignment){
        int m = n << 1;
        used.assign(m, false);
        order.clear();
        rep(i, m) if(!used[i]) dfs1(i);
        comp.assign(m, -1);
        int cl = 0;
        for(int i = m - 1; i >= 0; i--){
            int v = order[i];
            if(comp[v] == -1) dfs2(v, cl++);
        }
        assignment.assign(n, false);
        for(int i = 0; i < n; i++){
            if(comp[i << 1] == comp[i << 1 | 1]) return false;
            assignment[i] = comp[i << 1] > comp[i << 1 | 1];
        }
        return true;
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
    TwoSat ts(n + 1);
    auto lit = [](int x){
        if(x < 0) return (-x) << 1 | 1;
        return x << 1;
    };
    rep(_, m){
        int x, y; cin >> x >> y;
        ts.add(lit(x), lit(y));
    }

    vector<bool> assignment;
    if(ts.solve(assignment)){
        cout << 1 << '\n';
    }
    else cout << 0 << '\n';
    return 0;
}
