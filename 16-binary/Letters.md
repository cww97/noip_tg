# Letters


## 题目描述

柏林大学有 `n` 幢公寓楼，依次用`1 ~ n`编号，每幢公寓楼由一系列房间组成，假设第i幢公寓楼有`a[i]`个房间，房间号分别为`1 ~ a[i]`。

有一个快递员要送信到一个房间，但是信封上却没有写明需要送到第几幢第几个房间，只有这个房间在所有房间中的编号（从第一幢楼第一个房间依次编号）。

现在有`m`个信封，每个信封上只有需要送到的房间在所有房间中的编号。问这个房间位于第几幢公寓楼的第几个房间。

举个例子，如果`n=2, a[1]=3, a[2]=5`,信封上的编号可以是`1~8`,如果写着`7`,那么就代表需要送到第`2`幢公寓楼的第`4`个房间。

## 输入格式

第一行两个整数`n`，`m`，表示公寓楼数量和信封数量。

第二行`n`个整数 `a[i]`, 表示第 `i` 幢公寓楼的房间数量。

第三行`m`个整数`b[j]`,表示第 `j` 个信封上的编号。保证给出的`b[j]`是递增的。


## 输出格式

对于每个信封的数字输出一行，每行两个数字`f`,`k`，用空格隔开，表示需要送到第`f`幢公寓楼的第`k`个房间。

## 输入样例

    3 6
    10 15 12
    1 9 12 23 26 37

## 输出样例

    1 1
    1 9
    2 2
    2 13
    3 1
    3 12
    
## 数据范围
- $1 \le n, m \le 2*10^5$
- $1 \le a_i \le 10^{10}$
- $1 \le b_j \le a_1 + a_2 + ... + a_n$

**【测试网站】**

[codeforces](https://codeforces.com/contest/978/problem/C)

## 题目分析
   
   首先，最简单的方法就是记录房间总数的前缀和，对于查询的编号依次遍历每幢公寓楼的前缀和，第一个大于等于编号的位置x就说明了在第x幢。然后作一下差就能同时得到房间号。
   
```c++
#include <cstdio>
#include <bits/stdc++.h>
#include <cmath>
#include <map>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef  long long ll;
const int maxn = 200005;
const ll mod = 1e9+7;
const int INF = 1e9;
const double eps = 1e-6;

int n,m;
ll a[maxn];
ll sum[maxn];
char s[maxn];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }

    for(int i=0;i<m;i++){
        ll x;
        scanf("%lld",&x);
        int pos=-1;
        for(int j=1;j<=n;j++){
            if(sum[j]>=x){
                pos=j;
                break;
            }
        }
        //int pos=lower_bound(sum+1,sum+1+n,x)-sum;
        ll res=x-sum[pos-1];
        printf("%d %lld\n",pos,res);
    }
}
```
   
冷静分析一下，其复杂度为O(nm)，显然会超时。

于是我们想到可以用二分找这个位置x,这里我们既可以用手写二分，也可以用lower_bound()函数，这样能把时间复杂度降到`O(mlogn)`.
   

## 代码示例1

```c++
#include <cstdio>
#include <bits/stdc++.h>
#include <cmath>
#include <map>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef  long long ll;
const int maxn = 200005;
const ll mod = 1e9+7;
const int INF = 1e9;
const double eps = 1e-6;

int n,m;
ll a[maxn];
ll sum[maxn];
char s[maxn];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=0;i<m;i++)
    {
        ll x;
        scanf("%lld",&x);
        int pos=lower_bound(sum+1,sum+1+n,x)-sum;
        ll res=x-sum[pos-1];
        printf("%d %lld\n",pos,res);
    }
}
```

## 代码示例2

```c++
#include <cstdio>
#include <bits/stdc++.h>
#include <cmath>
#include <map>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef  long long ll;
const int maxn = 200005;
const ll mod = 1e9+7;
const int INF = 1e9;
const double eps = 1e-6;

int n,m;
ll a[maxn];
ll sum[maxn];
char s[maxn];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=0;i<m;i++)
    {
        ll x;
        scanf("%lld",&x);
        int pos=-1;
        int l=1,r=n;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(sum[mid]>=x)
            {
                pos=mid;
                r=mid-1;
            }
            else l=mid+1;
        }
        ll res=x-sum[pos-1];
        printf("%d %lld\n",pos,res);
    }
}

```
   
   
   
