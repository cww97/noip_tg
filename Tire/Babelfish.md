# Babelfish


## 题目描述

你刚从滑铁卢搬到了一个大城市。 这里的人们说的是一种难以理解的外语方言。 幸运的是，你有一本词典来帮助你理解它们。

## 输入格式

输入由最多`100000`个字典条目组成，后面跟着一个空行，再后面跟着最多`100000`个单词的消息。 
每个字典条目都是一个包含英文单词的行，后跟一个空格和一个外语单词。 字典中同一个外语单词不会出现多次。
消息是外语中的一系列单词，每行一个单词。输入中的每个单词都是最多`10`个小写字母的序列。

## 输出格式

输出是将信息翻译成英文的结果。 外文字词不在字典中应翻译为“eh”。

## 输入样例

    dog ogday
    cat atcay
    pig igpay
    froot ootfray
    loops oopslay

    atcay
    ittenkay
    oopslay

## 输出样例

    cat
    eh
    loops    

**【测试网站】**

[POJ](http://poj.org/problem?id=2503) 

## 题目分析
   
  将字典中的单词插入到字典树中，在最后一个节点上加上其翻译单词。
  查找的时候只要找到了这个单词最后这个节点，且这个节点上的存储翻译单词的域不为空说明存在翻译，输出其翻译，如果域为空，则输出“eh”。

  
## 代码示例

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
   
   
   
