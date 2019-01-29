# Shortest Prefixes


## 题目描述

给你一些单词，让你求出他们最短的前缀，当然，这个前缀不能有歧义，例如给出单词 `carton`、`cart`、`car`

`carton`的前缀就不能是`cart`，因为`cart`的前缀是`cart`，同理`cart`的前缀也不能是`car`。 

要找到每个单词独一无二且是最短的前缀，`car`的前缀不能是，`c`,`ca`，因为他们在别的单词中也有出现

如果找不到独一无二，那个这个单词本身就是他自己的前缀。 

## 输入格式

输入数据有`n`行。
每行一个字符串`S`。

## 输出格式

对于每个字符串输出一行，输出它本身和最短前缀，中间用空格隔开。

## 输入样例

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

## 输出样例

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
    
## 数据范围
- `2 ≤ n ≤ 1000`
- `1 ≤ |S| ≤ 20`

**【测试网站】**

[POJ](http://poj.org/problem?id=2001) 

## 题目分析
   
  首先容易发现这个是一道字典树的题目，我们只要在建立字典树的时候标记一下经过某个节点的单词数目
  
  那么在查找的时候我们只要找到单词数目为1的节点就能找到最短前缀了
  
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
   
   
   
