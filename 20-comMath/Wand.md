# Wand


## 题目描述

有`N`个数字(`1~N`)，问它的全排列中，有多少个方案，使得`a[i]==i`的个数大于等于`k`.

## 输入格式

第一行一个整数`T`，表示数据组数。
接下来`T`行，每行两个整数`n`和`k`。

## 输出格式

对于每组数据输出答案，占一行,答案对`1e9+7`取模。

## 输入样例

    2
    1 1
    3 1

## 输出样例

    1 
    4

## 样例解释

对于第二组数据，满足条件的四个排列为：`{1,2,3}`,`{1,3,2}`,`{2,1,3}`,`{3,2,1}`
    
## 数据范围
- `1 ≤ T ≤ 10`
- `1 ≤ n ≤ 10^4`
- `1 ≤ k ≤ 100`
- `k ≤ n`

**【测试网站】**

[FOJ](https://vjudge.net/problem/FZU-2282) 

## 题目分析
   
  题目要求`a[i]==i`的个数大于等于`k`，那我们可以转化为`a[i]==i`的个数为`x`( `k≤ x ≤n` )这个子问题,对于每个`x`求解，然后求和即可。
  
  那么对于现在的题目，我们只要先把任意`x`个数放在对应位置上，然后把剩下`n-x`个数都不放在对应位置上即可。前面的部分显而易见我们可以用组合数`C(n,x)`解决。
  
  而后半部分，我们需要引入错排的概念，错排就是把所有元素都不放对应位置上的方案数。那么如何求解错排的方案数呢？
  
  我们用`dp[i]`表示把`i`个元素都不放在对应位置上的方案数。假设现在要放第`i`个元素，且放在位置`pos`上，共有`i-1`种放法(因为不能放在位置`i`上)
  
  对于`pos`这个元素来说，共有两种情况：
    
    1. 如果放在位置`i`上，那我们剩下的`i-2`个元素只要错排就可以了，方案数为`dp[i-2]`.
    
    2. 如果不放在位置`i`上，那么其实要做的就是把除元素`i`以外的`i-1`个元素错排，方案数为`dp[i-1]`.
  
  综上所述，错排公式为`dp[i]=(i-1)*(dp[i-1]+dp[i-1])`
  
  那么对于子问题的求解答案便为`C(n,x)*dp[n-x]`
  
## 代码示例

```c++

#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 20005;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n,k;
ll fac[maxn],inv[maxn];
ll dp[maxn];

ll fast_mod(ll a,ll x,ll Mod)
{
    ll ans=1;
    while(x)
    {
        if(x&1) ans=(ans*a)%Mod;
        a=(a*a)%Mod;
        x/=2;
    }
    return ans;
}

void init()
{
    fac[0]=1;
    for(int i=1; i<maxn; i++)
    {
        fac[i]=(fac[i-1]*i)%mod;
    }
    inv[maxn-1]=fast_mod(fac[maxn-1],mod-2,mod);
    for(int i=maxn-2; i>=0; i--)
    {
        inv[i]=(inv[i+1]*(i+1))%mod;
    }
}

ll C(int n,int m)
{
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
    init();
    dp[0]=1;
    dp[1]=0;
    for(int i=1;i<maxn;i++)
    {
        dp[i]=(ll)(i-1)*(dp[i-1]+dp[i-2]);
        dp[i]%=mod;
    }
    rush()
    {
        scanf("%d%d",&n,&k);
        ll ans=0;
        for(int i=k;i<=n;i++)
        {
            ans+=C(n,i)*dp[n-i];
            ans%=mod;
        }
        printf("%lld\n",ans);
    }
}


```
