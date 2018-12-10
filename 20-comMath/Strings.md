# Counting Arrays


## 题目描述

定义一个`01`串的权值为，每次把该字符串的最后两位变成一位（如果是两个`0`就变成`1`，否则变成`0`），最后只剩一位即为该字符串的权值，问包含`n`个`0`和`m`个`1`的权为`g`的长度为`n+m`的`01`串个数

## 输入格式

一行三个整数`n`,`m`,`g`。

## 输出格式

输出满足条件的`01`串个数，答案需要对`1e9+7`取膜。

## 输入样例

    2 2 0

## 输出样例

    4

## 样例解释

共有如下`4`个满足条件的`01`串：`0011`, `1001`, `1010`, `1100`
    
## 数据范围
- `0 ≤ n, m ≤ 10^5`
- `n + m ≥ 1`
- `0 ≤ g ≤ 1`

**【测试网站】**

[codeforces](https://codeforces.com/problemset/problem/336/D) 

## 题目分析
   
  `n=0`时，如果`m=1`则权为`1`，否则权为`0`

  `m=0`时，如果n为奇数则权为`0`，否则权为`1`

  `n,m≠0`时，如果想得到权为`1`的字符串，只有两种情况

    1. 奇数个`0+1+`非空任意数，这样奇数个`0`后面必然多一个`0`变成偶数个`0`，权是`1`
    2. 偶数个`0+1`，`01`变成`0`，进而变成偶数个`0`，权是`1`
    
  分别计数即得到权为`1`的字符串个数，如果问的是权为`0`的字符串，则拿总数`C(n+m，n)`减去权为`1`的字符串即可

  
## 代码示例

```c++

#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 200005;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n,m,g;
ll fac[maxn],inv[maxn];

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

void init()    //通过逆元预处理，以便O(1)求解大范围组合数
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
    scanf("%d%d%d",&n,&m,&g);
    if(n==0)
    {
        if(m==1&&g==1||m>1&&g==0) puts("1");
        else puts("0");
    }
    else if(m==0)
    {
        if(n%2&&g==0||n%2==0&&g==1) puts("1");
        else puts("0");
    }
    else
    {
        ll ans=0;
        for(int i=1;i<=n;i+=2)
        {
            if(n-i+m-1) ans=(ans+C(n-i+m-1,m-1))%mod;
        }
        if(n%2==0&&m==1) ans++;
        if(g==0) ans=(C(n+m,m)-ans+mod)%mod;
        printf("%lld\n",ans);
    }
}


```
   
   
   
