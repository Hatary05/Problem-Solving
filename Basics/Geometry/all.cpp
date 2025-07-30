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
