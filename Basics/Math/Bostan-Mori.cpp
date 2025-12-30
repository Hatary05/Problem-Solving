// ============================================================
// ICPC Template (C++17) - modint(998244353) + NTT + Bostan-Mori
// Compile: g++ -std=gnu++17 -O2 -pipe -static -s main.cpp
// ============================================================

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

// -------------------- ModInt (998244353) --------------------
static constexpr int MOD = 998244353;     // NTT-friendly prime
static constexpr int G   = 3;             // primitive root for MOD

struct Mint {
    int v;
    Mint(long long _v=0) { set_v(_v % MOD); }
    inline void set_v(long long _v) { v = int(_v < 0 ? _v + MOD : _v); }

    inline Mint& operator+=(const Mint& o){ v += o.v; if(v >= MOD) v -= MOD; return *this; }
    inline Mint& operator-=(const Mint& o){ v -= o.v; if(v < 0) v += MOD; return *this; }
    inline Mint& operator*=(const Mint& o){ v = int((long long)v * o.v % MOD); return *this; }

    static Mint powmod(Mint a, long long e){
        Mint r = 1;
        while(e > 0){
            if(e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    static Mint invmod(Mint a){ return powmod(a, MOD - 2); }

    inline Mint& operator/=(const Mint& o){ return (*this) *= invmod(o); }

    friend Mint operator+(Mint a, const Mint& b){ return a += b; }
    friend Mint operator-(Mint a, const Mint& b){ return a -= b; }
    friend Mint operator*(Mint a, const Mint& b){ return a *= b; }
    friend Mint operator/(Mint a, const Mint& b){ return a /= b; }
    friend Mint operator-(Mint a){ if(a.v) a.v = MOD - a.v; return a; }
};

// -------------------- NTT --------------------
static inline int ceil_pow2(int n){
    int x = 1;
    while(x < n) x <<= 1;
    return x;
}

static void ntt(vector<Mint>& a, bool invert){
    int n = (int)a.size();

    // bit-reversal permutation
    for(int i=1, j=0; i<n; i++){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len=2; len<=n; len<<=1){
        Mint wlen = Mint::powmod(Mint(G), (MOD - 1) / len);
        if(invert) wlen = Mint::invmod(wlen);

        for(int i=0; i<n; i+=len){
            Mint w = 1;
            int half = len >> 1;
            for(int j=0; j<half; j++){
                Mint u = a[i + j];
                Mint v = a[i + j + half] * w;
                a[i + j] = u + v;
                a[i + j + half] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert){
        Mint inv_n = Mint::invmod(Mint(n));
        for(auto &x: a) x *= inv_n;
    }
}

static vector<Mint> convolution(vector<Mint> a, vector<Mint> b){
    int n = (int)a.size(), m = (int)b.size();
    if(!n || !m) return {};
    // small fallback
    if(1LL * n * m <= 2000){
        vector<Mint> c(n + m - 1);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                c[i + j] += a[i] * b[j];
        return c;
    }
    int sz = ceil_pow2(n + m - 1);
    a.resize(sz); b.resize(sz);
    ntt(a, false);
    ntt(b, false);
    for(int i=0; i<sz; i++) a[i] *= b[i];
    ntt(a, true);
    a.resize(n + m - 1);
    return a;
}

// -------------------- Poly helpers --------------------
static inline void trim(vector<Mint>& p){
    while((int)p.size() > 1 && p.back().v == 0) p.pop_back();
}

static vector<Mint> even_part(const vector<Mint>& a){
    vector<Mint> b((a.size() + 1) / 2);
    for(int i=0; i<(int)a.size(); i+=2) b[i/2] = a[i];
    trim(b);
    return b;
}
static vector<Mint> odd_part(const vector<Mint>& a){
    vector<Mint> b(a.size() / 2);
    for(int i=1; i<(int)a.size(); i+=2) b[i/2] = a[i];
    trim(b);
    return b;
}

// -------------------- Bostan–Mori --------------------
// returns [x^k] P(x)/Q(x), assuming Q(0) != 0
static Mint bostan_mori(vector<Mint> P, vector<Mint> Q, ull k){
    trim(P); trim(Q);
    // Q(0) must be non-zero
    // (for our counting problem, Q(0)=1 always)
    while(k > 0){
        vector<Mint> Qm = Q; // Q(-x)
        for(int i=1; i<(int)Qm.size(); i+=2) Qm[i] = -Qm[i];

        auto PQ = convolution(P, Qm);
        auto QQ = convolution(Q, Qm);

        if(k & 1ULL) P = odd_part(PQ);
        else         P = even_part(PQ);

        Q = even_part(QQ);
        // keep them clean (optional, but 안정성에 좋음)
        trim(P); trim(Q);

        k >>= 1;
    }
    // k==0: coefficient = P(0)/Q(0)
    return P[0] / Q[0];
}

// ============================================================
// Example usage for your problem:
// ans = [x^M] 1 / ((1-x)*Π(1-x^{Ai}))
// ============================================================
static void multiply_one_minus_xk(vector<Mint>& Q, int k){
    int old = (int)Q.size();
    Q.resize(old + k); // appended zeros
    for(int i = old + k - 1; i >= k; --i){
        Q[i] -= Q[i - k];
    }
    trim(Q);
}

static Mint solve_count_leq_sum(const vector<int>& A, ull M){
    vector<Mint> Q(1, Mint(1));           // Q(x)=1
    for(int a: A) multiply_one_minus_xk(Q, a);
    multiply_one_minus_xk(Q, 1);          // (1-x)
    vector<Mint> P(1, Mint(1));           // numerator 1
    return bostan_mori(P, Q, M);
}

// -------------------- Main (optional demo) --------------------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ull M;
    cin >> N >> M;
    vector<int> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    Mint ans = solve_count_leq_sum(A, M);
    cout << ans.v << "\n";
    return 0;
}
