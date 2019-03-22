# 图和连通(Tarjan)

## HDU 1269  迷宫城堡
这是一道tarjan算法的模版题，只需要懂得基本定义即可。当强连通分量为1的时候输出Yes否者输出No。

```
#include <bits/stdc++.h>
using namespace std;

#define MAXN 10010
#define MAXM 100010

struct Edge {
  int v, next;
} edge[MAXM];   //边结点数组

int first[MAXN], stack[MAXN], DFN[MAXN], Low[MAXN], Belong[MAXM];
// first[]头结点数组,stack[]为栈,DFN[]为深搜次序数组，Belong[]为每个结点所对应的强连通分量标号数组
// Low[u]为u结点或者u的子树结点所能追溯到的最早栈中结点的次序号
int instack[10010];  // instack[]为是否在栈中的标记数组
int n, m, cnt, scnt, top, tot;

void init() {
  cnt = 0;
  scnt = top = tot = 0;    //初始化连通分量标号，次序计数器，栈顶指针为0
  memset(first, -1, sizeof(first));
  memset(DFN, 0, sizeof(DFN));   //结点搜索的次序编号数组为0，同时可以当是否访问的数组使用
}

void read_graph(int u, int v) { //构建邻接表
  edge[tot].v = v;
  edge[tot].next = first[u];
  first[u] = tot++;
}

void Tarjan(int v) {     //Tarjan算法求有向图的强连通分量
  int min, t;
  DFN[v] = Low[v] = ++tot;    //cnt为时间戳
  instack[v] = 1;    //标记在栈中
  stack[top++] = v;      //入栈
  for(int e = first[v]; e != -1; e = edge[e].next) {
    //枚举v的每一条边
    int j = edge[e].v;   //v所邻接的边
    if(!DFN[j]) {
      //未被访问
      Tarjan(j);    //继续向下找
      if(Low[v] > Low[j]) Low[v] = Low[j];  // 更新结点v所能到达的最小次数层
    } else if(instack[j] && DFN[j] < Low[v]) {
      //如果j结点在栈内,
      Low[v] = DFN[j];
    }
  }
  if(DFN[v] == Low[v]) {
    //如果节点v是强连通分量的根
    scnt++;   //连通分量标号加1
    do {
      t = stack[--top];   //退栈
      instack[t] = 0;   //标记不在栈中
      Belong[t] = scnt;   //出栈结点t属于cnt标号的强连通分量
    } while(t != v);  //直到将v从栈中退出
  }
}

void solve() {
  for(int i = 1; i <= n; i++)   //枚举每个结点，搜索连通分量
    if(!DFN[i])  //未被访问
      Tarjan(i);  //则找i结点的连通分量
}

int main() {
  while(scanf("%d%d", &n, &m) && (n || m)) {
    init();
    while(m--) {
      int u, v;
      scanf("%d%d", &u, &v);
      read_graph(u, v);
    }
    solve();     //求强连通分量
    if(scnt == 1) printf("Yes\n");  //只有一个强连通分量，说明此图各个结点都可达
    else printf("No\n");
  }
  return 0;
}
```



## POJ 2186  Popular Cows
给定 n 个节点和 m 条单向边代表关系链（可传递），求被其他所有点关系的点数。思考连通分量的基本定义可知：存在被所有点关系的点的条件是缩点图中只有一个点出度为零，而这个答案就是这个缩点代表的强连通分量中的节点数。所以这题序维护缩点的出度和原图中节点数。

