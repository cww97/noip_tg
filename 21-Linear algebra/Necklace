# Necklace


## 题目描述

一条长度为`n`的项链，由红色珠子和蓝色珠子（分别用`1`和`0`表示）组成

在连续的素数子段中，红色珠子的个数不能少于蓝色珠子

问组成这个项链有多少种方案，求方案数模`1000000007`

## 输入格式

第一行一个整数`T`，表示数据组数。

第二行一个整数`n`，表示珠子总个数。



## 输出格式

输出走法的数量。

## 输入样例

    2 3

## 输出样例

    3
 
    
## 数据范围
- `2 ≤ N,M ≤ 1000`

**【测试网站】**

[51nod 1118](https://www.51nod.com/Challenge/Problem.html#!#problemId=1118) 

## 题目分析

  根据题意，我们总共需要往右走`n-1`步，往下走`m-1`步，共`n+m-2`步，我们要做的其实就是在这`n+m-2`步中选出`m-1`个位置向右走即可。那么方案数即为`C(n+m-2,n-1)`。
  
  由于数据范围较小，我们直接了可以用杨辉三角求组合数。时间复杂度为`O(n * n)`

## 代码示例1

```
#include <cstdio>
int dp[1001][1001],n,m,ans;
int main()
{
    for(int i=1;i<=1001;++i)
    {
        dp[1][i]=1;
        dp[i][1]=1;
    }
    scanf("%d%d",&m,&n);
    for(int i=2;i<=m;++i)
    {
        for(int j=2;j<=n;++j)
        {
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
            dp[i][j]%=1000000007;
        }
    }
    printf("%d",dp[m][n]);
}
```
  当然也可以通过预处理快速地求组合数。总时间复杂度`O(n)`

## 代码示例2

```c++
#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 2005;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n,m;
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
    scanf("%d%d",&n,&m);
    printf("%lld\n",C(n+m-2,n-1));
}

```
   
   
   
