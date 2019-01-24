# luoguP2604 [ZJOI2010]网络扩容


## 题目描述

给定一张有向图，每条边都有一个容量C和一个扩容费用W。这里扩容费用是指将容量扩大1所需的费用。  求：  
1、 在不扩容的情况下，1到N的最大流；  
2、 将1到N的最大流增加K所需的最小扩容费用。

## 输入格式

输出文件一行包含两个整数，分别表示问题1和问题2的答案。

## 输出格式

1个整数，表示具有该性质数的个数。

## 输入样例

  5 8 2  
  1 2 5 8  
  2 5 9 9     
  5 1 6 2   
  5 1 1 8   
  1 2 8 7   
  2 5 4 9   
  1 2 1 1   
  1 4 2 1   

## 输出样例

  13 19

## 说明

30%的数据中，N<=100

100%的数据中，N<=1000，M<=5000，K<=10

## 测试网站

[luoguP2604](https://www.luogu.org/problemnew/show/P2604)



## 题目分析

首先题意很明显，第一问是求最大流，直接用Dinic求最大流即可，不知道怎么求最大流请先学习如何求最大流，第二问是求最小花费下使最大流增长k，所以其本质是最小费用最大流，只需要建图时注意，将一条边分别拆成一条费用为0容量为c的边和一条费用为w容量为INF的边，然后再用EK&Spfa跑最小费用最大流的增广时，如果当前flow + a[t] >= k(需要增加的流) + maxflow(dinic所求)， 则不需要再增广，并且使cost加上相应的最后部分流增广的费用，然后返回退出即可。详见代码。

【源程序】

```c++
#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 10;
const int maxm = 1e4 + 10;

int n,m,k;
int l[maxn];//记录层数
int h[maxn];//链式前向星
int cur[maxn];
int tot = 0;

struct edge
{
  int to;
  int c;
  int next;
  edge(int x = 0, int y = 0, int z = 0) : to(x), c(y), next(z) {}
 }es[maxm*2];//记录边 注意是2倍

void add_edge(int u, int v, int c)
{
    es[tot] = edge(v,c,h[u]);
    h[u] = tot++;
    es[tot] = edge(u,0,h[v]);
    h[v] = tot++;
}

bool bfs(int s, int t)
{
   memset(l,0,sizeof(l));
   l[s] = 1;
   queue <int> q;
   q.push(s);
   while(!q.empty())
   {
    int u = q.front();
    q.pop();
    if(u == t)  return true;
    for(int i = h[u]; i != -1; i = es[i].next)
        {
         int v = es[i].to;
         if(!l[v] && es[i].c) {l[v] = l[u] + 1; q.push(v);}
        }
   }
   return false;
}

int dfs(int x, int t, int mf)
{
    if(x == t) return mf;
    int ret = 0;
    for(int &i = cur[x]; i != -1; i = es[i].next)
    {
      if(es[i].c && l[x] == l[es[i].to] - 1)
      {
        int f = dfs(es[i].to,t,min(es[i].c,mf - ret));
        es[i].c -= f;
        es[i^1].c += f;
        ret += f;
        if(ret == mf) return ret;
      }
    }
    return ret;
}

int dinic(int s, int t)
{
  int ans = 0;
  while(bfs(s,t))
  {
   for(int i = 0; i <= t; i++) cur[i] = h[i];
   ans += dfs(s,t,INF);
   }
  return ans;
}

typedef long long LL;
typedef pair<int,int> P;
//const LL mod = 1e9 + 7;

#define PI 3.1415926
#define sc(x)  scanf("%d",&x)
#define pf(x)  printf("%d",x)
#define pfn(x) printf("%d\n",x)
#define pfln(x) printf("%lld\n",x)
#define pfs(x) printf("%d ",x)
#define rep(n) for(int i = 0; i < n; i++)
#define per(n) for(int i = n-1; i >= 0; i--)
#define mem(a,x) memset(a,x,sizeof(a))

struct edge1
{
  int from,to,cap,flow,cost;
  edge1(int from,int to, int cap, int flow, int cost) : from(from),to(to),cap(cap),flow(flow),cost(cost) {}
};

int tot1 = 0;
vector<edge1> E;
vector<int> G[maxn];
int inq[maxn];
int d[maxn];
int p[maxn];
int a[maxn];


void addedge(int from, int to, int cap, int cost)
{
  E.push_back(edge1(from,to,cap,0,cost));
  E.push_back(edge1(to,from,0,0,-cost));
  tot1 = E.size();
  G[from].push_back(tot1-2);
  G[to].push_back(tot1-1);
}

bool spfa(int s, int t, int &flow, int &cost)
{
  mem(d,INF);
  mem(inq,0);
  d[s] = 0,inq[s] = 1; p[s] = 0, a[s] = INF;
  queue<int> Q;
  Q.push(s);
  while(!Q.empty())
  {
    int u = Q.front();Q.pop();
    inq[u] = 0;
    for(int i = 0; i < G[u].size(); i++)
    {
      edge1 e = E[G[u][i]];
      if(e.cap > e.flow && d[e.to] > d[u] + e.cost)
      {
        d[e.to] = d[u] + e.cost;
        p[e.to] = G[u][i];
        a[e.to] = min(a[u],e.cap - e.flow);
        if(!inq[e.to]) {Q.push(e.to); inq[e.to] = 1;}
      }
    }
  }

  if(d[t] == INF) return false;
  if(flow + a[t] >= k)
  {
    cost += d[t] * (k-flow);
    return false;
  }
  flow += a[t];
  cost += d[t] * a[t];
  int u = t;
  while(u != s)
  {
    E[p[u]].flow += a[t];
    E[p[u]^1].flow -= a[t];
    u = E[p[u]].from;
  }
  return true;
}

int mcf(int s, int t)
{
  int flow = 0,cost = 0;
  while(spfa(s,t,flow,cost)) ;
  return cost;
}


int main()
{
   scanf("%d%d%d",&n,&m,&k);
   tot = 0;
   memset(h,-1,sizeof(h));
   int u,v,c;
   for(int i = 0; i < m; i++)
   {
     int x;
    scanf("%d%d%d%d",&u,&v,&c,&x);
    add_edge(u,v,c);
    addedge(u,v,c,0);
    addedge(u,v,INF,x);
   }
   int ans = dinic(1,n);
   printf("%d",ans);
   k += ans;
   int s,t;
   s = 1, t = n;
   printf(" %d\n",mcf(s,t));
   return 0;
}

```
