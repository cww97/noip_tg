# Xor-Longest-Path


## 题目描述

给出一棵树，求树中异或和最大的路径的异或值。 

## 输入格式

输入包含多个测试用例。 

每个测试用例的第一行包含一个整数`n`,表示树上节点的个数。

接下来`n-1`行每个包含三个整数`u`,`v`,`w`，这意味着在节点`u`和`v`之间存在权重为`w`的边。

## 输出格式

对于每个测试样例输出最大的异或值。

## 输入样例

    4
    0 1 3
    1 2 4
    1 3 6

## 输出样例

    7

## 样例解释

    0->1->2， 最大异或值为3^4=7

## 数据范围
- `1 ≤ n ≤ 10^5`
- `0 ≤ u,v < n`
- `0 ≤ w < 2^31`

**【测试网站】**

[POJ](http://poj.org/problem?id=3764) 

## 题目分析
   
  首先把这题模型转换一下，对于任意一条路径的异或，表示为`f(u,v)`，则`f(u,v)=f(0,u)^f(0,v)`。
  
  其中`f(0,i)`是可以在`O(n)`的时间复杂度内处理出来，然后就是在一个数组内，找两个数异或值最大。
  
  直接用`01`字典树即可。
  
  对于一个询问，在字典树上找，尽量找跟其相反的路径。
  
  比如第`30`位是`0`就尽量找最开始是`1`的路径，实在找不到就只能将这一位妥协，就是一种贪心的思路。
  
  
## 代码示例

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
   
   
   
