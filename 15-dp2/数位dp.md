# 数位DP

## 做题链接：[GO](https://vjudge.net/contest/284355)

### Password：aomeng

## 题目一：Bomb

[HDOJ 3555](http://acm.hdu.edu.cn/showproblem.php?pid=3555)

### 题意

给定`n`，求出`[0,n]`中包含`49`的数的个数。

### 思路1

用`dp[i][0]`表示长度为`i`且包含`49`的数的个数。

用`dp[i][1]`表示长度为`i`，不包含`49`但最高位为`9`的数的个数。

用`dp[i][2]`表示长度为`i`，不包含`49`但最高位不为`9`的数的个数。

然后根据题意转移即可

### 代码1

```c++
#include <bits/stdc++.h>
#define mst(a) memset(a,0,sizeof(a))
using namespace std;
long long dp[20][3];
void init()
{
    mst(dp);
    dp[0][2]=1;
    for(int i=1;i<=20;i++)
    {
        dp[i][0]=dp[i-1][0]*10+dp[i-1][1];   //含49
        dp[i][1]=dp[i-1][2];                 //不含49但最高位为9
        dp[i][2]=dp[i-1][2]*10-dp[i-1][1];   //不含49且最高位不为9
    }
}
long long fun(long long n)
{
    int len=1;
    int bit[25];
    while(n)
    {
        bit[len++]=n%10;
        n/=10;
    }
    bit[len]=0;
    int flag=0;
    long long sum=0;
    for(int i=len;i>0;i--)
    {
        sum+=bit[i]*dp[i-1][0];
        if(flag) sum+=bit[i]*dp[i-1][2];
        if(!flag&&bit[i]>4) sum+=dp[i-1][1];
        if(bit[i+1]==4&&bit[i]==9) flag=1;
    }
    return sum;
}
int main()
{
    init();
    int t;
    long long n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&n);
        printf("%lld\n",fun(n+1));
    }
    return 0;
}

```

### 思路2

数位`dp`

在写`dfs`的时候，

`st=0`:没有`49`且最后一位不为`4`, `st=1`：没有`49`且最后一位为`4`,  `st=2`：有`49`

`flag=1`表示无限制，`flag=0`表示有限制

用`dp[i][j]`表示考虑到第`i`位，且`st=j`时的个数。

### 代码2

```c++
#include <bits/stdc++.h>
#define mst(a) memset(a,-1,sizeof(a))
#define f(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int bit[20];
long long dp[20][3];

long long dfs(int pos,int st,int flag)
{
    if(pos==0) return st==2;
    if(flag&&dp[pos][st]!=-1) return dp[pos][st];
    long long sum=0;
    int x=flag?9:bit[pos];
    for(int i=0;i<x;i++)
    {
        if((st==2)||(st==1&&i==9))
            sum+=dfs(pos-1,2,flag||i<x);
        else if(i==4) sum+=dfs(pos-1,1,flag||i<x);
        else sum+=dfs(pos-1,0,flag||i<x);
    }
    if(flag) dp[pos][st]=sum;
    return sum;
}
long long cal(long long x)
{
    int len=0;
    while(x)
    {
        bit[++len]=x%10;
        x/=10;
    }
    return dfs(len,0,0);
}
int main()
{
    int t;
    scanf("%d",&t);
    mst(dp);
    while(t--)
    {
        long long n;
        scanf("%lld",&n);
        printf("%lld\n",cal(n));
    }
    return 0;
}

```


## 题目二：Sereja and Swaps

[Codeforces 426C](http://acm.hdu.edu.cn/showproblem.php?pid=5883)

### 题意

给定一个长度为`n`的序列 `a1,a2,...,an`

你有 k 次机会选择 一个`x`和`y (1≤x<y≤n)`，交换`ax`和`ay`。

`k`次机会不一定要全部用完，你需要操作完之后选择一个区间`[l,r]`,使得 `al +a[l+1] + ... +ar `最大。

### 思路

由于`n`比较小，我们考虑直接暴力贪心。

每次枚举最终的区间 `[l,r]`。 不断将 `[l,r]` 内最小的数换成外面最大的数。

即有`t≤k`个 `[l,r]` 内的数不算入，而有另外`t`个`[l,r]`外的数算入。

取最小的数和最大的数用优先队列实现即可。

时间复杂度`O(n^3*k)`

### 代码

```c++
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 305;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n,m;
int a[maxn];

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        int ans=-INF;
        for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
        {
            priority_queue<int,vector<int>, less<int> > out;
            priority_queue<int,vector<int>, greater<int> > in;
            for(int k=0;k<n;k++)
            {
                if(k>=i&&k<=j)  in.push(a[k]);
                else out.push(a[k]);
            }
            int temp=m;
            while(temp--)
            {
                if(in.size()==0||out.size()==0) break;
                int u=in.top();
                int v=out.top();
                if(v<=u) break;
                else
                {
                    in.pop(),out.pop();
                    in.push(v),out.push(u);
                }
            }
            int cnt=0;
            while(in.size())
            {
                int u=in.top();
                in.pop();
                cnt+=u;
            }
            ans=max(ans,cnt);
        }
        printf("%d\n",ans);
    }
}
```

### 拓展

上面的是`naive`版本，接下来我们考虑`n≤10000`的情况，如果还用上面的做法显然会超时

于是我们考虑用数位`dp`来解决这个问题。

我们知道，最后的答案肯定是一个区间，只是把区间内的一些数跟区间外的一些数进行了交换。

我们用`dp[idx][st][out][in]`来表示考虑到`a[idx]`，且状态为`st`，区间内`out`个数忽略，已经考虑了区间外`in`个数(即加进来的数的个数)的区间和最大值

对于`st`:

1. `st==0`时表示区间未开始
2. `st==1`时表示区间已经开始，但没有结束
3. `st==2`时表示区间已经结束

然后记忆化搜索即可,时间复杂度`O(n*k^2)`

### 代码

```c++
#include <cstdio>
#include <cmath>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 205;
const ll mod = 1e9+7;
const int INF = 1e9;
const double eps = 1e-6;

int n,k;
int a[maxn];
bool vis[maxn][3][15][15];
int dp[maxn][3][15][15];

int solve(int idx,int st,int out,int in)
{
    if(idx==n)
    {
        if(in==out&&st) return 0;
        return -INF;
    }
    if(vis[idx][st][out][in]) return dp[idx][st][out][in];
    int cnt=-INF;
    if(st==0)       //区间未开始
    {
        cnt=max(solve(idx+1,1,out,in)+a[idx],solve(idx+1,0,out,in));
        cnt=max(cnt,solve(idx+1,1,out+1,in));
        if(in<k) cnt=max(cnt,solve(idx+1,0,out,in+1)+a[idx]);
    }
    else if(st==1)  //区间开始，未结束
    {
        cnt=max(solve(idx+1,2,out,in),solve(idx+1,1,out,in)+a[idx]);
        if(out<k) cnt=max(cnt,solve(idx+1,1,out+1,in));
    }
    else
    {
        cnt=max(cnt,solve(idx+1,2,out,in));
        if(in<k) cnt=max(cnt,solve(idx+1,2,out,in+1)+a[idx]);
    }

    vis[idx][st][out][in]=1;
    return dp[idx][st][out][in]=cnt;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    mst(vis,0);
    mst(dp,0);
    printf("%d\n",solve(0,0,0,0));
}
```


## 题目三：windy数

[BZOJ 1026](https://www.lydsy.com/JudgeOnline/problem.php?id=4513)

### 题意

RT

### 思路

用`dp[i][j]`表示长度为`i`，最高位为`j`的`windy`数个数，可以用暴力求得。

然后就是不断地分解输入的这个数，累加答案即可。

唯一值得注意的是，`solve`函数求出的是`[1,x-1]`内`windy`数的个数，因为每次都是从比当前位小的数去统计，没有考虑`x`是否为`windy`数。

具体细节见代码。


### 代码

```c++
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 15;
const ll mod = 1e9+7;
const ll INF = 1e18;
const double eps = 1e-6;

int digit[maxn];
ll dp[maxn][maxn];

void init()
{
    mst(dp,0);
    for(int i=0;i<=9;i++) dp[1][i]=1;
    for(int i=2;i<=10;i++)
    for(int j=0;j<=9;j++)
    for(int k=0;k<=9;k++)
    {
        if(abs(j-k)>=2) dp[i][j]+=dp[i-1][k];
    }
}

ll solve(ll x)
{
    ll ans=0;
    if(x==0) return 0;
    mst(digit,0);
    int len=0;
    while(x)
    {
        digit[++len]=x%10;
        x/=10;
    }
    for(int i=1;i<=digit[len]-1;i++) ans+=dp[len][i]; //长度相等，最高位小于
    for(int i=1;i<=len-1;i++)   //长度小于
    for(int j=1;j<=9;j++)
    {
        ans+=dp[i][j];
    }
    for(int i=len-1;i>0;i--)    //前面固定后，枚举每一位
    {
        for(int j=0;j<=digit[i]-1;j++)
        {
            if(abs(digit[i+1]-j)>=2) ans+=dp[i][j];
        }
        if(abs(digit[i+1]-digit[i])<2) break;
    }
    return ans;
}

int main()
{
    ll a,b;
    scanf("%lld%lld",&a,&b);
    init();
    printf("%lld\n",solve(b+1)-solve(a));
}
```

## 题目四：count 数字计数

[BZOJ 1833](https://www.lydsy.com/JudgeOnline/problem.php?id=1833)

### 题意

RT

### 思路

用`dp[i][j][k]`表示长度为`i`，最高位为`j`的所有数中数码`k`出现的次数。
为了预处理出`dp`数组，我们现需要找到转移方程

1. f[i][j][k]=∑f[i-1][l][k]              (j!=k)
2. f[i][j][k]=∑f[i-1][l][k]+10i-1        (j!=k)

第一种情况就是直接在前面加一个非`k`的数，结果跟长度为`i-1`时相同

第二种情况就是在前面加一个`k`，因为后面`i-1`位共有`2^(i-1)`个数，那么就相当于多了`2^(i-1)个k`

然后就是对读入的数分别求出每个数码有几个，相减即可。


### 代码

```c++
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 15;
const ll mod = 1e9+7;
const ll INF = 1e18;
const double eps = 1e-6;

ll fac[15];
ll dp[15][10][10];
int digit[15];
ll ans1[10],ans2[10];

void init()
{
    mst(dp,0);
    fac[0]=1;
    for(int i=1;i<=14;i++) fac[i]=fac[i-1]*10;
    for(int i=0;i<=9;i++) dp[1][i][i]=1;
    for(int i=2;i<=13;i++)
    for(int j=0;j<=9;j++)
    {
        for(int l=0;l<=9;l++)
        {
            for(int k=0;k<=9;k++)
            {
                dp[i][j][k]+=dp[i-1][l][k];
            }
        }
        dp[i][j][j]+=fac[i-1];
    }
}

void solve(ll x,ll *num)
{
    mst(digit,0);
    if(x==0) return;
    int len=0;
    ll tmp=x;
    while(tmp)
    {
        digit[++len]=tmp%10;
        tmp/=10;
    }
    for(int i=1;i<len;i++)  //长度小于len的所有情况
    for(int j=1;j<=9;j++)
    for(int k=0;k<=9;k++)
    {
        num[k]+=dp[i][j][k];
    }
    for(int i=1;i<=digit[len]-1;i++)  //长度等于len且最高位不超过digit[len]的所有情况
    for(int k=0;k<=9;k++)
    {
        num[k]+=dp[len][i][k];
    }
    x%=fac[len-1];
    num[digit[len]]+=x+1;            //例如x=4532,把x变为532，统计532，数码4的个数加上532+1(4000~4532)
    for(int i=len-1;i>0;i--)         //以此类推
    {
        for(int j=0;j<digit[i];j++)
        for(int k=0;k<=9;k++)
        {
            num[k]+=dp[i][j][k];
        }
        x%=fac[i-1];
        num[digit[i]]+=(x+1);
    }
}

int main()
{
    init();
    ll x,y;
    scanf("%lld%lld",&x,&y);
    solve(y,ans1);
    solve(x-1,ans2);
    for(int i=0;i<=8;i++) printf("%lld ",ans1[i]-ans2[i]);
    printf("%lld\n",ans1[9]-ans2[9]);
}
```

## 题目五：储能表

[BZOJ 4513](https://www.lydsy.com/JudgeOnline/problem.php?id=4513)

### 题意

RT

### 思路

由于是异或且数据范围较大，于是可以考虑二进制分解，根据题意，我们只要算出`i^j>k`的个数和异或和就能得到解，考虑从高位到低位进行数位`DP`。

我们用`num[pos][a][b][c]`表示`i`和`j`从高到低确定到`pos`位,`i`和`n`的当前位`nown`的关系为`a`,`j`和`m`的当前位`nowm`的关系为`b`，`i^j`与`k`的当前位`nowk`的关系为`c`满足条件的方案数。

对应的,`sum[pos][a][b][c]`表示总的异或和。

其中当`a，b`等于`0`时，表示小于`n,m`当前位，而等于`1`时表示等于当前位

当`c`等于0时，表示大于`k`当前位，等于`1`时表示等于当前位。

然后就由`num[i+1]`转移到`num[i]`

由`num[i+1]`和`sum[i+1]`转移到`sum[i]`即可

最后答案为`sum[0][0][0][0]`-`num[0][0][0][0]*k`

### 代码

```c++
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 1005;
const ll mod = 1e9+7;
const ll INF = 1e18;
const double eps = 1e-6;

ll n,m,k,Mod;
ll num[65][2][2][2];
ll sum[65][2][2][2];
ll fac[maxn];

void init()
{
    fac[0]=1;
    fac[1]=2;
    for(int i=2;i<=62;i++)
    {
        fac[i]=fac[i-1]*2%Mod;
    }
}

int main()
{
    rush()
    {
        scanf("%lld%lld%lld%lld",&n,&m,&k,&Mod);
        init();
        mst(num,0);
        mst(sum,0);
        num[61][1][1][1]=1;
        for(int i=60;i>=0;i--)
        for(int a=0;a<2;a++) //0:小于 1：等于
        for(int b=0;b<2;b++)
        for(int c=0;c<2;c++) //0：大于 1：等于
        {
            if(num[i+1][a][b][c])
            {
                int nown=(n>>i)&1;
                int nowm=(m>>i)&1;
                int nowk=(k>>i)&1;
                for(int x=0;x<=(a?nown:1);x++)
                for(int y=0;y<=(b?nowm:1);y++)
                {
                    int kk=x^y;
                    if(c&&kk<nowk) continue;
                    num[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]+=num[i+1][a][b][c];
                    num[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]%=Mod;
                    sum[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]+=sum[i+1][a][b][c];
                    sum[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]%=Mod;
                    if(kk)
                    {
                        sum[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]+=fac[i]*num[i+1][a][b][c]%Mod;  //当前位的贡献
                        sum[i][a&&x==nown][b&&y==nowm][c&&kk==nowk]%=Mod;
                    }
                }
            }
        }
        k%=Mod;
        printf("%lld\n",(sum[0][0][0][0]-k*num[0][0][0][0]%Mod+Mod)%Mod);
    }
}
```
