inline ll sgn(ll x) {return (x > 0) - (x < 0);}
inline ll cross(pll a, pll b, pll c) {return (b.fr-a.fr)*(c.sc-a.sc) - (c.fr-a.fr)*(b.sc-a.sc);}
inline ll ccw(pll a, pll b, pll c) {return sgn(cross(a, b, c));}
bool seg_intersect(pll a, pll b, pll c, pll d){
    ll ab = ccw(a,b,c) * ccw(a,b,d);
    ll cd = ccw(c,d,a) * ccw(c,d,b);

    if(ab==0 && cd==0){
        if(a>b) swap(a,b);
        if(c>d) swap(c,d);
        return (a <= d && c <= b);
    }
    return ab<=0 && cd<=0;
}
vector<pll> convex_hull(vector<pll> &points) {
    sort(all(points)); compress(points);
    if(sz(points) <= 2) return points;

    vector<pll> up, low;
    for(auto i : points) {
        while(sz(up) >= 2 && ccw(up[sz(up)-2], up.back(), i) >= 0) up.pop_back();
        while(sz(low) >= 2 && ccw(low[sz(low)-2], low.back(), i) <= 0) low.pop_back();
        up.push_back(i), low.push_back(i);
    }
    reverse(all(up));
    up.pop_back(); low.pop_back();
    low.insert(low.end(), all(up));

    return low;
}
bool P_in_the_Polygon(const vector<Pt>& P, const Pt& q) {
    int n = (int)P.size();
    if (n == 1) return (q.x == P[0].x && q.y == P[0].y);
    if (n == 2) return onSeg(P[0], P[1], q);

    if (ccw(P[0], P[1], q) < 0) return false;
    if (ccw(P[0], P[n-1], q) > 0) return false;

    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (ccw(P[0], P[m], q) >= 0) l = m;
        else                         r = m;
    }
    return ccw(P[l], P[(l+1)%n], q) >= 0;
}
