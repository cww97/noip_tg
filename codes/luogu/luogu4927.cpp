#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = LL(1e5 + 7) << 2;
const LL MOD = 998244353;

LL sqr(LL x){return x*x;}
LL gcd(LL x, LL y){
    if (y) while((x %= y) && (y %= x));
    return x + y;
}
LL power(LL a, LL x){
    LL ans = 1;
    for (; x; x >>= 1){
        if (x & 1) ans = (ans * a) % MOD;//不能直接乘 
        a = (a * a) % MOD;
    }
    return ans % MOD;
}

LL arr[N];

struct SegTree{
    #define lc (rt << 1)
    #define rc (rt << 1 | 1)
    #define lson rt<<1, l, mid
    #define rson rt<<1|1, mid+1, r

    LL n;
    // for one Node
    LL sum[N], len[N], tag[N];
    LL len_2[N], len_sum[N];  // include child nodes
    LL con[N]; // contribution, also include child nodes

    // commonly pushUp
    void pushUp(const LL &rt) {
        sum[rt] = sum[lc] + sum[rc];
        len_sum[rt] = len[rt]*sum[rt] + len_sum[lc] + len_sum[rc];
        con[rt] = sqr(sum[rt]) + con[lc] + con[rc];
    }

    void Tag(const LL &rt, const LL &l, const LL &r, const LL &v){
        sum[rt] += v * (r-l+1);
        tag[rt] += v;
        con[rt] += 2*v*len_sum[rt] + sqr(v)*len_2[rt];
        len_sum[rt] += v * len_2[rt];
    }

    void pushDown(const LL &rt, const LL &l, const LL &r){
        if (!tag[rt]) return;
        LL mid = (l+r) >> 1;
        Tag(lson, tag[rt]);
        Tag(rson, tag[rt]);
        tag[rt] = 0;
    }

    void build(const LL &rt, const LL &l, const LL &r) {
        if (l == r) {
            sum[rt] = len_sum[rt] = arr[l];
            len[rt] = len_2[rt] = 1;
            tag[rt] = 0;
            con[rt] = sqr(sum[rt]);
            return;
        }
        LL mid = (l + r) >> 1;
        build(lson);
        build(rson);
        len[rt] = len[lc] + len[rc];
        len_2[rt] = sqr(len[rt]) + len_2[lc] + len_2[rc];
        tag[rt] = 0;
        pushUp(rt);
    }

    void update(const LL &rt, const LL &l, const LL &r, const LL &L, const LL &R, const LL &v) {
        if (L <= l && r <= R) {
            Tag(rt, l, r, v);
            return;
        }
        LL mid = (l + r) >> 1;
        pushDown(rt, l, r);
        if (L <= mid) update(lson, L, R, v);
        if (mid <  R) update(rson, L, R, v);
        pushUp(rt);
    }

    void query(){ // prLL ans;
        LL p = con[1], q = sum[1], gd = gcd(p, q);
        p /= gd, q /= gd;
        //prLLf("%d, %d: ", p, q);
        LL ans = ((p%MOD) * power(q, MOD-2)) % MOD;
        printf("%lld\n", ans);
    }

    void prLL(LL rt, LL l, LL r){ // prLL tree
        printf("%d: [%d, %d], len = %d, len_2 = %d, sum = %d, len_sum = %d, tag = %d, con = %d\n", 
            rt, l, r, len[rt], len_2[rt], sum[rt], len_sum[rt], tag[rt], con[rt]);
        if (l == r) return;
        LL mid = (l + r) >> 1;
        prLL(rt<<1, l, mid);
        prLL(rt<<1|1, mid+1, r);
    }
} T;


int main(){
    //freopen("in.txt", "r", stdin);
    LL n, m;
    scanf("%lld%lld", &n, &m);
    for (LL i = 1; i <= n; i++){
        scanf("%lld", &arr[i]);
    }
    T.build(1, 1, n);
    //T.print(1, 1, n);

    for (LL op, l, r, v; m--;){
        scanf("%lld", &op);
        if (op==2) T.query();
        else{ // update
            scanf("%lld%lld%lld", &l, &r, &v);
            T.update(1, 1, n, l, r, v);
        }
    }
    return 0;
}