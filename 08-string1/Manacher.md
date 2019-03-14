# Manacher（马拉车）

> 首先来一份模板

```c++
//string1 = "aa" -> "$#a#a#"
//string2 = "aba" -> "$#a#b#a#"
char s[N];
char ss[2*N];
int p[2*N];
void manacher(char s[],int len){
    ss[0]='$';
    for(int i=1;i<=2*len+1;i+=2)ss[i]='#';
    for(int i=0;i<len;i++)ss[2*i+2]=s[i];
    int Len=2*len+1;
    int mx=0,id=0;
    int MaxLen=0;
    for(int i=0;i<Len;i++){
        p[i]=i>mx?1:min(mx-i,p[2*id-i]);
        while(ss[i+p[i]]==ss[i-p[i]])p[i]++;
        MaxLen=max(MaxLen,p[i]-1);//回文长度==p[i]-1
        if(i+p[i]>mx)mx=i+p[i],id=i;
    }
}
```

## Non Super Boring Substring

[Codeforces Gym-101864J](<https://cn.vjudge.net/problem/Gym-101864J>)

### 题意

给出一个回文串，问有多少个**子串中不包含长度至少k的回文串**的子串

### 思路

首先当然是直接套马拉车板子，得出回文串长度

如果我们可以快速处理出以i点作为右端点的串有多少个包含k长回文串，题目就做出来了

### 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define debug(i) printf("# %d\n",i)
typedef long long LL;
const int N=1e5+5;
char s[N];
char ss[2*N];
int p[2*N];
void manacher(char s[],int len){
    ss[0]='$';for(int i=1;i<=2*len+1;i+=2)ss[i]='#';
    for(int i=0;i<len;i++)ss[2*i+2]=s[i];
    int Len=2*len+1;
    int mx=0,id=0;int MaxLen=0;
    for(int i=0;i<Len;i++){
        p[i]=i>mx?1:min(mx-i,p[2*id-i]);
        while(ss[i+p[i]]==ss[i-p[i]])p[i]++;
        MaxLen=max(MaxLen,p[i]-1);
        if(i+p[i]>mx)mx=i+p[i],id=i;
    }
}

int tr[N];
void add(int pos,int v,int n){
    while(pos<=n)tr[pos]=max(tr[pos],v),pos+=(pos&(-pos));
}
int query(int pos){
    int re=0;
    while(pos>=1)re=max(tr[pos],re),pos-=(pos&(-pos));return re;
}

int main(){
    int t;scanf("%d",&t);
    while(t--){
        memset(tr,0,sizeof(tr));
        int k;scanf("%d",&k);
        scanf("%s",s);
        int len=strlen(s);
        int Len=2*len+1;
        manacher(s,len);

        for(int i=2;i<Len;i++){
            if(p[i]-1<k)continue;
            int st,en,tmp=k;           
            if(tmp%2!=(p[i]-1)%2)tmp++; 
            if(i%2==0){           
                en=i/2+tmp/2,st=i/2-tmp/2;
            }
            else{              
                en=(i-1)/2+tmp/2,st=(i+1)/2-tmp/2;
            }
            add(en,st,len);
        }
        LL ans=0;
        for(int i=1;i<=len;i++)ans+=(LL)(i-query(i));
        printf("%lld\n",ans);
    }
}
```

## 吉哥系列故事——完美队形II

[HDU-4513](<http://acm.hdu.edu.cn/showproblem.php?pid=4513>)

### 题意

求一个最长回文串，回文串的前一半满足非严格单调递增，后一半满足非严格单调递减

### 思路

模板魔改题目，改一改马拉车模板，怼上

### 代码

```C++
#include <iostream>
#include <cstdio>
#include<cstring>
#include <algorithm>
using namespace std;
const int maxn=100005;
int str[maxn];
int tmp[maxn<<1];
int Len[maxn<<1];

int N;
int INIT(int *st){
    int i,len=N;
    tmp[0]=-2;
    tmp[1]=-1;
    for(i=0;i<len;i++)
    {
        tmp[(i+1)<<1]=str[i];
        tmp[((i+1)<<1)+1]=-1;
    }
    tmp[2*len+1]=-1;
    tmp[2*len+2]=-3;
    tmp[2*len+3]=0;
    return 2*len+1;
}

int MANACHER(int *st,int len){
    memset(Len,0,sizeof Len);
    int ans=0,pos=0;
    for(int i=1;i<=len;i++){
        bool label=true;
        if(Len[pos]+pos>i)
            Len[i]=min(Len[2*pos-i],Len[pos]+pos-i);
        else
        Len[i]=1;
        while(st[i-Len[i]]==st[i+Len[i]]&&label){
            if(st[i-Len[i]]<0)
            Len[i]++;
            else if(st[i-Len[i]]<=st[i+Len[i]-2])
            	Len[i]++;
            else
            	label=false;
        }
        if(Len[i]+i>pos+Len[pos])
            pos=i;
        ans=max(ans,Len[i]);
    }
    return ans-1;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i=0;i<N;i++)
            scanf("%d",&str[i]);
        int tnum=INIT(str);
        printf("%d\n",MANACHER(tmp,tnum));
    }
    return 0;
}
```

## 

[BZOJ-3790](#)

> 原题失踪，给出描述
>
> ```
> Description 
> 母亲节就要到了，小 H 准备送给她一个特殊的项链。这个项链可以看作一个用小写字 
> 母组成的字符串，每个小写字母表示一种颜色。为了制作这个项链，小 H 购买了两个机器。第一个机器可以生成所有形式的回文串，第二个机器可以把两个回文串连接起来，而且第二个机器还有一个特殊的性质：假如一个字符串的后缀和一个字符串的前缀是完全相同的，那么可以将这个重复部分重叠。例如：aba和aca连接起来，可以生成串abaaca或 abaca。现在给出目标项链的样式，询问你需要使用第二个机器多少次才能生成这个特殊的项链。 
> 
> Input 
> 输入数据有多行，每行一个字符串，表示目标项链的样式。 
> 
> Output 
> 多行，每行一个答案表示最少需要使用第二个机器的次数。 
> 
> Sample Input 
> abcdcba 
> abacada 
> abcdef 
> 
> Sample Output 
> 0 
> 2 
> 5 
> 
> 
> HINT 
> 每个测试数据，输入不超过 5行 
> 每行的字符串长度小于等于 50000
> ```

### 题意

给出操作，链接回文串生成特殊字符串，输出次数

### 思路

马拉车初始化，问题转化为区间覆盖问题

### 代码

```C++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=50000+5;