```
#include<cstdio>
#include<stack>
#include<cstring>
#include<iostream>
using namespace std;
#define maxn 10010
struct EDGE {
    int to, nxt;
} edge[maxn * 5];
int head[maxn], id[maxn], dfn[maxn], low[maxn], tot, sum;
stack<int> s;
int all[maxn];
void tarjan(int u, int fa) {
    s.push(u);
    dfn[u] = low[u] = ++tot;
    for(int i = head[u]; i != -1; i = edge[i].nxt) {
        int v = edge[i].to;
        if(!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[v], low[u]);
        } else if(!id[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        sum++;
        while(!s.empty()) {
            int num = s.top();
            s.pop();
            id[num] = sum;
            all[sum]++;
            if(u == num) break;
        }
    }
    return ;
}
int main() {
    int n, m, x, y;
    while(~scanf("%d%d", &n, &m)) {
        memset(head, -1, sizeof(head));
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            edge[i].to = y;
            edge[i].nxt = head[x];
            head[x] = i;
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(id, 0, sizeof(id));
        tot = 0, sum = 0;
        while(!s.empty()) s.pop();
        memset(all, 0, sizeof(all));
        for(int i = 1; i <= n; i++) {
            if(!dfn[i]) {
                tarjan(i, -1);
            }
        }
        //cout<<"sum = "<<sum<<endl;
        int vis[maxn];
        memset(vis, 0, sizeof(vis));
        int du[maxn];
        memset(du, 0, sizeof(du));
        /*for(int i = 1;i <= sum;i++)
        {
            cout<<"all = "<<all[i]<<endl;
        }*/
        for(int u = 1; u <= n; u++) {
            for(int j = head[u]; j != -1; j = edge[j].nxt) {
                int v = edge[j].to;
                if(id[u] != id[v]) {
                    du[id[u]]++;
                }
            }
        }
        int sub = 0, last = 0;
        for(int i = 1; i <= sum; i++) {
            if(du[i] == 0) {
                sub++;
                last = i;
            }
        }
        if(sub != 1) puts("0");
        else printf("%d\n", all[last]);
    }
    return 0;
}
```

## POJ 2553  The Bottom of a Graph

定义：点v是汇点须满足 --- 对图中任意点u，若v可以到达u则必有u到v的路径；若v不可以到达u，则u到v的路径可有可无。  
题意：在n个点m条边的有向图里面，问有多少个点是汇点。  
分析：首先若SCC里面有一个点不是汇点，那么它们全不是汇点，反之也如此。这也就意味着一个SCC里面的点要么全是，要么全不是。在求出SCC并缩点后，任一个编号为A的SCC若存在指向编号为B的SCC的边，那么它里面所有点必不是汇点（因为编号为B的SCC不可能存在指向编号为A的SCC的边）。若编号为A的SCC没有到达其他SCC的路径，那么该SCC里面所有点必是汇点。因此判断的关键在于SCC的出度是否为0.
思路：先用tarjan求出所有SCC，然后缩点后找出所有出度为0的SCC，并用数字存储点，升序排列后输出。


