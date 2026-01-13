struct lazyseg {
    int n;
    vector<ll> t, lz;
    lazyseg(int lim) {
        n = 1;
        while(n < lim) n <<= 1;
        t.assign(n << 1, 0);
        lz.assign(n << 1, 0);
    }

    void apply(int i, int nl, int nr, ll w) {
        t[i] += w * (nr - nl + 1);
        lz[i] += w;
    }
    void push(int i, int nl, int nr) {
        if(lz[i] == 0 || nl == nr) return;
        int jd = (nl + nr) / 2;
        apply(i << 1, nl, jd, lz[i]);
        apply(i << 1 | 1, jd + 1, nr, lz[i]);
        lz[i] = 0;
    }
    void update(int l, int r, ll w) {
        update(1, l, r, w, 0, n - 1);
    }
    void update(int i, int l, int r, ll w, int nl, int nr) {
        if(nr < l || r < nl) return;
        if(l <= nl && nr <= r) {
            apply(i, nl, nr, w);
            return;
        }
        push(i, nl, nr);
        int jd = (nl + nr) / 2;
        update(i << 1, l, r, w, nl, jd);
        update(i << 1 | 1, l, r, w, jd + 1, nr);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    ll query(int p) {
        return query(1, p, 0, n - 1);
    }
    ll query(int i, int p, int nl, int nr) {
        if(nr < p || p < nl) return 0;
        if(nl == nr) return t[i];
        push(i, nl, nr);
        int jd = (nl + nr) / 2;
        if(p <= jd) return query(i << 1, p, nl, jd);
        else return query(i << 1 | 1, p, jd + 1, nr);
    }
};
