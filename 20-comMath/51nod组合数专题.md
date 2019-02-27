# 51nod组合数专题

## 大大走格子

测试网站[51nod 1486](https://www.51nod.com/Challenge/Problem.html#!#problemId=1486) 

### 题目描述

有一个`h`行`w`列的棋盘，里面有一些格子是不能走的，现在要求从左上角走到右下角的方案数。

### 输入格式

单组测试数据。

第一行有三个整数`h`, `w`, `n`，表示棋盘的行和列，还有不能走的格子的数目。

接下来`n`行描述格子，第i行有两个整数`ri`, `ci`，表示格子所在的行和列。

输入保证起点和终点不会有不能走的格子。


### 输出格式

输出答案对`1000000007`取余的结果。

### 输入样例

    3 4 2
    2 2
    2 3

### 输出样例

    2
 
### 数据范围
- `1 ≤ h, w ≤ 10^5`
- `1 ≤ n ≤ 2000`
- `1 ≤ ri ≤ h, 1 ≤ ci ≤ w`

### 题目分析

 用`ans[i]`代表从起点走到第`i`个障碍格子且中间不经过其他障碍格子的方案数(终点也要算作障碍格子)。
 
 所以一开始我们需要对障碍物点根据`x`,`y`坐标进行排序，那我们求解`ans[i]`的时候只要计算`(1,1)`走到`(ri,ci)`的方案数减去所有的`ans[j]*C(ri-rj+ci-cj,ri-rj)`,其中`1 ≤ j < i`。即减去经过前面障碍物的方案个数。
 
 `j`作为经过的第一个障碍物，后面无限制地随便走，这样保证了减去的方案不会重复也不会缺少。

### 代码示例

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

int n,m,q;
ll fac[maxn],inv[maxn];
ll ans[maxn];

struct node
{
    int x,y;
}a[maxn];

bool cmp(node a,node b)
{
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

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
    if(n-m<0) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

ll cal(int s,int t)
{
    return C(a[t].x-a[s].x+a[t].y-a[s].y,a[t].x-a[s].x);
}

int main()
{
    init();
    scanf("%d%d%d",&n,&m,&q);
    a[0].x=1,a[0].y=1;
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    a[q+1].x=n,a[q+1].y=m;
    sort(a+1,a+q+2,cmp);

    for(int i=1;i<=q+1;i++)
    {
        ans[i]=cal(0,i);
        for(int j=1;j<i;j++)
        {
            ans[i]=(ans[i]-ans[j]*cal(j,i)%mod+mod)%mod;
        }
    }
    printf("%lld\n",ans[q+1]);

}
```

## 机器人走方格

测试网站[51nod 1118](https://www.51nod.com/Challenge/Problem.html#!#problemId=1118) 

### 题目描述

`M` * `N` 的方格，一个机器人从左上走到右下，只能向右或向下走。有多少种不同的走法？

由于方法数量可能很大，只需要输出Mod `10^9 + 7`的结果。

- `2 ≤ N,M ≤ 1000`

### 题目分析

  根据题意，我们总共需要往右走`n-1`步，往下走`m-1`步，共`n+m-2`步，我们要做的其实就是在这`n+m-2`步中选出`m-1`个位置向右走即可。那么方案数即为`C(n+m-2,n-1)`。
  
  由于数据范围较小，我们直接了可以用杨辉三角求组合数。时间复杂度为`O(n * n)`

### 代码示例1

```c++
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

### 代码示例2

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
   
 ## 机器人走方格V2

测试网站[51nod 1119](https://www.51nod.com/Challenge/Problem.html#!#problemId=1119) 

### 题目描述

`M` * `N` 的方格，一个机器人从左上走到右下，只能向右或向下走。有多少种不同的走法？

由于方法数量可能很大，只需要输出Mod `10^9 + 7`的结果。
 
    
### 数据范围
- `2 ≤ N,M ≤ 1000000`



### 题目分析

  根据题意，我们总共需要往右走`n-1`步，往下走`m-1`步，共`n+m-2`步，我们要做的其实就是在这`n+m-2`步中选出`m-1`个位置向右走即可。那么方案数即为`C(n+m-2,n-1)`。
  
  跟之前的一题唯一的变化就是数据范围，这样我们显然不能用`O(n*n)`的方法求解，但还是可以用`O(n)`的方法二求解，改一下数据范围即可。

### 代码示例

```c++
#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 2000005;
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
   
## 机器人走方格V3

测试网站[51nod 1120](https://www.51nod.com/Challenge/Problem.html#!#problemId=1120) 

### 题目描述

` N * N `的方格，从左上到右下画一条线。一个机器人从左上走到右下，只能向右或向下走。

并要求只能在这条线的上面或下面走，不能穿越这条线，有多少种不同的走法？

由于方法数量可能很大，只需要输出Mod `10007`的结果。

- `2 ≤ N ≤ 10^9`



### 题目分析

 分析一下题意，我们可以这么转化，如果只能在这条线的下面走，相当于某一时刻向下走的次数要大于等于向右走的数量。
 
 那么我们可以联想到这不就是括号匹配吗，用卡特兰数求解。即为`C(2n,n)`-`C(2n,n-1)`,由于可以往上面走或者下面走，最后答案乘以`2`即可。
 
 由于这道题`n`的范围比较大，我们可以用`lucas`定理求组合数。

### 代码示例

```c++
#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 2000005;
const ll mod = 1e4+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n;

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

ll Niyuan(ll a,ll n)
{
    ll x,y;
    ll d=exgcd(a,n,x,y);
    if(d==1)
        return (x%n+n)%n;
    return -1;
}

ll muti(ll a,ll b)
{
    return (a%mod)*(b%mod)%mod;
}

ll solve(ll n,ll m)
{
    ll a=1,b=1;
    if(m>n)
        return 0ll;
    while(m)
    {
        a=(a*n)%mod;
        b=(b*m)%mod;
        m--;
        n--;
    }
    return muti(a,Niyuan(b,mod));
}

ll lucas(ll n,ll m)
{
    if(m==0)
        return 1ll;
    ll a=solve(n%mod,m%mod);
    ll b=lucas(n/mod,m/mod);
    return (a*b)%mod;
}


int main()
{
    scanf("%d",&n);
    n--;
    printf("%lld\n",2*(lucas(2*n,n)-lucas(2*n,n-1)+mod)%mod);
}


```
