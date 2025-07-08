//https://www.acmicpc.net/problem/25548
// sum_{1 <= x <= 1e9} tau(x), tau(x)는 x의 약수의 개수
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

const ll MAXP = 1e6 + 16;
ll pre[MAXP | 1], tau[MAXP | 1];
unordered_map<ll, ll> mp;
ll T(ll x){
    if(x <= MAXP) return pre[x];
    if(mp.count(x)) return mp[x];

    ll s = sqrt(x);
    ll ret = 0;
    for(ll i = 1; i <= s; i++) ret += x / i;
    ret = 2 * ret - s * s;
    return mp[x] = ret;
}
ll query(ll l, ll r){
    return T(r) - T(l - 1);
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n; cin >> n;
    ll L = min(n, MAXP);
    for(int i = 1; i <= L; i++) for(int j = i; j <= L; j += i) tau[j]++;
    for(int i = 1; i <= L; i++) pre[i] = pre[i - 1] + tau[i];

    ll ans = 0;
    for(ll l = 1, r; l <= n; l = r + 1){
        ll v = n / l; r = n / v;
        ans += query(l, r) * v;
    }
    cout << ans << endl;
    return 0;
}
