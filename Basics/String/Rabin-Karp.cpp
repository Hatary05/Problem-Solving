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

int n; string s;
const int MOD1 = 1e9 + 7, BASE1 = 31;
const int MOD2 = 998244353, BASE2 = 53;
bool f(int x){
    unordered_map<ll, ll> mp;
    ll val1 = 0, e1 = 1;
    ll val2 = 0, e2 = 1;
    rep(i, x){
        val1 = (val1 * BASE1 + s[i]) % MOD1;
        e1 = (e1 * BASE1) % MOD1;

        val2 = (val2 * BASE2 + s[i]) % MOD2;
        e2 = (e2 * BASE2) % MOD2;
    }
    mp[val1] = val2;

    bool found = false;
    for(int i = x; i < n; i++){
        val1 = (val1 * BASE1 + s[i] - s[i - x] * e1 % MOD1 + MOD1) % MOD1;
        val2 = (val2 * BASE2 + s[i] - s[i - x] * e2 % MOD2 + MOD2) % MOD2;

        if(mp.count(val1) && mp[val1] == val2){
            found = true; break;
        }
        else mp[val1] = val2;
    }
    return found;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> s;
    int l = 0, r = n;
    while(r - l > 1){
        int mid = (l + r) / 2;
        if(f(mid)) l = mid;
        else r = mid;
    }
    cout << l << endl;
    return 0;
}
