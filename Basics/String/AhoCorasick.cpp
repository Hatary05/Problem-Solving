// 집합 S의 원소들이 string s에 하나라도 부분 문자열로 존재하는지 탐색할 수 있음
// O(집합 원소 총 길이 + s의 길이) = O(NL + M);
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

struct AhoCorasick{
    static const int MAXC = 26;
    struct node{
        int nxt[MAXC], fail = 0;
        bool op = false;
        node(){rep(i, MAXC) nxt[i] = -1;}
    };
    vector<node> trie;
    AhoCorasick(){
        trie.push_back(node());
    };

    void insert(const string& s){
        int cur = 0;
        for(auto c : s){
            int p = c - 'a';
            if(trie[cur].nxt[p] == -1){
                trie[cur].nxt[p] = sz(trie);
                trie.push_back(node());
            }
            cur = trie[cur].nxt[p];
        }
        trie[cur].op = true;
    }
    void build(){
        queue<int> q;
        rep(i, MAXC){
            int nxt = trie[0].nxt[i];
            if(nxt != -1){
                trie[nxt].fail = 0;
                q.push(nxt);
            }
            else trie[0].nxt[i] = 0;
        }
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(trie[trie[cur].fail].op) trie[cur].op = true;
            rep(i, MAXC){
                int nxt = trie[cur].nxt[i];
                if(nxt != -1){
                    trie[nxt].fail = trie[trie[cur].fail].nxt[i];
                    q.push(nxt);
                }
                else trie[cur].nxt[i] = trie[trie[cur].fail].nxt[i];
            } 
        }
    }
    bool find(const string& s){
        int cur = 0;
        for(auto c : s){
            int p = c - 'a';
            cur = trie[cur].nxt[p];
            if(trie[cur].op) return true;
        }
        return false;
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
    AhoCorasick ac;
    rep(_, n){
        string s; cin >> s;
        ac.insert(s);
    }
    ac.build();

    int q; cin >> q;
    while(q--){
        string s; cin >> s;
        cout << (ac.find(s) ? "YES" : "NO") << '\n';
    }
    return 0;
}