```
#include<stdio.h>
#include<string.h>
#include<vector>
#include<stack>
#include<algorithm>
#define MAX 21000
#define INF 0x3f3f3f
using namespace std;
int cost[MAX];
int low[MAX], dfn[MAX];
int head[MAX], instack[MAX];
int ans, n, m;
int sccno[MAX], clock; //sccno用来记录当前点属于哪个scc，
int scccnt;//记录总共有多少个scc
stack<int>s;
vector<int>newmap[MAX];//scc缩点之后储存新图
vector<int>scc[MAX];//用来记录scc中的点
int out[MAX];//记录scc的入度
int ant[MAX];
struct node {
    int beg, end, next;
} edge[MAX];
void init() {
    memset(head, -1, sizeof(head));
    ans = 0;
}
void add(int u, int v) {
    edge[ans].beg = u;
    edge[ans].end = v;
    edge[ans].next = head[u];
    head[u] = ans++;
}
void getmap() {
    int i, j, a, b;
    for(i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        add(a, b);
    }
}
void tarjan(int u) {
    int v, i, j;
    low[u] = dfn[u] = ++clock;
    s.push(u);
    instack[u] = 1;
    for(i = head[u]; i != -1; i = edge[i].next) {
        v = edge[i].end;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        scccnt++;
        scc[scccnt].clear();//？？
        while(1) {
            v = s.top();
            s.pop();
            instack[v] = 0;
            sccno[v] = scccnt;
            scc[scccnt].push_back(v);
            if(v == u)
                break;
        }
    }
}
void find(int l, int r) {
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(sccno, 0, sizeof(sccno));
    memset(instack, 0, sizeof(instack));
    clock = scccnt = 0;
    for(int i = l; i <= r; i++) {
        if(!dfn[i])
            tarjan(i);
    }
}
void suodian() {
    int i, j;
    for(i = 1; i <= scccnt; i++) {
        newmap[i].clear();
        out[i] = 0;
    }
    for(i = 0; i < ans; i++) { //遍历所有的边
        int u = sccno[edge[i].beg]; //当前边的起点
        int v = sccno[edge[i].end]; //当前边的终点
        if(u != v) { //因为sccno中记录的是当前点属于哪个scc，所以u！=v证明不在同一个scc但是由一条边相连，
            //证明这两个scc联通
            newmap[u].push_back(v);//将scc中的点储存下来  ？？
            out[u]++;//两个scc联通 则入度加一，
        }
    }
}
void solve() {
    int i, j, k = 0;
    for(i = 1; i <= scccnt; i++) {
        if(out[i] == 0) {
            for(j = 0; j < scc[i].size(); j++)
                ant[k++] = scc[i][j];
        }
    }
    sort(ant, ant + k);
    for(i = 0; i < k; i++) {
        if(i < k - 1)
            printf("%d ", ant[i]);
        else
            printf("%d", ant[i]);
    }
    printf("\n");
}
int main() {
    int j, i;
    while(scanf("%d", &n), n) {
        scanf("%d", &m);

        init();
        getmap();
        find(1, n);
        suodian();
        solve();
    }
    return 0;
}
```


## UVA 11324 The Largest Clique

题意：给出一张有向图，求一个结点数最大的结点集，使得该结点集中任意两个结点u和v满足：要么u可以到到v，要么v可以到达u(u和v可以互相到达)

思路：我们可以缩点，用Tarjan求出所有强连通分量，让每个SCC的权值等于它的结点个数。由于SCC图是有一个DAG，使用DP求解。


```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

vector<int> g[MAXN], scc[MAXN], G[MAXN];
stack<int> s;
int pre[MAXN], lowlink[MAXN], sccno[MAXN], sccnum[MAXN], dfs_clock, scc_cnt;
int d[MAXN];
int n, m;

int Tarjan(int u) {
    lowlink[u] = pre[u] = ++dfs_clock;
    s.push(u);
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!pre[v]) {
            Tarjan(v);
            lowlink[u] = min(lowlink[v], lowlink[u]);
        } else if (!sccno[v]) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if (lowlink[u] == pre[u]) {
        scc_cnt++;
        for (;;) {
            int x = s.top();
            s.pop();
            sccno[x] = scc_cnt;
            sccnum[sccno[x]]++;
            if (x == u) break;
        }
    }
}

void find_scc() {
    memset(pre, 0, sizeof(pre));
    memset(lowlink, 0, sizeof(lowlink));
    memset(sccno, 0, sizeof(sccno));
    memset(sccnum, 0, sizeof(sccnum));
    dfs_clock = scc_cnt = 0;
    for (int i = 0; i < n; i++)
        if (!pre[i])
            Tarjan(i);
}

int dp(int i) {
    int &ans = d[i];
    if (ans > 0) return ans;
    ans = sccnum[i];
    for (int j = 0; j < G[i].size(); j++) {
        int v = G[i][j];
        ans = max(ans, dp(v) + sccnum[i]);
    }
    return ans;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            g[i].clear();
        int u, v;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            u--;
            v--;
            g[u].push_back(v);
        }

        find_scc();

        memset(d, -1, sizeof(d));
        memset(G, 0, sizeof(G));
        for (int u = 0; u < n; u++) {
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (sccno[u] != sccno[v])
                    G[sccno[u]].push_back(sccno[v]);
            }
        }

        int ans = 0;
        for (int i = 1; i <= scc_cnt; i++)
            ans = max(ans, dp(i));

        printf("%d\n", ans);
    }
    return 0;
}

```

