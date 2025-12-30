#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define rep(i, n) for(int i = 0; i < (n); i++)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fr first
#define sc second

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, q; cin >> n >> q;

    ll ans = n;
    map<ll, ll> fs;
    while(q--) {
        ll l, r; cin >> l >> r;
        auto it = fs.lower_bound(l);
        if(it != fs.begin() && prev(it)->sc >= l) it--;

        ll nl = l, nr = r, w = 0;
        while(it != fs.end() && it->fr <= r) {
            nl = min(nl, it->fr);
            nr = max(nr, it->sc);
            w += it->sc - it->fr + 1;
            it = fs.erase(it);
        }

        ll add = (nr - nl + 1) - w;
        fs[nl] = nr;
        ans -= add;
        cout << ans << '\n';
    }
    return 0;
}
