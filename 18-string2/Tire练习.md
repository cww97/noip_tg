# Tire 练习

## Babelfish

测试网站[POJ](http://poj.org/problem?id=2503) 

### 题目描述

你刚从滑铁卢搬到了一个大城市,这里的人们说的是一种难以理解的外语方言。 

幸运的是，你有一本词典来帮助你理解它们。

### 输入格式

输入由最多`100000`个字典条目组成，后面跟着一个空行，再后面跟着最多`100000`个单词的消息。 

每个字典条目都是一个包含英文单词的行，后跟一个空格和一个外语单词。 字典中同一个外语单词不会出现多次。

消息是外语中的一系列单词，每行一个单词。输入中的每个单词都是最多`10`个小写字母的序列。

### 输出格式

输出是将信息翻译成英文的结果。 

外文字词不在字典中应翻译为“eh”。

### 输入样例

    dog ogday
    cat atcay
    pig igpay
    froot ootfray
    loops oopslay

    atcay
    ittenkay
    oopslay

### 输出样例

    cat
    eh
    loops    



### 题目分析
   
  将字典中的单词插入到字典树中，在最后一个节点上加上其翻译单词。
  
  查找的时候只要找到了这个单词最后这个节点，且这个节点上的存储翻译单词的域不为空说明存在翻译，输出其翻译，如果域为空，则输出“eh”。

  
### 代码示例

```c++
//#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 100005;
const ll INF = 1e18;
const ll mod=1e9+7;
const double eps = 1e-9;

int sz;
char tmp[maxn],s[maxn],t[maxn];
int word[maxn*12];
char Mp[maxn][12];
int ch[maxn*12][28];
int key[maxn*12];

void init()
{
    sz=1;
    mst(ch[0],0),mst(word,0);
}

void Insert(char *s,int id)
{
    int len=strlen(s);
    int u=0;
    for(int i=0; i<len; i++)
    {
        int c=s[i]-'a';
        if(!ch[u][c])         //节点不存在
        {
            mst(ch[sz],0);
            ch[u][c]=sz++;    //节点数加1
        }
        u=ch[u][c];
        word[u]++;            //该节点下的单词数+1
    }
    key[u]=id;
}

void solve(char *s)
{
    int len=strlen(s);
    int u=0;
    int flag=0;
    for(int i=0; i<len; i++)
    {
        int c=s[i]-'a';
        u=ch[u][c];
        if(u==0)
        {
            flag=1;
            break;
        }
    }
    if(flag) puts("eh");
    else puts(Mp[key[u]]);
}

int main()
{
    init();
    int tot=0;
    while(gets(tmp))
    {
        if(strcmp(tmp,"")==0) break;
        int len=strlen(tmp);
        int now=0;
        int cnt=0;
        for(now=0;now<len;now++)
        {
            if(tmp[now]==' ') break;
            s[cnt++]=tmp[now];
        }
        s[cnt]='\0';
        cnt=0;
        for(now=now+1;now<len;now++)
        {
            t[cnt++]=tmp[now];
        }
        t[cnt]='\0';
        strcpy(Mp[tot],s);
        Insert(t,tot);
        tot++;
    }
    while(~scanf("%s",s))
    {
        solve(s);
    }
}
```

## Shortest Prefixes

测试网站[POJ](http://poj.org/problem?id=2001) 

### 题目描述

给你一些单词，让你求出他们最短的前缀，当然，这个前缀不能有歧义，例如给出单词 `carton`、`cart`、`car`

`carton`的前缀就不能是`cart`，因为`cart`的前缀是`cart`，同理`cart`的前缀也不能是`car`。 

要找到每个单词独一无二且是最短的前缀，`car`的前缀不能是，`c`,`ca`，因为他们在别的单词中也有出现。

如果找不到独一无二，那个这个单词本身就是他自己的前缀。 

### 输入格式

输入数据有`n`行。

每行一个字符串`S`。

### 输出格式

对于每个字符串输出一行，输出它本身和最短前缀，中间用空格隔开。

### 输入样例

    carbohydrate
    cart
    carburetor
    caramel
    caribou
    carbonic
    cartilage
    carbon
    carriage
    carton
    car
    carbonate

### 输出样例

    carbohydrate carboh
    cart cart
    carburetor carbu
    caramel cara
    caribou cari
    carbonic carboni
    cartilage carti
    carbon carbon
    carriage carr
    carton carto
    car car
    carbonate carbona
    
### 数据范围
- `2 ≤ n ≤ 1000`
- `1 ≤ |S| ≤ 20`


### 题目分析
   
  首先容易发现这个是一道字典树的题目，我们只要在建立字典树的时候标记一下经过某个节点的单词数目
  
  那么在查找的时候我们只要找到单词数目为1的节点就能找到最短前缀了
  
### 代码示例

```c++
//#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 1005;
const ll INF = 1e18;
const ll mod=1e9+7;
const double eps = 1e-9;

int sz;
char s[maxn][25];
int word[maxn*28];
int ch[maxn*28][28];

void init()
{
    sz=1;
    mst(ch[0],0),mst(word,0);
}

void Insert(char *s)
{
    int len=strlen(s);
    int u=0;
    for(int i=0; i<len; i++)
    {
        int c=s[i]-'a';
        if(!ch[u][c])         //节点不存在
        {
            mst(ch[sz],0);
            ch[u][c]=sz++;    //节点数加1
        }
        u=ch[u][c];
        word[u]++;            //该节点下的单词数+1
    }
}

void find_pre(char *s)
{
    printf("%s ",s);
    int len=strlen(s);
    int u=0;
    vector<char>vec;
    int flag=0;
    for(int i=0; i<len; i++)
    {
        int c=s[i]-'a';
        u=ch[u][c];
        vec.push_back(s[i]);
        if(word[u]==1)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        puts(s);
        return;
    }
    /*for(auto it :vec)
    {
        printf("%c",it);
    }*/
    for(int i=0;i<vec.size();i++) printf("%c",vec[i]);
    puts("");
}

int main()
{
    int cnt=0;
    init();
    while(~scanf("%s",s[cnt]))
    {
        Insert(s[cnt]);
        cnt++;
    }
    for(int i=0;i<cnt;i++)
    {
        find_pre(s[i]);
    }
}

```
   
## Xor-Longest-Path

测试网站[POJ](http://poj.org/problem?id=3764) 

### 题目描述

给出一棵树，求树中异或和最大的路径的异或值。 

### 输入格式

输入包含多个测试用例。 

每个测试用例的第一行包含一个整数`n`,表示树上节点的个数。

接下来`n-1`行每个包含三个整数`u`,`v`,`w`，这意味着在节点`u`和`v`之间存在权重为`w`的边。

### 输出格式

对于每个测试样例输出最大的异或值。

### 输入样例

    4
    0 1 3
    1 2 4
    1 3 6

### 输出样例

    7

### 样例解释

    0->1->2， 最大异或值为3^4=7

### 数据范围
- `1 ≤ n ≤ 10^5`
- `0 ≤ u,v < n`
- `0 ≤ w < 2^31`


### 题目分析
   
  首先把这题模型转换一下，对于任意一条路径的异或，表示为`f(u,v)`，则`f(u,v)=f(0,u)^f(0,v)`。
  
  其中`f(0,i)`是可以在`O(n)`的时间复杂度内处理出来，然后就是在一个数组内，找两个数异或值最大。
  
  直接用`01`字典树即可。
  
  对于一个询问，在字典树上找，尽量找跟其相反的路径。
  
  比如第`30`位是`0`就尽量找最开始是`1`的路径，实在找不到就只能将这一位妥协，就是一种贪心的思路。
  
  
### 代码示例

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 100005;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

int n;
int cnt,tot;
int tree[maxn*35][2];
int mark[maxn*35];
int head[maxn],vis[maxn];
int val[maxn];

void init()
{
    cnt=tot=0;
    mst(tree,0);
    mst(mark,0);
    mst(vis,0);
    mst(head,-1);
}

struct node
{
    int v,w,next;
}e[maxn*2];

void add(int u,int v,int w)
{
    e[tot].v=v;
    e[tot].w=w;
    e[tot].next=head[u];
    head[u]=tot++;
}


void Insert(int x)
{
    int now=0;
    for(int i=32;i>=0;i--)
    {
        int w=(x&((ll)1<<i))>0;
        if(tree[now][w]==0)
        {
            tree[now][w]=++cnt;
        }
        now=tree[now][w];
    }
    mark[now]=x;
}

int query(int x)
{
    int now=0;
    for(int i=32;i>=0;i--)
    {
        int w=(x&((ll)1<<i))>0;
        if(tree[now][!w])
            now=tree[now][!w];
        else now=tree[now][w];
    }
    return x^mark[now];
}

void dfs(int now,int x)                 //dfs求出f(0,i)
{
    val[now]=x;
    vis[now]=1;
    for(int i=head[now];~i;i=e[i].next)
    {
        int v=e[i].v;
        int w=e[i].w;
        if(vis[v]==0) dfs(v,x^w);
    }
}

int main()
{
    while(~scanf("%d",&n))
    {
        init();
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
        }
        dfs(0,0);
        int ans=0;
        for(int i=0;i<n;i++) Insert(val[i]);
        for(int i=0;i<n;i++)
        {
            ans=max(ans,query(val[i]));
        }
        printf("%d\n",ans);
     }
    return 0;
}

```
   
   
## 洛谷的文件夹

测试网站[luogu](https://www.luogu.org/problemnew/show/P1738) 

### 题目描述

`kkksc03`是个非凡的空想家！在短时间内他设想了大量网页，然后总是交给可怜的`lzn`去实现。

洛谷的网页端，有很多文件夹，文件夹还套着文件夹。

例如：`/luogu/application/controller`表示根目录下有一个名称为`luogu`的文件夹，这个文件夹下有一个名称`application`的文件夹，其中还有名为`controller`的文件夹。

每个路径的第`1`个字符总是`/`，且没有两个连续的`/`，最后的字符不是`/`。所有名称仅包含数字和小写字母。

目前根目录是空的。`kkksc03`想好了很多应该有的文件夹路径名。问题是，需要是使这些文件夹都存在，需要新建几个文件夹呢？

### 输入格式

输入文件第1行为一个正整数`N`。

接下来`N`行，每行为一个描述路径的字符串，长度均不超过`100`。

### 输出格式

输出应包含`N`行，每行`1`个正整数，第`i`行输出若要使第`1`个路径到第`i`个路径存在，最少需要新建多少个文件夹。

### 输入样例

    4
    /a
    /a/b
    /a/c
    /b/b

### 输出样例

    1
    2
    3
    5


### 数据范围

- `1 ≤ n ≤ 10^3`

### 题目分析
   
   一眼看上去就是`Trie`。虽然暴力可过。
   
   这道题其实就是不用查找的`Trie`。直接每次输出这棵树的节点数量就可以了。
   
   每次找到这个目录的下一个`/`，取出这一个文件夹的名称，再在当前已找到的节点上寻找是否有这个文件夹，如果有，那么就直接进去，否则新建一个文件夹。
   
   我们每次读入新串的时候可以忽略这个字符串的第一个`/`，并在这个字符串的结尾加上一个`/`。
   
   由于要用到字符串为下标的二维数组，所以可以用`map+pair`。
  
  
### 代码示例

```c++

#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
#define mst(a,b) memset((a),(b),sizeof(a))
#define rush() int T;scanf("%d",&T);while(T--)

typedef long long ll;
const int maxn = 10005;
const ll mod = 1e9+7;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;

string s;
int n,cnt;
map<pair<int,string>,int> Trie;

void Insert(string s)
{
    int u=0;
    string tmp="";
    s+='/';
    for(int i=1;i<s.size();i++)
    {
        if(s[i]!='/') tmp+=s[i];
        else
        {
            if(!Trie[make_pair(u,tmp)]) Trie[make_pair(u,tmp)]=++cnt;
            u=Trie[make_pair(u,tmp)];
            tmp="";
        }
    }
    printf("%d\n",cnt);
}

int main()
{
    cin>>n;
    cnt=0;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        Insert(s);
    }
}

```
   
