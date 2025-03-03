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

using line_t = long double;
const line_t is_query = -1e18;
struct Line{
    line_t m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line &rhs) const{
        if(rhs.b != is_query)
            return m < rhs.m;
        const Line* s = succ();
        if(!s) return false;
        line_t x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line>{
    bool bad(iterator y){
        auto z = next(y);
        if(y == begin()){
            if(z == end()) return false;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if(z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
    }
    void insert_line(line_t m, line_t b){
        auto y = insert({m, b});
        y->succ = [=]{
            return next(y) == end() ? nullptr : &*next(y);
        };
        if(bad(y)){erase(y); return;}
        while(next(y) != end() && bad(next(y))) erase(next(y));
        while(y != begin() && bad(prev(y))) erase(prev(y));
    }
    line_t query(line_t x){
        auto l = *lower_bound((Line){x, is_query});
        return l.m * x + l.b;
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
    vector<ll> a(n + 1), b(n + 1), dp(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    dp[1] = 0;
    HullDynamic H;
    H.insert_line(-b[1], -dp[1]);
    for(int i = 2; i <= n; i++){
        dp[i] = -(ll)round(H.query(a[i]));
        H.insert_line(-b[i], -dp[i]);
    }
    cout << dp[n] << '\n';
    return 0;
}
