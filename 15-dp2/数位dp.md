# 图论建模

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

你有 k 次机会选择 一个`x`和`y (1≤x<y≤n) ，交换`ax`和`ay`。

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


## 题目一：The Best Path

[HDOJ 5883](http://acm.hdu.edu.cn/showproblem.php?pid=5883)

### 题意


### 思路



### 代码

```c++

```

## 题目一：The Best Path

[HDOJ 5883](http://acm.hdu.edu.cn/showproblem.php?pid=5883)

### 题意


### 思路



### 代码

```c++

```
