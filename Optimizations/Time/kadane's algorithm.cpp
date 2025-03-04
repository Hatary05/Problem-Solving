//연속한 부분 수열의 최대합을 O(n)으로 구하는 법
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

//O(n^2)
int bruteforce(const vector<int>& a){
    int n = sz(a), mx = INT_MIN;
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = i; j < n; j++){
            sum += a[j];
            mx = max(mx, sum);
        }
    }
    return mx;
}
//O(n)
int kadane(const vector<int>& a){
    int mx = INT_MIN, cur = 0;
    for(auto x : a){
        cur = max(x, cur + x);
        mx = max(mx, cur);
    }
    return mx;
}
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    cout << bruteforce(a) << endl;
    cout << kadane(a) << endl;
    return 0;
}