## HDU 1827  Summer Holiday
题意：一个人需要联系其他所有人，已知他自己联系每个人的花费，并且他可以联系某个人再让他联系他能联系到的人，给出一系列关系表示 A 能够联系 B。问他最少需要联系多少人，花费多少钱

首先，建成一个有向图，强连通分量内的点可以相互通知，但是如果某个强连通分量入度为0，那么这个强连通分量中的点不能通过其他分量到达，因此只要通知这些入度为0的强连通分量中花费最少的一个人就行了，所以强连通时更新每个分量的最小花费值，然后建边记录入度，联系人数就是入度为0的强连通分量数，而花费就是这些分量的最小花费和。


```
#include<stdio.h>
#include<string.h>
#include<stack>
#include<queue>
using namespace std;

const int maxn = 1005;
const int maxm = 2005;

int head[2][maxn], point[2][maxm], nxt[2][maxm], size[2];
int n, t, scccnt;
int stx[maxn], low[maxn], scc[maxn], num[maxn], a[maxn], id[maxn], ans1, ans2;
stack<int>S;

void init() {
    memset(head, -1, sizeof(head));
    size[0] = size[1] = 0;
    ans1 = ans2 = 0;
}

void add(int a, int b, int c = 0) {
    point[c][size[c]] = b;
    nxt[c][size[c]] = head[c][a];
    head[c][a] = size[c]++;
    if(c)id[b]++;
}

void dfs(int s) {
    stx[s] = low[s] = ++t;
    S.push(s);
    for(int i = head[0][s]; ~i; i = nxt[0][i]) {
        int j = point[0][i];
        if(!stx[j]) {
            dfs(j);
            low[s] = min(low[s], low[j]);
        } else if(!scc[j]) {
            low[s] = min(low[s], stx[j]);
        }
    }
    if(low[s] == stx[s]) {
        scccnt++;
        while(1) {
            int u = S.top(); S.pop();
            scc[u] = scccnt;
            if(a[u] < num[scccnt])num[scccnt] = a[u];
            if(s == u)break;
        }
    }
}

void setscc() {
    memset(stx, 0, sizeof(stx));
    memset(scc, 0, sizeof(scc));
    memset(num, 0x3f, sizeof(num));
    memset(id, 0, sizeof(id));
    t = scccnt = 0;
    for(int i = 1; i <= n; ++i)if(!stx[i])dfs(i);
    for(int i = 1; i <= n; ++i) {
        for(int j = head[0][i]; ~j; j = nxt[0][j]) {
            int k = point[0][j];
            if(scc[i] != scc[k]) {
                add(scc[i], scc[k], 1);
            }
        }
    }
}

int main() {
    int m;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 1; i <= n; ++i)scanf("%d", &a[i]);
        while(m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b);
        }
        setscc();
        for(int i = 1; i <= scccnt; ++i) {
            if(!id[i]) {
                ans1++;
                ans2 += num[i];
            }
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
```

## POJ 3694  Network
题意：一个无向图可以有重边，下面q个操作，每次在两个点间连接一条有向边，每次连接后整个无向图还剩下多少桥（注意是要考虑之前连了的边，每次回答是在上一次的基础之上）

首先运行一次tarjan，求出桥和缩点，那么远无向图将缩点为一棵树，树边正好是原来的桥。每次连接两点，看看这两点是不是在同一个缩点内，如果是，那么缩点后的树没任何变化，如果两点属于不同的缩点，那么连接起来，然后找这两个缩点的LCA，，因为从点u到LCA再到点v再到点u，将形成环，里面的树边都会变成不是桥。计数的时候注意，有些树边可能之前已经被标记了，这次再经过不能再标记

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;
#define N 100010
#define M 200010

vector<int>ver[N];
int head[N], dfn[N], low[N], vis[N], fa[N], dcnt, bcnt;
struct edge {
    int u, v, used, next;
} e[2 * M];
bool isbridge[N];

inline void add(int u, int v, int &k) {
    e[k].v = v; e[k].used = 0;
    e[k].next = head[u]; head[u] = k++;
}

