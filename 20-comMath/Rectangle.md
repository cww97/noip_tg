# Rectangle


## 题目描述

给出一个`n*m`的棋盘，每一个格子的颜色是白色的或者是黑色的，问有多少不同的非空集合满足集合中所有格子的颜色是相同的且任意两个格子处在同一行或者同一列。

## 输入格式

第一行两个整数`n`,`m`，表示棋盘大小。

接下来`n`行，每行`m`个整数，用空格隔开，表示棋盘中每个格子的颜色，`0`表示白色，`1`表示黑色。


## 输出格式

输出集合的个数

## 输入样例

    2 3
    1 0 1
    0 1 0

## 输出样例

    8
 
    
## 数据范围
- `1 ≤ n, m ≤ 50`

**【测试网站】**

[codeforces](https://codeforces.com/contest/844/problem/B) 

## 题目分析
   
  首先我们算出集合元素个数为`1`的个数，显然，这部分的答案为`n*m`。
  
  又由题意，要满足两个条件，我们只能在同一行或者同一列颜色相同的格子种选出几个，这显然是组合数的运用。
  
  考虑到数据范围较小，我们先预处理组合数，然后暴力模拟即可。
  
## 代码示例

```c++
#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 55;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n,m;
int mp[maxn][maxn];
ll c[maxn][maxn];


void init()             //预处理组合数
{
    for(int i=0; i<maxn; i++)
        c[i][0]=c[i][i]=(ll)1;
    for(int i=2; i<maxn; i++)
    for(int j=1; j<i; j++)
        c[i][j]=(c[i-1][j-1]+c[i-1][j]);
}


int main()
{
    init();
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            scanf("%d",&mp[i][j]);
        }
        ll ans=(ll)n*m;
        for(int i=0;i<n;i++)
        {
            int cnt1=0;
            int cnt2=0;
            for(int j=0;j<m;j++)    //统计黑白棋子的总个数
            {
                if(mp[i][j]==0) cnt1++;
                else cnt2++;
            }
            if(cnt1>1)
            {
                for(int j=2;j<=cnt1;j++)
                {
                    ans+=c[cnt1][j];
                }
            }
            if(cnt2>1)
            {
                for(int j=2;j<=cnt2;j++)
                {
                    ans+=c[cnt2][j];
                }
            }
        }
        for(int i=0;i<m;i++)
        {
            int cnt1=0;
            int cnt2=0;
            for(int j=0;j<n;j++)
            {
                if(mp[j][i]==0) cnt1++;
                else cnt2++;
            }
            if(cnt1>1)
            {
                for(int j=2;j<=cnt1;j++)
                {
                    ans+=c[cnt1][j];
                }
            }
            if(cnt2>1)
            {
                for(int j=2;j<=cnt2;j++)
                {
                    ans+=c[cnt2][j];
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}


```
   
   
   
