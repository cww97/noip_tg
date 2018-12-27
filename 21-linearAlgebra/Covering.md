# Covering


## 题目描述

用 `1*2` 的小长方形完全覆盖`4*n`的矩形有多少方案。

## 输入格式

输入数据有多组

每组一个整数`n`


## 输出格式

对于每组数据输出方案数,答案对`1e9+7`取膜。

## 输入样例

    1
    2

## 输出样例

    1
    5
 
    
## 数据范围

- `1 ≤ n ≤ 10^18`

**【测试网站】**

[HDOJ 6185](http://acm.hdu.edu.cn/showproblem.php?pid=6185) 

## 题目分析

  这道题显然可以想到用状态压缩DP去做，详细做法可以参考一篇博客：[传送门](https://blog.csdn.net/my_sunshine26/article/details/74612684)
  
  但是可以观察到此题的数据范围很大，达到了`1e18`，我们自然而然的想到应该要找规律，可能要用到矩阵快速幂云云...
  
  于是用状压DP的代码来打表，果然结果是有规律的。规律为：
  
    dp[i]=dp[i-1]+5*dp[i-2]+dp[i-3]-dp[i-4] （i>=5）
 
 这样我们就可以构造出矩阵的转移方程。
  
    | 1 5 1 -1|        | F[n-1] |       |  F[n]  |
    | 1 0 0 0 |    *   | F[n-2] |   =   | F[n-1] |
    | 0 1 0 0 |        | F[n-3] |       | F[n-2] |
    | 0 0 1 0 |        | F[n-4] |       | F[n-3] |

  然后套用矩阵快速幂的模板即可。

## 代码示例

```c++
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T,scanf("%d",&T),while(T--)

typedef long long ll;
const int maxn = 4;
const ll mod = 1000000007;
const int INF = 0x3f3f3f3f;

struct Matrix
{
    ll temp[maxn][maxn];
} a;

void init()
{
    for(int i=0;i<maxn;i++)
    for(int j=0;j<maxn;j++)
    {
        a.temp[i][j]=0;
    }
    a.temp[0][0]=a.temp[0][2]=1;
    a.temp[0][1]=5;
    a.temp[0][3]=-1;
    a.temp[1][0]=a.temp[2][1]=a.temp[3][2]=1;
}
Matrix mul(Matrix a,Matrix b)
{
    Matrix ans;
    for (int i=0; i<maxn; i++)
        for (int j=0; j<maxn; j++)
        {
            ans.temp[i][j]=0;
            for (int k=0; k<maxn; k++)
            {
                ans.temp[i][j]+=(a.temp[i][k]*b.temp[k][j]+mod)%mod;  //特别注意
                ans.temp[i][j]%=mod;
            }
        }
    return ans;
}

void fun(Matrix ans,ll k)
{
    for(int i=0; i<maxn; i++)
        for(int j=0; j<maxn; j++)
            a.temp[i][j]=(i==j);
    while(k)
    {
        if(k%2)
            a=mul(a,ans);
        ans=mul(ans,ans);
        k/=2;
    }
}

int main()
{
    Matrix t;
    ll n;
    for(int i=0;i<maxn;i++)
    for(int j=0;j<maxn;j++)
    {
        t.temp[i][j]=0;
    }
    t.temp[0][0]=36;
    t.temp[1][0]=11;
    t.temp[2][0]=5;
    t.temp[3][0]=1;
    while(~scanf("%I64d",&n))
    {
        init();
        if(n<=4)
        {
            printf("%I64d\n",t.temp[4-n][0]);
            continue;
        }
        fun(a,n-4);
        a=mul(a,t);
        ll ans=a.temp[0][0]%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
```
   
   
   
