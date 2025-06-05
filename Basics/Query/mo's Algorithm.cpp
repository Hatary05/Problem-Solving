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

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int m; cin >> m;
    struct query{int l, r, idx, block;};
    vector<query> q(m);
    int sz_block = sqrt(n);
    rep(i, m){
        int l, r; cin >> l >> r;
        q[i] = {l, r, i, l / sz_block};
    }
    sort(all(q), [](auto a, auto b){
        if(a.block != b.block) return a.block < b.block;
        return a.r < b.r;
    });

    const int MAXV = 1e6 + 6;
    static int freq[MAXV];
    int cnt = 0;
    auto add = [&](int idx){
        int x = a[idx];
        if(++freq[x] == 1) cnt++;
    };
    auto remove = [&](int idx){
        int x = a[idx];
        if(--freq[x] == 0) cnt--;
    };

    int l = 1, r = 0;
    vector<int> ans(m);
    rep(i, m){
        while(r < q[i].r) add(++r);
        while(r > q[i].r) remove(r--);
        while(l < q[i].l) remove(l++);
        while(l > q[i].l) add(--l);
        ans[q[i].idx] = cnt;
    }
    for(auto &x : ans) cout << x << '\n';
    return 0;
}
