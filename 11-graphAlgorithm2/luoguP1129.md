# luoguP1129 [ZJOI2007]矩阵游戏


## 题目描述

小Q是一个非常聪明的孩子，除了国际象棋，他还很喜欢玩一个电脑益智游戏――矩阵游戏。矩阵游戏在一个N×N黑白方阵进行（如同国际象棋一般，只是颜色是随意的）。每次可以对该矩阵进行两种操作：

行交换操作：选择矩阵的任意两行，交换这两行（即交换对应格子的颜色）

列交换操作：选择矩阵的任意两列，交换这两列（即交换对应格子的颜色）

游戏的目标，即通过若干次操作，使得方阵的主对角线(左上角到右下角的连线)上的格子均为黑色。

对于某些关卡，小Q百思不得其解，以致他开始怀疑这些关卡是不是根本就是无解的！于是小Q决定写一个程序来判断这些关卡是否有解。

输入格式

第一行包含一个整数T，表示数据的组数。

接下来包含T组数据，每组数据第一行为一个整数N，表示方阵的大小；接下来N行为一个N×N的01矩阵（0表示白色，1表示黑色）。

## 输出格式

包含T行。对于每一组数据，如果该关卡有解，输出一行Yes；否则输出一行No

## 输入样例

2  
2  
0 0  
0 1  
3  
0 0 1  
0 1 0  
1 0 0  

## 输出样例

No  
Yes

## 说明

对于20%的数据，N ≤ 7
对于50%的数据，N ≤ 50
对于%100%的数据，N ≤ 200

## 测试网站

[luoguP1129](https://www.luogu.org/problemnew/show/P1129)

## 题目分析

二分图最大匹配变形，使用匈牙利算法。
行和列交换，问是否最终能使正对角线上的各自全为黑色，经过观察可以发现，对于任意2个黑色方块，如果它们初始状态时不在同一行（列），那么无论如何交换，它们都不会在同一行（列）。所以，只需要查看初始状态下，对于每一行是否有一列能与之匹配，再利用二分图最大匹配查看行和列的匹配数，如若等于n,则说明则可以满足题意。输出yes,否则输出No。

【源程序】

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 10;
const int maxm = 100000 + 10;

bool vis[maxn];
int line[maxn];
int h[maxn];
int tot = 0;

struct edge{
  int to,next;
  edge(int to = 0, int next = 0) : to(to), next(next) {}
}es[maxm];

void add_edge(int u, int v)
{
 es[tot] = edge(v,h[u]);
 h[u] = tot++;
}

bool dfs(int u,int n)
{
    for(int i = h[u]; ~i ; i = es[i].next)
    {
        int v = es[i].to;
        if(!vis[v])
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
    for(int i = 1; i <= p; i++)
    {
        memset(vis,false,sizeof(vis));
        if(dfs(i,n)) all++;
        else break;
    }
    return all;
}

int n;

int main()
{
  int T;
  scanf("%d",&T);
  while(T--)
  {
  tot = 0;
  scanf("%d",&n);
  memset(h,-1,sizeof(h));
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      {
        int x;
        scanf("%d",&x);
        if(x == 1)
           add_edge(i,j);

      }
  int ans = Max_match(n,n);
  if(ans == n)
  printf("Yes\n");
  else printf("No\n");
}
  return 0;
}

```
