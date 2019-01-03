//P2158 [SDOI2008]仪仗队
#include <bits/stdc++.h>
using namespace std;
const int N = 44444;

bool is_prime[N];
int prime[N], prime_cnt, phi[N];

void getPrime(int N){
    memset(is_prime, true, sizeof is_prime);
    is_prime[1] = false;
    phi[1] = 1;
    for (int i =2; i < N; i++){
        if (is_prime[i]){
            prime[++prime_cnt] = i;
            phi[i] = i-1;
        }
        for (int j = 1; j <= prime_cnt && prime[j]*i < N; j++){
            is_prime[prime[j]*i] = false;
            if (i % prime[j] == 0){
                phi[i*prime[j]] = phi[i] * prime[j];
            }else{
                phi[i*prime[j]] = phi[i] * phi[prime[j]];
            }
        } 
    }
}

int main() {
    int n, ans;
    cin >> n;
    if (n == 1){
        ans = 0;
    }else{
        getPrime(n+7);
        ans = 0;
        for (int i = 1; i < n; i++){
            ans += phi[i];
            printf("%d %d\n", i, phi[i]);
        }
        ans = ans * 2 + 1;
    }
    cout << ans << endl;
    return 0;
}
