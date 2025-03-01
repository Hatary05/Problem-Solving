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

vector<int> getpi(const string& s){
    int n = sz(s);
    vector<int> pi(n, 0);

    int j = 0;
    for(int i = 1; i < n; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j]) pi[i] = ++j;
    }
    return pi;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    vector<int> pi = getpi(s);

    cout << n - pi[n - 1] << endl;
    return 0;
}
