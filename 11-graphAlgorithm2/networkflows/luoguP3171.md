# luoguP3171 [CQOI2015]网络吞吐量


## 题目描述

路由是指通过计算机网络把信息从源地址传输到目的地址的活动，也是计算机网络设计中的重点和难点。网络中实现路由转发的硬件设备称为路由器。为了使数据包最快的到达目的地，路由器需要选择最优的路径转发数据包。例如在常用的路由算法OSPF(开放式最短路径优先)中，路由器会使用经典的Dijkstra算法计算最短路径，然后尽量沿最短路径转发数据包。现在，若已知一个计算机网络中各路由器间的连接情况，以及各个路由器的最大吞吐量（即每秒能转发的数据包数量），假设所有数据包一定沿最短路径转发，试计算从路由器1到路由器n的网络的最大吞吐量。计算中忽略转发及传输的时间开销，不考虑链路的带宽限制，即认为数据包可以瞬间通过网络。路由器1到路由器n作为起点和终点，自身的吞吐量不用考虑，网络上也不存在将1和n直接相连的链路。。

## 输入格式

输入文件第一行包含两个空格分开的正整数n和m，分别表示路由器数量和链路的数量。网络中的路由器使用1到n编号。接下来m行，每行包含三个空格分开的正整数a、b和d，表示从路由器a到路由器b存在一条距离为d的双向链路。 接下来n行，每行包含一个正整数c，分别给出每一个路由器的吞吐量。

## 输出格式

输出一个整数，为题目所求吞吐量。

## 输入样例

  7 10  
  1 2 2  
  1 5 2  
  2 4 1  
  2 3 3  
  3 7 1  
  4 5 4  
  4 3 1  
  4 6 1  
  5 6 2  
  6 7 1  
  1  
  100  
  20  
  50  
  20  
  60  
  1  

## 输出样例

  70

## 说明

对于100%的数据，n<=500，m<=100000，d,c<=10^9

## 测试网站

[luoguP3171](https://www.luogu.org/problemnew/show/P3171)



## 题目分析

题意：有一个路由网络, 每个路由器有一个吞吐量, 不同的路由器之间会有链路, 该链路带宽不限, 但是有一个距离, 该路由网络的传输数据严格按照算法OSPF(开放式最短路径优先)来规划数据传输，即使用经典的Dijkstra算法计算最短路径并沿最短路径转发数据包。然后求1到n的最大吞吐量。  
解决办法：拆点建图，将路由器拆成两个点，i,i+n,然后构建一条流量为吞吐量的边(i --> i+n); 在原路由网络双向跑最短路，然后根据d1[],d2[],d的关系来选择有效边, 即最短路上的边，将该边放入新网络，流量为INF。 然后跑dinic最大流即可。  
注意：1,n,自己本身的吞吐量不受限制; 由于最短路不一定只有一条, 所以maxflow 可能会超过1e9, 所以要用long long !


【源程序】

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair <LL,int> P;
const int INF = 0x3f3f3f3f;
const int maxn = 600 + 10;
const int maxm = 1e5 + 10;


int n,m;
int a[maxm],b[maxm],c[maxn];
LL d1[maxn],d2[maxn],d[maxm];

struct edge
{
    int to,cost;
    edge(int u = 0,int d = 0) : to(u),cost(d) {}
};

vector <edge> G[maxn];

void dijkstra()
{
    for(int i = 0; i <= n; i++) d1[i] = 1e18;
    d1[1] = 0;
    priority_queue < P,vector<P>,greater<P> >  Q;//P.first 是距离，.P.second 是顶点
    Q.push(P(0,1));
    while(!Q.empty())
    {
        P x = Q.top();
        Q.pop();
        LL dist = x.first;
        int u = x.second;

        if(d1[u] < dist) continue;//排除u相同时, dist不同的情况。
        for(int i = 0; i < G[u].size(); i++)
        {
            edge e = G[u][i];
            if(d1[e.to] > d1[u] + e.cost)
            {
                d1[e.to] = d1[u]+ e.cost;
                Q.push(P(d1[e.to],e.to));
            }
        }
    }

    for(int i = 0; i <= n; i++) d2[i] = 1e18;
    d2[n] = 0;
    Q.push(P(0,n));
    while(!Q.empty())
    {
        P x = Q.top();
        Q.pop();
        LL dist = x.first;
        int u = x.second;

        if(d2[u] < dist) continue;//排除u相同时, dist不同的情况。
        for(int i = 0; i < G[u].size(); i++)
        {
            edge e = G[u][i];
            if(d2[e.to] > d2[u] + e.cost)
            {
                d2[e.to] = d2[u]+ e.cost;
                Q.push(P(d2[e.to],e.to));
            }
        }
    }

}

void input()
{
    for(int i = 0; i < m; i++)
    {
      int u,v,dist;
      scanf("%d%d%d",&u,&v,&dist);
      a[i] = u, b[i] = v, d[i] = dist;
      G[u].push_back(edge(v,dist));
      G[v].push_back(edge(u,dist));
    }
    for(int i = 1; i <= n; i++)  scanf("%d",&c[i]);
}

int l[maxn*2];//记录层数
int h[maxn*2];//链式前向星
int cur[maxn*2];
int tot = 0;

struct edge1
{
  int to,c,next;
  edge1(int x = 0, int y = 0, int z = 0) : to(x), c(y), next(z) {}
}es[maxm*2+maxn];//记录边 注意是2倍

void add_edge(int u, int v, int c)
{
   //cout << u << " " << v << " " << c << endl;
    es[tot] = edge1(v,c,h[u]);
    h[u] = tot++;
    es[tot] = edge1(u,0,h[v]);
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

LL dinic(int s, int t)
{
  LL ans = 0;
  while(bfs(s,t))
  {
   for(int i = 0; i <= 2*n; i++) cur[i] = h[i];
   ans += dfs(s,t,1e9);
   }
  return ans;
}


void select_build()
{
  memset(h,-1,sizeof(h));
  for(int i = 2; i < n; i++) add_edge(i,i+n,c[i]);
  for(int i = 0; i < m; i++)
    {
      if(d1[a[i]]+d2[b[i]]+d[i] == d1[n])
       add_edge(a[i]+n,b[i],INF);
      if(d2[a[i]]+d1[b[i]]+d[i] == d1[n])
       add_edge(b[i]+n,a[i],INF);
     }
}


int main()
{
  scanf("%d%d",&n,&m);
  input();
  dijkstra();
  select_build();
  printf("%lld\n", dinic(n+1,n));
  return 0;
}

```
