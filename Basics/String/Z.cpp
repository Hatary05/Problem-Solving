//string S에서 prefix와 suffix가 일치 하는 string si에 대하여, 
//S에서 si가 몇번 나타나는지 O(n)으로 탐색 가능
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

vector<int> getZ(const string& s){
    int n = sz(s);
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++){
        if(i <= r) z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r){
            r = i + z[i] - 1; l = i;
        }
    }
    return z;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string s; cin >> s;
    vector<int> z = getZ(s);

    int n = sz(s);
    vector<int> freq(n + 1, 0);
    for(int i = 1; i < n; i++){
        if(z[i] > 0) freq[z[i]]++;
    }
    for(int i = n - 1; i >= 1; i--){
        freq[i] += freq[i + 1];
    }

    vector<int> cand;
    cand.push_back(n);
    for(int i = 1; i < n; i++){
        if(i + z[i] == n) cand.push_back(z[i]);
    }
    sort(all(cand)); compress(cand);
    cout << sz(cand) << '\n';
    for(auto l : cand){
        cout << l << ' ' << freq[l] + 1 << '\n';
    }
    return 0;
}
