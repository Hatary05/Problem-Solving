//O(nloglogn) MAXN = 1e6정도여도 무리없음
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

const int MAXN = 1010101;
vector<pii> factor[MAXN];
void build_factor(){ //O(n log log n)
    for(int i = 2; i < MAXN; i++){
        if(!factor[i].empty()) continue;
        for(int j = i; j < MAXN; j += i){
            int x = j, cnt = 0;
            while(x % i == 0){
                x /= i; cnt++;
            }
            factor[j].emplace_back(i, cnt);
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

    build_factor();
    int n; cin >> n;
    for(int i = 1; i <= n; i++){
        cout << i << " = ";
        for(auto[x, e] : factor[i]) cout << x << "^" << e << ' ';
        cout << '\n';
    }
    return 0;
}
