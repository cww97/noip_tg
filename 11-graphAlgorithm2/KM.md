# KM 二分图最大匹配

## 奔小康赚大钱

[HDU-2255](<http://acm.hdu.edu.cn/showproblem.php?pid=2255>)

### 题意

村里要分房子。有N家老百姓，刚好有N间房子。考虑到每家都要有房住，每家必须分配到一间房子且

仅仅能分配到一间房子。另外， 村长为了得到最大利益，让老百姓对房子进行估价。

比方有3件房子，一家老百姓能够对第一间出10万，对第二间出2万，对第三间出4万。第二家老百姓能够对第一间出8万，对第二家出3万，对第三间出5万。那么问题来了：怎么分配，才干使利益最大化。

(村民房子不一定能分到房，关键看领导分配)。

### 题解

只让指定居民找到他愿意付最多钱的房子

在发生多居民抢一个房子时，用它来得到该居民到其它房子的松弛量（即该居民到其它房子 比 到这个用钱最多的房子 愿意花的钱数上差的值。）



建立二分图，一边为N家老百姓，还有一边为N间房子。对老百姓和房子之间估价建立一条有带权边。问

题就转变为了再二分图中找出一个总权值最大的匹配，也就是加权二分图最佳匹配问题。

### 代码

```C++
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N=310;
const int INF=0x3f3f3f3f;

int n,nx,ny;
int linker[N],lx[N],ly[N],slack[N];
int visx[N],visy[N],w[N][N];

int DFS(int x){
    visx[x]=1;
    for(int y=1;y<=ny;y++){
        if(visy[y])
            continue;
        int tmp=lx[x]+ly[y]-w[x][y];
        if(tmp==0){
            visy[y]=1;
            if(linker[y]==-1 || DFS(linker[y])){
                linker[y]=x;
                return 1;
            }
        }else if(slack[y]>tmp)
            slack[y]=tmp;
    }
    return 0;
}

int KM(){
    int i,j;
    memset(linker,-1,sizeof(linker));
    memset(ly,0,sizeof(ly));
    for(i=1;i<=nx;i++)
        for(j=1,lx[i]=-INF;j<=ny;j++)
            if(w[i][j]>lx[i])
                lx[i]=w[i][j];
    for(int x=1;x<=nx;x++){
        for(i=1;i<=ny;i++)
            slack[i]=INF;
        while(1){
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(DFS(x))
                break;
            int d=INF;
            for(i=1;i<=ny;i++)
                if(!visy[i] && d>slack[i])
                    d=slack[i];
            for(i=1;i<=nx;i++)
                if(visx[i])
                    lx[i]-=d;
            for(i=1;i<=ny;i++)
                if(visy[i])
                    ly[i]+=d;
                else
                    slack[i]-=d;
        }
    }
    int res=0;
    for(i=1;i<=ny;i++)
        if(linker[i]!=-1)
            res+=w[linker[i]][i];
    return res;
}

int main(){
    while(~scanf("%d",&n)){
        nx=ny=n;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&w[i][j]);
        int ans=KM();
        printf("%d\n",ans);
    }
    return 0;
}
```



## Assignment

[HDU-2853](<http://acm.hdu.edu.cn/showproblem.php?pid=2853>)

### 题意

给定一个二分图，N个点对应M个点，两两之间存在一组关系，每组关系一个权值。题目中了给定了一个匹配方案，现在要求满足这组关系中的最大的匹配权值在原方案上增长了多少？并且还要求出在原匹配方案上改变(**最少**)多少条边才能够得到这个最大匹配？

### 题解

首先如果我们只需要求最大权值匹配，那么这道题是一个左右点集大小不对称的最优匹配问题。

因为我们要变动最小，所以对在原计划中的边要有一些特殊照顾，使得最优匹配时，尽量优先使用原计划的边，这样变化才能是最小的且不会影响原匹配。

把每条边的权值扩大k倍（k>n），然后属于原始任务的边权值+1，权值加1是为了当两条边权值相同时，更优先选择属于原始任务的边，扩大k倍的巧妙之处不仅在于KM匹配时优先选择原始边所得答案除k得到原始答案，而且结果对k求余就是保留的就是原始任务的数量。

### 代码

```C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn=505;
const int oo=1e9;
int lx[maxn], ly[maxn], vx[maxn], vy[maxn], match[maxn], slack[maxn];
int map[maxn][maxn];
int n, m;

bool find(int i){
    vx[i]=1;
    for(int j=1; j<=m; j++)
        if(!vy[j]){
            int t=lx[i]+ly[j]-map[i][j];
            if(t==0){
                vy[j]=1;
                if(match[j]==-1||find(match[j])){
                    match[j]=i;
                    return true;
                }
            }
            else slack[j]=min(slack[j],t);
        }
    return false;
}

int KM(){
    int  ans=0;
    memset(match,-1,sizeof(match));
    memset(ly,0,sizeof(ly));
    for(int i=1; i<=n; i++){
        lx[i]=-oo;
        for(int j=1; j<=m; j++)
            lx[i]=max(lx[i],map[i][j]);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) slack[j]=oo;
        while(1){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if(find(i)) break;
            int d=oo;
            for(int j=1; j<=m; j++)
                if(!vy[j]) d=min(d,slack[j]);
            for(int j=1; j<=n; j++)
                if(vx[j]) lx[j]-=d;
            for(int j=1; j<=m; j++)
                if(vy[j]) ly[j]+=d;
            for(int j=1; j<=m; j++) slack[j]-=d;
        }
    }
    for(int i=1; i<=m; i++)
        if(match[i]!=-1) ans+=map[ match[i] ][i];
    return ans;
}

int main(){
    while(cin >> n >> m){
        for(int i=0; i<=n; i++)
            for(int j=0; j<=m; j++) map[i][j]=-oo;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++){
                 int c;
                 scanf("%d",&c);
                 map[i][j]=max(map[i][j],100*c);
            }
        int sum=0;
        for(int i=1,j; i<=n; i++){
            scanf("%d",&j);
            sum+=map[i][j]/100;
            map[i][j]+=1;
        }
        int ans=KM();
        printf("%d %d\n",n-ans%100,ans/100-sum);
    }
    return 0;
}
```



## Similarity

[HDU-3718](<http://acm.hdu.edu.cn/showproblem.php?pid=3718>)

### 题意

给定一个标准答案字符串，然后下面每一行给一个串，要求把字符一种对应一种，要求匹配尽量多

### 题解

显然的KM最大匹配问题，位置对应的字符连边权值+1

### 代码

```C++
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
 
const int MAXNODE = 27;
 
typedef int Type;
const Type INF = 0x3f3f3f3f;
 
struct KM {
	int n, m;
	Type g[MAXNODE][MAXNODE];
	Type Lx[MAXNODE], Ly[MAXNODE], slack[MAXNODE];
	int left[MAXNODE], right[MAXNODE];
	bool S[MAXNODE], T[MAXNODE];
 
	void init(int n, int m) {
		this->n = n;
		this->m = m;
		memset(g, 0, sizeof(g));
	}
 
	void add_Edge(int u, int v, Type val) {
		g[u][v] += val;
	}
 
	bool dfs(int i) {
		S[i] = true;
		for (int j = 0; j < m; j++) {
			if (T[j]) continue;
			Type tmp = Lx[i] + Ly[j] - g[i][j];
			if (!tmp) {
				T[j] = true;
				if (left[j] == -1 || dfs(left[j])) {
					left[j] = i;
					right[i] = j;
					return true;
				}
			} else slack[j] = min(slack[j], tmp);
		}
		return false;
	}
 
	void update() {
		Type a = INF;
		for (int i = 0; i < m; i++)
			if (!T[i]) a = min(a, slack[i]);
		for (int i = 0; i < n; i++)
			if (S[i]) Lx[i] -= a;
		for (int i = 0; i < m; i++)
			if (T[i]) Ly[i] += a;
	}
 
	Type km() {
		memset(left, -1, sizeof(left));
		memset(right, -1, sizeof(right));
		memset(Ly, 0, sizeof(Ly));
		for (int i = 0; i < n; i++) {
			Lx[i] = -INF;
			for (int j = 0; j < m; j++)
				Lx[i] = max(Lx[i], g[i][j]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) slack[j] = INF;
			while (1) {
				memset(S, false, sizeof(S));
				memset(T, false, sizeof(T));
				if (dfs(i)) break;
				else update();
			}
		}
		Type ans = 0;
		for (int i = 0; i < n; i++)
			ans += g[i][right[i]];
		return ans;
	}
} gao;
 
const int N = 10005;
 
int t, n, k, m;
char s[N][2];
 
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		while (m--) {
			gao.init(26, 26);
			char c[2];
			for (int i = 0; i < n; i++) {
				scanf("%s", c);
				gao.add_Edge(s[i][0] - 'A', c[0] - 'A', 1);
			}
			printf("%.4lf\n", gao.km() * 1.0 / n);
		}
	}
	return 0;
}
```



## Card Game

[hdu-3722](<http://acm.hdu.edu.cn/showproblem.php?pid=3722>)

### 题意

每一个字符串都需要去接另外一个字符串，每个字符串保证只存在一个环中，问一个最大权值设定方案，
对应两个字符串想要互相连接，得到的权值是这样判定的：

abc连接cba，abc翻转之后是cba，和cba每个字母都对应上了，值为3.

abc连接cda，abc翻转之后是cba，和cda的第一个字母对上了，虽然第三个字母也对上了，但是中间间隔了一个没有对上的字符，那么值为1.

### 题解

首先$n^2$设定一下每个字符串和其他字符串连接能够得到的权值。

然后根据这个权值，我们直接KM匹配即可，得到的最大值，就是最优解。

### 代码

```C++
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int map[300][300];
char a[300][2000];
int match[350];
int lx[350];
int ly[350];
int vx[350];
int vy[350];
int n,low;
int find(int u){
    vx[u]=1;
    for(int i=1;i<=n;i++){
        if(vy[i]==1)continue;
        int tmpp=lx[u]+ly[i]-map[u][i];
        if(tmpp==0){
            vy[i]=1;
            if(match[i]==-1||find(match[i])){
                match[i]=u;
                return 1;
            }
        }
        else if(tmpp<low)low=tmpp;
    }
    return 0;
}
void KM(){
    memset(match,-1,sizeof(match));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],map[i][j]);
    for(int i=1;i<=n;i++)
        while(1){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            low=0x3f3f3f3f;
            if(find(i))break;
            for(int j=1;j<=n;j++){
                if(vx[j])lx[j]-=low;
                if(vy[j])ly[j]+=low;
            }
        }
    int sum=0;
    for(int i=1;i<=n;i++)
        sum+=map[match[i]][i];
    printf("%d\n",sum);
}
void getmap(){
    memset(map,0,sizeof(map));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            int leni=strlen(a[i]);
            reverse(a[i],a[i]+leni);
            int lenj=strlen(a[j]);
            int minn=max(leni,lenj);
            for(int k=0;k<minn;k++){
                if(a[i][k]==a[j][k])
                    map[i][j]++;
                else break;
            }
            reverse(a[i],a[i]+leni);
        }
}
int main(){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++)
            scanf("%s",a[i]);
        getmap();
        KM();
    }
}

```

