const ll root = 62;
ll exp(ll x, ll e, ll mod) {
    ll r = 1;
    while(e) {
        if(e & 1) r = r * x % mod;
        x = x * x % mod; e >>= 1;
    }
    return r;
}
void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for(static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, exp(root, MOD >> s, MOD)};
        rep(i, k, 2*k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i >> 1] | ((i & 1) << L)) >> 1;
    rep(i, 0, n) if(i < rev[i]) swap(a[i], a[rev[i]]);
    for(int k = 1; k < n; k *= 2) {
        for(int i = 0; i < n; i += 2*k) rep(j, 0, k) {
            ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
            a[i + j + k] = ai - z + (z > ai ? MOD : 0);
            ai += (ai + z >= MOD ? z - MOD : z);
        }
    }
}
vl conv(const vl &a, const vl &b) {
    if(a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s);
    int n = 1 << B;
    int inv = exp(n, MOD - 2, MOD);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i, 0, n) {
        out[-i & (n - 1)] = (L[i] * R[i] % MOD) * inv % MOD;
    }
    ntt(out);
    return {out.begin(), out.begin() + s};
}
