# Xor-Longest-Path


## 题目描述

给出一棵树，求树中异或和最大的路径的异或值。 

## 输入格式

输入包含多个测试用例。 
每个测试用例的第一行包含一个整数`n`,表示树上节点的个数。
以下`n-1`行每个包含三个整数`u`,`v`,`w`，这意味着在节点u和v之间存在权重为w的边。

## 输出格式

对于每个测试样例输出最大的异或值。

## 输入样例

    4
    0 1 3
    1 2 4
    1 3 6

## 输出样例

    7
    
## 数据范围
- `1 ≤ n ≤ 10^5`
- `0 ≤ u,v < n`
- `0 ≤ w < 2^31`

**【测试网站】**

[POJ](http://poj.org/problem?id=3764) 

## 题目分析
   
  首先把这题模型转换一下，对于任意一条路径的异或，表示为`f(u,v)`，则`f(u,v)=f(1,u)^f(1,v)`。
  其中`f(1,i)`是可以在`O(n)`的时间复杂度内处理出来，然后就是在一个数组内，找两个数异或值最大。
  直接用`01`字典树即可。
  对于一个询问，在字典树上找，尽量找跟其相反的路径。
  比如第`30`位是`0`就尽量找最开始是`1`的路径，实在找不到就只能将这一位妥协，就是一种贪心的思路。
  
  
## 代码示例

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
   
   
   
