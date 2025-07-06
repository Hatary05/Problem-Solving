ll extgcd(ll a, ll b, ll &x, ll &y){
    ll u1 = 1, u2 = 0, v1 = 0, v2 = 1;
    while(b){
        ll q = a / b;
        swap(a -= q*b, b);
        swap(u1 -= q*u2, u2);
        swap(v1 -= q*v2, v2);
    }
    x = u1, y = v1;
    return a;
};
ll gcd(ll a, ll b){
    while(b){
        ll q = a / b;
        swap(a -= q * b, b);
    }
    return a;
};
ll modinv(ll a, ll mod){
    ll x, y;
    if(extgcd(a, mod, x, y) != 1) return -1;

    x = (x % mod + mod) % mod;
    return x;
}