int len,pal[N*2];
char s[N],a[N*2];
struct Node{
    int le,ri;
}qu[N*2];

bool cmp(Node a,Node b){
    return a.le<b.le;
}
void insert(){
    memset(a,0,sizeof(a));
    int lena=-1;
    a[++lena]='+';
    for(int i=0;i<len;i++){
        a[++lena]='#';
        a[++lena]=s[i];
    }
    a[++lena]='#';
    a[++lena]='-';
    len=lena-1;
}
void manacher(){
    int mx=0,id;
    for(int i=1;i<=len;i++){
        if(mx>=i) pal[i]=min(mx-i+1,pal[2*id-i]);
        else pal[i]=1;
        while(a[i-pal[i]]==a[i+pal[i]]) ++pal[i];
        if(mx<i+pal[i]-1)
            mx=i+pal[i]-1,id=i;
    }
}
int fugai(){
    int ans=0,far=1;
    int i=1;
    for(i=1;qu[i].le<=1;i++)
        if(qu[i].ri>qu[far].ri) far=i;
    while(i<=len){
        ans++;
        int tmp=far;
        for(;qu[i].le<=qu[far].ri;i++)
            if(qu[i].ri>qu[tmp].ri) tmp=i; 
        far=tmp;
    }
    return ans;
}
int main(){
    while(scanf("%s",s)!=EOF){
        len=strlen(s);
        insert();
        manacher();
        memset(qu,0,sizeof(qu));
        for(int i=1;i<=len;i++)
            qu[i].le=i-pal[i]+1,qu[i].ri=i+pal[i]-1；
        sort(qu+1,qu+len+1,cmp);
        printf("%d\n",fugai()-1);
    }
    return 0;
}
```

## Palindrome

[POJ-1159]()

### 题意

给定一个字符串L，为了保证L是回文序列需要最少添加几个字符；

### 思路

做法是得到L的逆序列S，求L和S的最长公共子序列，用到动态规划的知识，如果运用$maxlen[i][j]=max(maxlen[i-1][j], maxlen[i][j-1])$会爆内存，所以用滚动数组来实现，因为当我们用完maxlen[i][j]后就用一次，所以可以把5000\*5000的数组缩小到2 \* 5000

### 代码

```C++
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
char L[5050], S[5050];
int maxl[2][5050];
int main(){
  int n,i,j;
  while(cin>>n){
      for(i=1; i<=n; i++)
        cin>>L[i];
      L[n+1]='\0';
      for(i=1; i<=n; i++)
        S[i]=L[n-i+1];
      memset(maxl,0,sizeof(maxl));
      int e=0;
      for(i=1; i<=n; i++){
          e=1-e;
          for(j=0; j<=n; j++){
              if(L[i]==S[j])
                maxl[e][j]=maxl[1-e][j-1]+1;
              else
                maxl[e][j]=maxl[e][j-1]>maxl[1-e][j]?maxl[e][j-1]:maxl[1-e][j];
            }
        }
      cout<<n-maxl[e][n]<<endl;
    }
  return 0;
}
```

