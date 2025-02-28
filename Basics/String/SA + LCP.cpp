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

vector<int> getSuffixArray(const string& s){
    int n = sz(s);
    vector<int> sa(n), rank(n), tmp(n);

    rep(i, n){sa[i] = i; rank[i] = s[i];}
    for(int k = 1; k < n; k <<= 1){
        auto cmp = [&](int i, int j){
            if(rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(all(sa), cmp);

        tmp[sa[0]] = 0;
        for(int i = 1; i < n; i++){
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        rank = tmp;
    }
    return sa;
}
vector<int> getLCP(const string& s, const vector<int>& sa){
    int n = sz(s);
    vector<int> lcp(n, 0), rank(n, 0);

    rep(i, n){rank[sa[i]] = i;}
    int h = 0;
    for(int i = 0; i < n; i++){
        if(rank[i] == 0) continue;
        int j = sa[rank[i] - 1];
        while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[rank[i]] = h;
        if(h > 0) h--;
    }
    return lcp;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string s; cin >> s;
    vector<int> sa = getSuffixArray(s);
    vector<int> lcp = getLCP(s, sa);
    for(auto x : sa) cout << x + 1 << ' ';
    cout << "\nx ";
    for(int i = 1; i < sz(s); i++) cout << lcp[i] << ' ';
    return 0;
}
