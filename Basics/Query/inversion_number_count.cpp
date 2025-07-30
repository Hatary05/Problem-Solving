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

struct fenwick {
    int n;
    vector<ll> t;
    fenwick(int n) : n(n) {t.assign(n + 1, 0);}
    void add(int i, ll v = 1) {
        for(; i <= n; i += i & -i) t[i] += v;
    }
    ll sum(int i) {
        ll s = 0;
        for(; i; i -= i & -i) s += t[i];
        return s;
    }
};
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    vector<ll> comp(a);
    sort(all(comp)); compress(comp);
    auto get = [&](ll v) {
        return lower_bound(all(comp), v) - comp.begin() + 1;
    };

    fenwick fw(n);
    ll inv_n = 0;
    for(int i = n - 1; i >= 0; i--) {
        int p = get(a[i]);
        inv_n += fw.sum(p - 1);
        fw.add(p);
    }
    cout << inv_n << '\n';
    return 0;
}
