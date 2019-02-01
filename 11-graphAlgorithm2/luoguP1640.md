# luoguP1640 [SCOI2010]连续攻击游戏

## 题目描述

lxhgww最近迷上了一款游戏，在游戏里，他拥有很多的装备，每种装备都有2个属性，这些属性的值用[1,10000]之间的数表示。当他使用某种装备时，他只能使用该装备的某一个属性。并且每种装备最多只能使用一次。游戏进行到最后，lxhgww遇到了终极boss，这个终极boss很奇怪，攻击他的装备所使用的属性值必须从1开始连续递增地攻击，才能对boss产生伤害。也就是说一开始的时候，lxhgww只能使用某个属性值为1的装备攻击boss，然后只能使用某个属性值为2的装备攻击boss，然后只能使用某个属性值为3的装备攻击boss……以此类推。现在lxhgww想知道他最多能连续攻击boss多少次？

## 输入格式

输入的第一行是一个整数N，表示lxhgww拥有N种装备接下来N行，是对这N种装备的描述，每行2个数字，表示第i种装备的2个属性值

## 输出格式

输出一行，包括1个数字，表示lxhgww最多能连续攻击的次数。

## 输入样例

3    
1 2  
3 2  
4 5  

## 输出样例

2

## 说明

对于30%的数据，保证N < = 1000

对于100%的数据，保证N < = 1000000

## 测试网站

[luoguP1640](https://www.luogu.org/problemnew/show/P1640)


## 题目分析

二分图最大匹配变形，使用匈牙利算法，左边为武器属性，右边为武器编号，根据武器的属性进行建边，然后从1到属性最大值开始找增广路，若没找到则break,因为武器属性必须连续。

【源程序】

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 10;

bool vis[maxn];
int line[maxn];
int h[maxn];
int tot = 0;

struct edge{
  int to,next;
  edge(int to = 0, int next = 0) : to(to), next(next) {}
}es[maxn*2];

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
    for(int i = 1; i < p; i++)//属性从1开始
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
  scanf("%d",&n);
  memset(h,-1,sizeof(h));
  for(int i = 0; i < n; i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    add_edge(a,i);add_edge(b,i);
  }
  int ans = Max_match(n,10001);
  printf("%d\n",ans);
  return 0;
}

```