void LCA(int u, int v) {
    if(dfn[u] < dfn[v]) swap(u, v);
    while(dfn[u] > dfn[v]) {
        if(isbridge[u]) bcnt--;
        isbridge[u] = false;
        u = fa[u];
    }
    while(u != v) {
        if(isbridge[u]) bcnt--;
        if(isbridge[v]) bcnt--;
        isbridge[u] = isbridge[v] = false;
        u = fa[u]; v = fa[v];
    }
}

void dfs(int u) {
    vis[u] = 1; dfn[u] = low[u] = ++dcnt;
    for(int k = head[u]; k != -1; k = e[k].next)
        if(!e[k].used) {
            e[k].used = e[k ^ 1].used = 1;
            int v = e[k].v;
            if(!vis[v]) {
                fa[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
                if(dfn[u] < low[v]) {
                    bcnt++;
                    isbridge[v] = true;
                }
            } else if(vis[v] == 1) low[u] = min(low[u], dfn[v]);
        }
    vis[u] = 2;
}

int main() {
    int n, m, q, cas = 0;
    while(scanf("%d%d", &n, &m) != EOF) {
        if(!n && !m) break;
        memset(head, -1, sizeof(head));
        int k = 0;
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v, k);
            add(v, u, k);
        }
        memset(isbridge, false, sizeof(isbridge));
        memset(vis, 0, sizeof(vis));
        dcnt = bcnt = 0;
        fa[1] = 1;
        dfs(1);
        printf("Case %d:\n", ++cas);
        scanf("%d", &q);
        while(q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            LCA(u, v);
            printf("%d\n", bcnt);
        }
        printf("\n");
    }
    return 0;
}

```

## POJ 1144  Network
题意：就要给你一个图，求有多少个割点。还是一道关于tarjan算法基本定义的题目。

```
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 110;

int dfn[N], low[N], head[N], vis[N];
bool cut[N];
int k, n, cnt, root;

struct Edge {
    int to, nxt;
} edge[N << 1];

void addedge(int cu, int cv) {
    edge[cnt].to = cv;
    edge[cnt].nxt = head[cu];
    head[cu] = cnt++;
}

void Tarjan(int u, int fa) {
    int son = 0;
    vis[u] = 1;
    dfn[u] = low[u] = ++k;
    for(int i = head[u]; i != -1; i = edge[i].nxt) {
        int v = edge[i].to;
        if(vis[v] == 1 && v != fa)
            low[u] = min(low[u], dfn[v]);
        if(vis[v] == 0) {
            Tarjan(v, u);
            son++;
            low[u] = min(low[u], low[v]);
            if((u == root && son > 1) || (u != root && dfn[u] <= low[v]))
                cut[u] = 1;
        }
    }
    vis[u] = 2;
}

