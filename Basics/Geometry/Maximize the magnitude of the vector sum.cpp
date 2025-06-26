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
    const ld PI = acos((ld)-1.0);
    struct point {
        ll x, y;
        ld ang;
    };
    vector<point> p;
    rep(_, n){
        ll x, y; cin >> x >> y;
        ld ang = atan2((ld)y, (ld)x);
        if(ang < 0) ang += 2*PI;
        p.push_back({x, y, ang});
    }

    rep(i, n) p.push_back({p[i].x, p[i].y, p[i].ang + 2*PI});
    sort(all(p), [](auto &a, auto &b){
        return a.ang < b.ang;
    });

    ll ans = 0;
    ll sx = 0, sy = 0;
    int m = sz(p);
    int j = 0;
    for(int i = 0; i < n; i++){
        while(j < m && p[j].ang - p[i].ang <= PI){
            sx += p[j].x;
            sy += p[j].y;
            ans = max(ans, sx*sx + sy*sy);
            j++;
        }

        sx -= p[i].x;
        sy -= p[i].y;
        ans = max(ans, sx*sx + sy*sy);
    }
    cout << ans << endl;
    return 0;
}
