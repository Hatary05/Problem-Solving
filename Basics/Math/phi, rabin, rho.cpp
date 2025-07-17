//Given n, calculate SUM of GCD(k, n) = 1 (1 <= k <= n)
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

ll gcd(ll x, ll y){
    while(y) swap(x %= y, y);
    return x;
}
ll mul_mod(ll a, ll b, ll mod){
    return (__int128)a * b % mod;
}
ll exp_mod(ll x, ll e, ll mod){
    ll ret = 1;
    while(e){
        if(e & 1) ret = mul_mod(ret, x, mod);
        x = mul_mod(x, x, mod); e >>= 1;
    }
    return ret;
}
vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool is_prime(ll n){
    if(n < 2) return false;
    for(auto p : primes) if(n % p == 0) return (n == p);

    ll d = n - 1, s = 0;
    while((d & 1) == 0) {d >>= 1; s++;}
    
    for(auto p : primes){
        ll x = exp_mod(p, d, n);
        if(x == 1 || x == n - 1) continue;

        bool ok = false;
        for(int e = 1; e < s; e++){
            x = mul_mod(x, x, n);
            if(x == n - 1) {ok = true; break;}
        }
        if(!ok) return false;
    }
    return true;
}
ll f(ll x, ll c, ll n) {return mul_mod(x, x, n) + c;}
ll rho(ll n){
    if((n & 1) == 0) return 2;
    mt19937_64 rng(random_device{}());
    while(true){
        ll c = rng() % (n - 1) + 1;
        ll x = 2, y = 2, d = 1;
        while(d == 1){
            x = f(x, c, n);
            y = f(f(y, c, n), c, n);
            d = gcd(abs(x - y), n);
        }
        if(d != n) return d;
    }
}
void factor(ll n, map<ll, ll> &ret){
    if(n == 1) return;
    if(is_prime(n)) {ret[n]++; return;}
    ll d = rho(n);
    factor(d, ret); factor(n / d, ret);
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n; cin >> n;
    map<ll, ll> factors;
    factor(n, factors);

    ll phi = n;
    for(auto [p, _] : factors) {
        phi = phi / p * (p - 1);
    }
    cout << phi << '\n';
    return 0;
}