int main() {

    //freopen("input.txt","r",stdin);

    while(~scanf("%d", &n) && n) {
        memset(head, -1, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(vis, 0, sizeof(vis));
        memset(cut, 0, sizeof(cut));
        cnt = 0;
        int u, v;
        while(scanf("%d", &u) && u) {
            while(getchar() != '\n') {
                scanf("%d", &v);
                addedge(u, v);
                addedge(v, u);
            }
        }
        root = 1;
        Tarjan(root, -1);
        int ans = 0;
        for(int i = 1; i <= n; i++)
            if(cut[i])
                ans++;
        printf("%d\n", ans);
    }
    return 0;
}
```

## HDU 3686  Traffic Real Time Query System
题意：给出一个无向连通图，然后给出S，T分别代表起始路和终止路的编号，问之间必须要经过的点有多少个?
分析：这样的点一定是割点，首先用tarjan算法找出割点（第一类点），然后求出点联通分量（边构成的块形成第二类点），缩点后形成一棵树，第一类点和第二类点是交叉相连的，所以用LCA找出最短路径后的距离/2就是结果；

```
#include<bits/stdc++.h>
#define M 10009
#define N 100009
#include"stdlib.h"
#include"math.h"
#define inf 99999999
using namespace std;
struct node { //构建原图
    int u, v, next, vis;
} edge[N * 2];
stack<int>q;
int t, head[M], dfn[M], low[M], cut[M], use[N * 2], index, num, belong[N * 2];
struct Tree { //缩点后的图
    int v;
    Tree() {}
    Tree(int vv): v(vv) {}
};
vector<Tree>Edge[M + N];
void init() {
    t = 0;
    memset(head, -1, sizeof(head));
    memset(edge, 0, sizeof(edge));
}
void add(int u, int v) {
    edge[t].u = u;
    edge[t].v = v;
    edge[t].next = head[u];
    head[u] = t++;
}
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++index;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if(edge[i].vis)continue;
        edge[i].vis = edge[i ^ 1].vis = 1;
        q.push(i);
        if(!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                num++;
                cut[u]++;
                int j;
                do {
                    j = q.top();
                    q.pop();
                    belong[j] = belong[j ^ 1] = num; //形成边连通块
                } while(j != i);
            }
        } else
            low[u] = min(low[u], dfn[v]);
    }
    if(fa < 0)
        cut[u]--;
}
void solve(int n) {
    index = num = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(cut, 0, sizeof(cut));
    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i, -1);
}
struct LCA {
    int u, v, w, next;
} lca[N * 3];
int t1, head1[N * 2], f[N * 2], dis[N * 2];
void Init() {
    t1 = 0;
    memset(head1, -1, sizeof(head1));
}
void Addlca(int u, int v) {
    lca[t1].u = u;
    lca[t1].v = v;
    lca[t1].next = head1[u];
    head1[u] = t1++;
}
int finde(int x) {
    if(x != f[x])
        f[x] = finde(f[x]);
    return f[x];
}
void make(int a, int b) {
    f[finde(a)] = finde(b);
}
void dfs(int u) { //离线LCA算法
    use[u] = 1;
    for(int i = 0; i < (int)Edge[u].size(); i++) {
        int v = Edge[u][i].v;
        if(!use[v]) {
            dis[v] = dis[u] + 1;
            dfs(v);
            f[v] = u;
            make(u, v);
        }
    }
    for(int i = head1[u]; i != -1; i = lca[i].next) {
        int v = lca[i].v;
        if(use[v])
            lca[i].w = lca[i ^ 1].w = f[finde(v)];
    }
}
void slove() {
    dis[1] = 0;
    for(int i = 0; i <= num; i++)
        f[i] = i;
    memset(use, 0, sizeof(use));
    for(int i = 1; i <= num; i++)
        if(!use[i])
            dfs(i);
    for(int i = 0; i < t1; i += 2) {
        int u = lca[i].u;
        int v = lca[i].v;
        int mid = lca[i].w;
        printf("%d\n", (dis[u] + dis[v] - 2 * dis[mid]) / 2);
    }
}
int main() {
    int n, m, i, u, v;
    while(scanf("%d%d", &n, &m), m || n) {
        init();
        for(i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            add(u, v);
            add(v, u);
        }
        solve(n);
        memset(use, 0, sizeof(use));
        for(u = 1; u <= n; u++) {
            if(cut[u]) {
                ++num;
                for(i = head[u]; i != -1; i = edge[i].next) {
                    if(!use[belong[i]]) {
                        Edge[num].push_back(belong[i]);
                        Edge[belong[i]].push_back(num);
                        use[belong[i]] = 1;
                    }
                }
                for(i = head[u]; i != -1; i = edge[i].next)
                    use[belong[i]] = 0;
            }
        }
        int Q;
        scanf("%d", &Q);
        Init();
        while(Q--) {
            scanf("%d%d", &u, &v);
            Addlca(belong[u * 2 - 1], belong[v * 2 - 1]);
            Addlca(belong[v * 2 - 1], belong[u * 2 - 1]);
        }
        slove();
        for(i = 0; i <= num; i++)
            Edge[i].clear();
    }
}
```


## 题目地址
```
https://vjudge.net/contest/235935#overview
```
