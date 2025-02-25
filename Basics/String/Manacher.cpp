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

ll bruteforce(const string& s){
    ll cnt = 0; int n = sz(s);
    auto src = [&](int l, int r){
        while(0 <= l && r < n && s[l] == s[r]){
            cnt++; l--; r++;
        }
    };
    rep(i, n){
        src(i, i); src(i, i + 1);
    }
    return cnt;
}
ll manacher(const string& s){
    ll cnt = 0;
    string t = "#";
    for(auto c : s){
        t += c; t += "#";
    }

    int n = sz(t);
    vector<int> p(n, 0);
    int c = 0, r = 0;
    rep(i, n){
        int oi = 2 * c - i;
        if(i <= r) p[i] = min(r - i, p[oi]);
        while(0 <= i - p[i] - 1 && i + p[i] + 1 < n 
            && t[i - p[i] - 1] == t[i + p[i] + 1]
        ) p[i]++;
        if(i + p[i] > r){
            c = i; r = i + p[i];
        }
        cnt += (p[i] + 1) / 2;
    }
    return cnt;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string s; cin >> s;
    cout << manacher(s) << endl;
    return 0;
}
