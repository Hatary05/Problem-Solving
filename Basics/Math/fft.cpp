using cd = complex<double>;
const ld PI = acosl(-1.0L);
void fft(vector<cd> &a, bool inv = false) {
    int n = sz(a);
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n / 2;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        if(inv) ang *= -1;

        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len) {
            cd w = 1; int m = len / 2;
            for(int j = 0; j < m; j++) {
                cd u = a[i + j], v = a[i + j + m] * w;
                a[i + j] = u + v;
                a[i + j + m] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv) for(auto &x : a) x /= n;
}
vector<ll> conv(vector<ll> &a, vector<ll> &b) {
    vector<cd> fa(all(a)), fb(all(b));
    int m = sz(fa) + sz(fb), n = 1;
    while(n < m) n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa); fft(fb);
    for(int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> ret(n);
    rep(i, n) ret[i] = llround(fa[i].real());
    return ret;
}
