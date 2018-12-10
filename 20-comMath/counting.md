# Counting Arrays


## 题目描述

给出两个数`x`、`y`，问有多少种不同的数列`F[1]`,`F[2]`,`F[3]`……`F[y]`，使得它们的乘积为`x`，答案模`1e9+7`。

## 输入格式

第一行一个整数`q`，表示询问的个数
接下来`q`行，每行两个整数`x`,`y`。


## 输出格式

对于每组询问输出答案。

## 输入样例

    2
    6 3
    4 2

## 输出样例

    36
    6
 
## 样例解释

对于第二组询问，共有下面`6`种不同的数列，`{-1,-4}`,`{-4,-1}`,`{-2,-2}`,`{2,2}`,`{1,4}`,`{4,1}`
    
## 数据范围
- `1 ≤ q ≤ 10^5`
- `1 ≤ x, y ≤ 10^6`

**【测试网站】**

[codeforces](https://codeforces.com/contest/893/problem/E) 

## 题目分析
   
  我们首先对x分解质因数，分解成`p[1]^c[1]` + `p[2]^c[2]`……的形式。
  
  然后先不考虑符号，把排列中的数`F[i]`都置为`1`，然后依次处理每个底数，假设它的指数为`C`，那么这里贡献的次数便是将`C`个底数分配到`y`个位置的情况数目。
  
  转化一下，便是放球问题中的球相同，盒子不同，允许空盒的方案数，具体可以看这份博客：[传送门](https://blog.csdn.net/my_sunshine26/article/details/77385809)， 然后每个底数的贡献相乘。
  
  最后再考虑符号，我们很容易发现，其实对于`y`个数的情况，前`y-1`个数的符号可以任意取定，只要利用最后一个数的符号使得乘积为正即可。
  
## 代码示例

```c++
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 2000005;
const ll mod = 1e9+7;
const ll INF = 1e15;
const double eps = 1e-9;

ll fac[maxn];
ll inv[maxn];

ll fast_mod(ll a,ll n,ll Mod)
{
    ll ans=1;
    a%=Mod;
    while(n)
    {
        if(n&1) ans=(ans*a)%Mod;
        a=(a*a)%Mod;
        n>>=1;
    }
    return ans;
}

void init()
{
    fac[0]=1;
    for(int i=1;i<maxn;i++)
    {
        fac[i]=(fac[i-1]*i)%mod;
    }
    inv[maxn-1]=fast_mod(fac[maxn-1],mod-2,mod);
    for(int i=maxn-2;i>=0;i--)
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
    rush()
    {
        int x,y;
        scanf("%d%d",&x,&y);
        vector<int>vec;
        for(int i=2;i*i<=x;i++)     //分解质因数
        {
            if(x%i==0)
            {
                int cnt=0;
                while(x%i==0)
                {
                    cnt++;
                    x/=i;
                }
                vec.push_back(cnt);
            }
        }
        if(x>1) vec.push_back(1);
        ll ans=1;
        y--;
        for(int i=0;i<vec.size();i++)
        {
            ans*=C(vec[i]+y,y);                 //模拟放球
            ans%=mod;
        }
        ans=(ans*fast_mod(2,y,mod))%mod;        //处理符号
        printf("%I64d\n",ans);
    }
}

```
   
   
   
