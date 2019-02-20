# 字符串初阶


对于初阶字符串问题而言，我们最常用的莫过于KMP问题，因此本章会整理一些有关于KMP的题型，并且总结其中的规律与问题


## KMP字符串匹配

[洛谷P3375](https://www.luogu.org/problemnew/show/P3375)

### 题目大意

给定两个字符串s1 和 s2 ，其中 s2 为s1的子串，求出s2 在s1中所有出现的位置，并输出子串的前缀数组next

### 题目分析

这道题就是KMP的一个经典的模板题型，通过kmp算法先求出next数组，然后对模式串和目标串进行匹配。最后确定出现位置即可

### 代码

https://paste.ubuntu.com/p/DTg99Hk8Ry/

```c++
#include<iostream>
#include<cstring>
#define MAXN 1000010
using namespace std;
int kmp[MAXN];
int la,lb,j; 
char a[MAXN],b[MAXN];
int main()
{
    cin>>a+1;
    cin>>b+1;
    la=strlen(a+1);
    lb=strlen(b+1);
    for (int i=2;i<=lb;i++)
       {     
       while(j&&b[i]!=b[j+1])
        j=kmp[j];    
       if(b[j+1]==b[i])j++;    
        kmp[i]=j;
       }
    j=0;
    for(int i=1;i<=la;i++)
       {
          while(j>0&&b[j+1]!=a[i])
           j=kmp[j];
          if (b[j+1]==a[i]) 
           j++;
          if (j==lb) {cout<<i-lb+1<<endl;j=kmp[j];}
       }

    for (int i=1;i<=lb;i++)
    cout<<kmp[i]<<" ";
    return 0;
}
```

## 无线传输

[洛谷 P4391](https://www.luogu.org/problemnew/show/P4391)

### 题目大意

给定一个字符串，求该字符串的最小循环节

### 题目分析

这个题目就是next 数组的一个应用了。我们知道一个结论 n - next [ n ] = t，t 就是循环节了的长度了

### 代码

https://paste.ubuntu.com/p/PnBtq6wjTQ/

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN=1024*1024;
int n,next[MAXN];
char str[MAXN];
int main(){
    scanf("%d%s",&n,str+1);
    for(int i=2,j=0;i<=n;i++){
        while(j&&str[j+1]!=str[i]){
            j=next[j];
        }
        if(str[j+1]==str[i]){
            j++;
        }
        next[i]=j;
    }
    printf("%d",n-next[n]);
    return 0;
}
```

## uva 1328

[uva 1328](https://www.luogu.org/problemnew/show/UVA1328)

### 题目大意

给定一个字符串，求该字符串的最小循环节 

### 题目分析

这个题和上面那个题是同一种题目，主要考点还是在next数组的应用上面

### 代码

https://paste.ubuntu.com/p/67qP8Njmv4/

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <cstring>
#include <map>
using namespace std;

#define maxn 1000000

int n;
char a[maxn+5];
int nxt[maxn+5]={0};

int main() {

    int T=0;
    while(~scanf("%d",&n)&&n!=0){
        printf("Test case #%d\n",++T);
        scanf("%s",a);
        nxt[0]=-1;
        for(int i=0;i<n;i++){
            int j=nxt[i];
            while(j>=0&&a[j]!=a[i]){
                j=nxt[j];
            }
            nxt[i+1]=++j;
        }
        for(int i=1;i<=n;i++){ 
            if(nxt[i]&&i%(i-nxt[i])==0){
                printf("%d %d\n",i,i/(i-nxt[i]));
            }
        }
        printf("\n");
    }

    return 0;
}
```

##  [POI2006]OKR-Periods of Words

[洛谷P3435](https://www.luogu.org/problemnew/show/P3435)

### 题目大意

给定一个字符串，对于每一个前缀，求它的最长前缀，使其重复后能够覆盖原串

### 题目分析

这道题目也是基于next数组的一个分析的过程，我们要使某个前缀重复以后能够覆盖整个串，我们只要求出当前子串的前缀=后缀的最短的匹配长度，那么剩余长度就是我们要求的最长前缀。
那么怎么求最短的匹配长度呢？

`next[i]` 表示当前匹配的最长前缀和后缀相等
我们只需要继续求 `next[next[i]]` 的话，也就是依然满足前缀=后缀的情况。只要一直求，求到`0`为止，就可以得出最短的匹配长度了

### 代码

https://paste.ubuntu.com/p/6VsRgDj2QQ/

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
char a[1000010];int n,fail[1000010];
int main(){
    scanf("%d",&n);scanf("%s",a);int i,j;ll cnt=0;
    fail[0]=fail[1]=0;j=0;
    for(i=1;i<n;i++){
        while(j&&(a[i]!=a[j])) j=fail[j];
        j+=(a[i]==a[j]);fail[i+1]=j;
    }
    for(i=1;i<=n;i++){
        j=i;
        while(fail[j]) j=fail[j];
        if(fail[i]!=0) fail[i]=j;
        cnt+=i-j;
    }
    printf("%lld",cnt);
}
```

## [NOI2014]动物园

[洛谷 P2375](https://www.luogu.org/problemnew/show/P2375)

### 题目大意

这道题目要求前缀与后缀相等但不重叠的长度，记做num[i]，求 （num[i]+1)的乘积

### 题目分析

这个题类似我们刚才求最短长度的做法，我们不断的求 `next[i]`，只要满足 `2*next[i]<n` 的话，这就是我们要求的长度了，然而这样做的话，复杂度会比较高 `O(n*L*log(L))` 会TLE
所以，我们要直接写出递推解，这里考虑KMP的做法，我们在计算再跑一次next数组的求法，就可以解决这个问题了

代码：https://paste.ubuntu.com/p/bZqRSkwHtY/

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm> 

using namespace std;
#define mod 1000000007
#define N 1000005
int dp[N],t,next[N],n,num[N];
char s[N];
inline void KMP(long long ans=1)
{
    n=strlen(s);
    next[0]=-1;
    int j;
    for (int i=0;i<n;i++)
    {
        j=next[i];
        while (j!=-1&&s[i]!=s[j])
        j=next[j];
        next[i+1]=++j;
        num[i+1]=num[j]+1;
    }
    j=0;
    for (int i=1;i<n;i++)
    {
        while (j!=-1&&s[j]!=s[i]) 
          j=next[j];
        j++;
        while((j<<1)>i+1) j=next[j];
        ans*=num[j]+1;ans%=mod;
    }
    cout<<ans<<endl;
} 
int main(){
    for(scanf("%d",&t);t--;) scanf("%s",s),num[0]=0,KMP();
    return 0;
}
```

##  password

[codeforces 126B](http://codeforces.com/contest/126/problem/B)

### 题目大意

给定一个字符串，找出其中一个最长的子串，使得这个子串既是前缀又是后缀又在中间出现

### 题目分析

我们看到前后缀很自然的可以想到Kmp中的next数组，那么如何处理是否在中间呢？我一开始构建了一个s除去头尾的子串，试图在其中用find函数去查找是否存在这样的串，很显然这样的复杂度是很高的，会T，我们可以发现，我们在求next的数组的时候，就是求最长前缀后多少个，因此，我们只要记录除了最后一个字符意外的前面的最长前缀的情况，也就是除去后缀之后，前缀和中间出现的又构成的一个前后缀，我们只要找到满足这样条件的子串即可。

### 代码

https://paste.ubuntu.com/p/RHJfnF8z4Q/

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+50;
const int inf=0x3f3f3f3f;
const int mod =1e9+7;
int next[maxn];
int _hash[maxn];
void getnext(string s)
{
    int len=s.size();
    int i=0,j=-1;
    next[0]=-1;
    while(i<len)
    {
        if(j==-1||s[i]==s[j])
        {
            next[++i]=++j;
        }
        else j=next[j];
    }
    for(int i=1;i<len;i++)
    {
        _hash[next[i]]++;
    }
}
int main()
{
    string a;
    cin>>a;
    getnext(a);
    int len = a.size();
    int k=next[len];

    while(k)
    {
        if(_hash[k])
        {
            for(int i=0;i<k;i++)
            {
                cout<<a[i];
            }
            return 0;
        }
        k=next[k];
    }
    printf("Just a legend\n");
    return 0;
}
```