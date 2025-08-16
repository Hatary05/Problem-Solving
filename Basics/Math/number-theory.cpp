//선형체로 mu function 구하기 1e7까지
vector<int> primes;
vector<int> mu(MAXN+1), lp(MAXN+1);
void linear_sieve(int N){
    mu[1]=1;
    for(int i=2;i<=N;i++){
        if(!lp[i]) lp[i]=i, primes.push_back(i), mu[i]=-1;
        for(int p:primes){
            if(p>lp[i] || 1LL*i*p>N) break;
            lp[i*p]=p;
            if(p==lp[i]){ mu[i*p]=0; break; }
            else mu[i*p]=-mu[i];
        }
    }
}

//약수 제타, 뫼비우스 변환 길이 n
// divisor zeta transform: F[n] += sum_{d|n, d<n} F[d]
void divisor_zeta(vector<long long>& F){
    int N = (int)F.size()-1;
    for(int d=1; d<=N; ++d)
        for(int m=d+d; m<=N; m+=d)
            F[m] += F[d];
}
// divisor mobius inverse (inverse of above)
void divisor_mobius_inverse(vector<long long>& F){
    int N = (int)F.size()-1;
    for(int d=1; d<=N; ++d)
        for(int m=d+d; m<=N; m+=d)
            F[m] -= F[d];
}

//배수 제타, 뫼비우스 변환
// multiple zeta: F[d] += sum_{m: d|m, m>d} F[m]
void multiple_zeta(vector<long long>& F){
    int N = (int)F.size()-1;
    for(int d=N; d>=1; --d)
        for(int m=d+d; m<=N; m+=d)
            F[d] += F[m];
}
// multiple mobius inverse (inverse of above)
void multiple_mobius_inverse(vector<long long>& F){
    int N = (int)F.size()-1;
    for(int d=N; d>=1; --d)
        for(int m=d+d; m<=N; m+=d)
            F[d] -= F[m];
}

//배열에서 gcd = 1의 쌍의 개수
// freq[v] = 값 v의 빈도, 1..V
long long count_pairs_gcd1(const vector<int>& freq){
    int V = (int)freq.size()-1;
    static vector<int> cnt; cnt.assign(V+1, 0);
    for(int g=1; g<=V; ++g)
        for(int m=g; m<=V; m+=g)
            cnt[g] += freq[m];           // 배수 카운트

    // μ 전처리 필요: mu[1..V]
    long long ans=0;
    for(int g=1; g<=V; ++g){
        long long c = cnt[g];
        if(c>=2) ans += 1LL*mu[g]* (c*(c-1)/2);
    }
    return ans;
}

//하이퍼볼라 트릭
long long coprime_rect(long long m, long long n, const vector<int>& M){ // M[x]=sum_{k<=x} mu[k]
    if(m>n) swap(m,n);
    long long ans=0;
    for(long long i=1; i<=m; ){
        long long v1=m/i, v2=n/i;
        long long j=min(m/v1, n/v2);
        ans += 1LL*(M[j]-M[i-1]) * v1 * v2;
        i=j+1;
    }
    return ans;
}

//
