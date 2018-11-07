#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// (a + b) % mod == ((a % mod) + (b % mod)) % mod, *
LL power0(LL a, LL x, LL mod){
    LL ans = 1;
    for (int i = 1; i <= x; i++){
        ans *= a;
        ans %= mod;
    }
    return ans % mod;
}

LL power(LL a, LL x, const LL &mod){
    //a ^ x = (a ^(x/2)) ^ 2
    if (x == 0) return 1 % mod;
    LL tmp = power(a, x >> 1, mod);
    LL ans = tmp * tmp % mod;
    if (x % 2 == 1) ans *= a;
    return ans % mod;
}

//快速乘法
LL fast_multi(LL m, LL n, LL mod){
    LL ans = 0;//注意初始化是0，不是1
    n = (n % mod + mod) % mod;
    for (;n; n >>= 1){
        if (n & 1) ans = (ans + m) % mod;
        m = (m + m) % mod;//和快速幂一样，只不过这里是加
    }
    return ans % mod;
}
LL fast_pow(LL a, LL n, LL mod){//快速幂
    LL ans = 1;
    for (;n;n >>= 1){
        if (n & 1) ans = fast_multi(ans, a, mod) % mod;//不能直接乘
        a = fast_multi(a, a, mod) % mod;
    }
    return ans;
}

int main(){
    LL b, p, k;
    scanf("%lld%lld%lld", &b, &p, &k);
    printf("%lld^%lld mod %lld=%lld\n", b, p, k, power(b, p, k));
    return 0;
}
