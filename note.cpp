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

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int tc; cin >> tc;
    while(tc--){
        multiset<int> s;

        int q; cin >> q;
        while(q--){
            char cmd; cin >> cmd;
            if(cmd == 'I'){
                int x; cin >> x;
                s.insert(x);
            }
            else{
                int x; cin >> x;
                if(s.empty()) continue;
                if(x == -1){
                    auto it = s.begin();
                    s.erase(it);
                }
                else{
                    auto it = prev(s.end());
                    s.erase(it);
                }
            }
        }
        if(s.empty()) cout << "EMPTY" << '\n';
        else{
            auto mx = prev(s.end());
            auto mn = s.begin();
            cout << *mx << ' ' << *mn << '\n';
        }
    }
}
