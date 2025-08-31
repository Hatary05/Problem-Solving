/*
w[x] = val(x) - val(parant(x)) 부모와의 potential 차이
pot(x) = val(x) - val(root(x)) 집합의 root와의 potential 차이

w[ry] = d + pot(x) - pot(y)의 의미
집합 Y를 집합 X에 포함
                        pot(y)
    pot(x)
    
    root(x)             root(y)
-----------------------------------
w[ry] = val(root(y)) - val(root(x)) 이므로
root(x) 기준 -> pot(x) + d - pot(y) -> root(y)가 되는 것이다.
*/
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

struct dsu {
    int n;
    vector<ll> p, w;
    dsu(int n) : n(n) {
        p.assign(n + 1, -1);
        w.assign(n + 1, 0);
    }
    int find(int x) {
        if(p[x] < 0) return x;
        int r = find(p[x]);
        w[x] += w[p[x]];
        return p[x] = r;
    }
    void merge(int x, int y, ll d) {
        int rx = find(x), ry = find(y);
        if(rx == ry) return;

        if(p[rx] < p[ry]) {
            w[ry] = d + pot(x) - pot(y);
            p[rx] += p[ry], p[ry] = rx;
        }
        else {
            w[rx] = pot(y) - pot(x) - d;
            p[ry] += p[rx], p[rx] = ry;
        }
    }
    inline bool same(int x, int y) {return (find(x) == find(y));}
    inline ll pot(int x) {find(x); return w[x];}
    inline ll diff(int x, int y) { return pot(y) - pot(x);}
};
void solve(int n, int m) {
    dsu uf(n);
    auto mes = [&](int a, int b, int w) {
        uf.merge(a, b, w);
    };
    auto ask = [&](int a, int b) {
        if(!uf.same(a, b)) {
            cout << "UNKNOWN" << '\n';
            return;
        }
        cout << uf.diff(a, b) << '\n';
    };

    rep(_, m) {
        char op; cin >> op;
        if(op == '!') {
            int a, b, w; cin >> a >> b >> w;
            mes(a, b, w);
        }
        else if(op == '?') {
            int a, b; cin >> a >> b;
            ask(a, b);
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

    int n, m;
    while(true) {
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        solve(n, m);
    }
    return 0;
}
