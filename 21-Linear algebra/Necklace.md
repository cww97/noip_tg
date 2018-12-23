# Necklace


## 题目描述

一条长度为`n`的项链，由红色珠子和蓝色珠子（分别用`1`和`0`表示）组成

在连续的素数子段中，红色珠子的个数不能少于蓝色珠子

问组成这个项链有多少种方案，求方案数模`1000000007`

## 输入格式

第一行一个整数`T`，表示数据组数。

接下来`T`行，每行一个整数`n`，表示珠子总个数。


## 输出格式

对于每组数据输出方案数。

## 输入样例

    2 
    3
    4

## 输出样例

    3
    4
 
    
## 数据范围
- `1 ≤ T ≤ 10000`
- `2 ≤ T ≤ 10^18`

**【测试网站】**

[HDOJ 6030](http://acm.hdu.edu.cn/showproblem.php?pid=6030) 

## 题目分析

  对于这种数据范围很大的题目，我们可以想到可能会用到矩阵快速幂。
  
  其实只要推出前几组就可以找到规律。
  
  当`i<4`时，`a[i]=i+1`
  
  当`i>=4`时，`a[i]=a[i-2]+a[i-3]+a[i-4]`
  
  通过递推式构造转移矩阵：
  
     | 0 1 1 1 |     | F[n-1] |     |   F[n]   |
     | 1 0 0 0 |  *  | F[n-2] |  =  |   F[n-1] |
     | 0 1 0 0 |     | F[n-3] |     |   F[n-2] |
     | 0 0 1 0 |     | F[n-4] |     |   F[n-3] |


## 代码示例

```
#include <bits/stdc++.h>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define f(i,a,b) for(int i=(a);i<(b);++i)
#define ll long long
const int maxn = 4;
const int mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
#define rush() int T;scanf("%d",&T);while(T--)
struct Matrix
{
    ll temp[maxn][maxn];
} a;
void init()
{
    f(i,0,maxn)
    f(j,0,maxn)
    {
        a.temp[i][j]=0;
    }
    a.temp[0][1]=a.temp[0][2]=a.temp[0][3]=1;
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
                ans.temp[i][j]+=a.temp[i][k]*b.temp[k][j];
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
    f(i,0,maxn)
    f(j,0,maxn)
    {
        t.temp[i][j]=0;
    }
    t.temp[0][0]=4;
    t.temp[1][0]=3;
    t.temp[2][0]=2;
    t.temp[3][0]=1;
    rush()
    {
        init();
        scanf("%I64d",&n);
        if(n<4)
        {
            printf("%I64d\n",n+1);
            continue;
        }
        fun(a,n-3);
        a=mul(a,t);
        ll ans=a.temp[0][0]%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
```
   
   
   
