# luoguP3386 【模板】二分图匹配

## 题目描述

给定一个二分图，结点个数分别为n,m，边数为e，求二分图最大匹配数

## 输入格式

第一行，n,m,e

第二至e+1行，每行两个正整数u,v，表示u,v有一条连边

## 输出格式

共一行，二分图最大匹配

## 输入样例

1 1 1  
1 1

## 输出样例

1

## 说明

n,m ≤ 1000, 1 ≤ u ≤ n, 1 ≤ v ≤ m, e ≤ n × m  
因为数据有坑，可能会遇到 v > m 或者 u > n 的情况。  
请把 v > m 或者 u > n 的数据自觉过滤掉。

算法：二分图匹配

## 测试网站

[luoguP3386](https://www.luogu.org/problemnew/show/P3386)



## 题目分析

二分图匹配的最大匹配问题，裸题。由于n,m都在1000以内，所以可以选用匈牙利算法(O(VE))。

【源程序】

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 10;

bool g[maxn][maxn];//存图，pXn 的图
bool vis[maxn];//标记一次寻找增广路是对边顶点
int line[maxn];//记录匹配方案
//寻找增广路O(VE)
bool dfs(int u,int n)
{
    for(int v = 0; v < n; v++)
    {
        if(g[u][v] && !vis[v])
        {
        vis[v] = true;
        if(line[v] == -1 || dfs(line[v],n))
        {line[v] = u;return true;}
        }
    }
    return false;
}

int Max_match(int n,int p)
{
    int all = 0;
    memset(line,-1,sizeof(line));  
    for(int i = 0; i < p; i++)
    {
        memset(vis,false,sizeof(vis));
        if(dfs(i,n)) all++;
    }
    return all;
}

int n,m,e;

int main()
{
  scanf("%d%d%d",&n,&m,&e);
  memset(g,false,sizeof(g));
  for(int i = 0; i < e; i++)
  {
    int u,v;
    scanf("%d%d",&u,&v);
    if(u < 1 || u > n || v < 1 || v > m) continue;
    u--,v--;
    g[u][v] = true;
  }
  int ans = Max_match(m,n);
  printf("%d\n",ans);
  return 0;
}

```
