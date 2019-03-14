# LCA 模板与练习

##luoguP3379 【模板】最近公共祖先（LCA)
平常在信息学竞赛中求LCA一般有三种办法：

### 1.倍增法求解

预处理复杂度是 O(nlogn)O(nlog⁡n) ,每次询问的复杂度是 O(logn)O(log⁡n), 属于在线解法。

```c++
/*by kzl*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
const int maxx = 5e5+500;
const int INF = 0x3f3f3f3f;
#define LEN 20
typedef long long LL;

int n,m,s,cnt,x,y;
int deep[maxx],to[2*maxx],nxt[2*maxx],head[maxx];
int father[maxx][30];//father[x][i]表示从x节点开始往上2^i层是哪个节点

//读入优化
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while((ch>'9'||ch<'0')&&ch!='-')
		ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
	if(x==0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int num=0;
	char c[25];
	while(x)
	{
		c[++num]=(x%10)+48;
		x/=10;
	}
	while(num)
		putchar(c[num--]);
	putchar('\n');
	return ;
}

//链式前向星
void add_edge(int a,int b){
	to[++cnt] = b;
	nxt[cnt] = head[a];
	head[a] = cnt;
}

//记录深度
void dfs(int x,int fa,int de){
	father[x][0] = fa;
	for (int i=1;i<=LEN;i++)
	{
		father[x][i]=father[father[x][i-1]][i-1];//仔细体会这句代码
	}
	deep[x] = de;
	for(int i=head[x];i!=-1;i = nxt[i]){
		if(to[i]!=fa)dfs(to[i],x,de+1);
	}
}

//求lca
int lca(int x,int y)
{
	if (deep[x]<deep[y]) swap(x,y);
	for(int i=LEN;i>=0;i--){
		if(deep[father[x][i]]>=deep[y])x = father[x][i];
	}
	if (x==y) return x;
	for(int i=LEN;i>=0;i--){
		if(father[x][i]!=father[y][i])x = father[x][i],y = father[y][i];
	}
	return father[x][0];
}

int main(){
	n = read();m = read(); s = read();
	memset(head,-1,sizeof(head));
	for(int i=0;i<n-1;i++){
		x = read();y = read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(s,0,1);
	for(int i=0;i<m;i++){
		x = read();y = read();
		put(lca(x,y));
	}
	return 0;
}
```


### 2.利用欧拉序转化为RMQ问题

用 ST表 求解RMQ问题，预处理复杂度 O(n+nlogn)O(n+nlog⁡n) ，每次询问的复杂度为 O(1)O(1)， 也是在线算法。
```c++
/*by kzl*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
const int maxx = 5e5+500;
const int INF = 0x3f3f3f3f;
typedef long long LL;

int n,m,s,x,y,cnt,tot;
int st[maxx],euler[2*maxx],r[2*maxx],dp[2*maxx][30];//r数组记录深度，euler记录欧拉序，st记录dfs序，dp[x][i]表示[x,x+2^i-1]区间最值
int head[maxx],nxt[2*maxx],to[2*maxx];

//读入优化
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while((ch>'9'||ch<'0')&&ch!='-')
		ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
	if(x==0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int num=0;
	char c[25];
	while(x)
	{
		c[++num]=(x%10)+48;
		x/=10;
	}
	while(num)
		putchar(c[num--]);
	putchar('\n');
	return ;
}

//链式前向星
void add_edge(int a,int b){
	to[++tot] = b;
	nxt[tot] = head[a];
	head[a] =  tot;
}

//dfs记录dfs序和欧拉序
void dfs(int now,int deep,int fa = 0){
	euler[++cnt] = now;r[cnt] = deep;
	st[now] = cnt;
	for(int i=head[now];i!=-1;i = nxt[i]){
		if(to[i]==fa)continue;
		dfs(to[i],deep+1,now);
		euler[++cnt] = now;
		r[cnt] = deep;
	}
}

//ST算法
void ST(int n){
	for(int i=1;i<=n;i++)dp[i][0] = i;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			int a = dp[i][j-1],b = dp[i+(1<<(j-1))][j-1];
			dp[i][j] = r[a]<r[b]?a:b;
		}
	}
}

//找两点间最值
int RMQ(int l,int rr){
	int k = 0;
	while(l+(1<<k)-1<=rr)k++;
	k--;
	int a = dp[l][k],b = dp[rr+1-(1<<k)][k];
	return r[a]<r[b]?a:b;
}

int lca(int a,int b){
	int aa = st[a],bb = st[b];
	if(aa>bb)swap(aa,bb);
	return euler[RMQ(aa,bb)];
}

int main(){
	n = read(),m = read(),s = read();
	memset(head,-1,sizeof(head));
	for(int i=0;i<n-1;i++){
		x = read();y = read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(s,1,-1);
	ST(cnt);
	for(int i=0;i<m;i++){
		x = read();y = read();
		put(lca(x,y));
	}
	return 0;
}
```

### 3.采用Tarjan算法求解

复杂度 O(α(n)+Q)O(α(n)+Q) ，属于离线算法。
```c++
/*by kzl*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
const int maxx = 5e5+500;
const int INF = 0x3f3f3f3f;
typedef long long LL;

int n,m,s,cnt,x,y,tot;
int head[maxx],to[2*maxx],nxt[2*maxx];//链式前向星记录树
int qu_head[maxx],qu_to[2*maxx],qu_nxt[2*maxx];//记录问题
int fa[maxx],lca[maxx],num[2*maxx],vis[maxx];

//读入优化
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while((ch>'9'||ch<'0')&&ch!='-')
		ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
	if(x==0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int num=0;
	char c[25];
	while(x)
	{
		c[++num]=(x%10)+48;
		x/=10;
	}
	while(num)
		putchar(c[num--]);
	putchar('\n');
	return ;
}

//并查集查找父亲节点
int get_father(int x){
	if(fa[x]==x)return x;
	else return fa[x] = get_father(fa[x]);
}

void add_edge(int a,int b){
	to[++cnt] = b;
	nxt[cnt] = head[a];
	head[a] = cnt;
}

void add_question(int a,int b,int c){
	qu_to[++tot] = b;
	qu_nxt[tot] = qu_head[a];
	qu_head[a] = tot;
	num[tot] = c;
}

void taijan(int x){
	vis[x] = 1;
	for(int i=head[x];i;i=nxt[i]){
		int y = to[i];
		if(!vis[y]){
			taijan(y);
			fa[y] = x;
		}
	}

	for(int i=qu_head[x];i;i=qu_nxt[i]){
		int y = qu_to[i];
		if(vis[y]){
			lca[num[i]] = get_father(y);
		}
	}
}

int main(){
	n = read();m = read(); s = read();
	for(int i=0;i<n-1;i++){
		x = read();y = read();
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=n;i++)fa[i] = i;
	for(int i=0;i<m;i++){
		x = read();y = read();
		add_question(x,y,i+1);
		add_question(y,x,i+1);
	}
	taijan(s);
	for(int i=1;i<=m;i++){
		put(lca[i]);
	}
	return 0;
}
```

## HDU2586How far away ？

题意：给一棵带边权的无根树，若干次询问，每次询问两个节点的最短距离。

解法：以任意一点为根建立欧拉序，同时dfs出所有节点到根节点的距离，询问a,b的答案就是 `dis[a]+dis[b]-2*dis[lca(a,b)]`
```c++
/*by kzl*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
const int maxx = 1e5+500;
const int INF = 0x3f3f3f3f;
#define LEN 20
typedef long long LL;

int n,m,s,cnt,x,y,c;
int deep[maxx],to[2*maxx],nxt[2*maxx],head[maxx],edge[2*maxx],val[maxx];
int father[maxx][30];

inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while((ch>'9'||ch<'0')&&ch!='-')
		ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
	if(x==0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int num=0;
	char c[25];
	while(x)
	{
		c[++num]=(x%10)+48;
		x/=10;
	}
	while(num)
		putchar(c[num--]);
	putchar('\n');
	return ;
}

void add_edge(int a,int b,int c){
	to[++cnt] = b;
	nxt[cnt] = head[a];
	head[a] = cnt;
	edge[cnt] = c;
}

void dfs(int x,int fa,int de){
	father[x][0] = fa;
	for (int i=1;i<=LEN;i++)
	{
		father[x][i]=father[father[x][i-1]][i-1];
	}
	deep[x] = de;
	for(int i=head[x];i!=-1;i = nxt[i]){

		if(to[i]!=fa){
			val[to[i]] = val[x] + edge[i];
			dfs(to[i],x,de+1);
		}
	}
}

int lca(int x,int y)
{
	if (deep[x]<deep[y]) swap(x,y);
	for(int i=LEN;i>=0;i--){
		if(deep[father[x][i]]>=deep[y])x = father[x][i];
	}
	if (x==y) return x;
	for(int i=LEN;i>=0;i--){
		if(father[x][i]!=father[y][i])x = father[x][i],y = father[y][i];
	}
	return father[x][0];
}

int main(){
	s = read();
	while(s--){
		n = read(); m = read();
		memset(head,-1,sizeof(head));
		memset(val,0,sizeof(val));
		for(int i=0;i<n-1;i++){
			x = read();y = read();c = read();
			add_edge(x,y,c);
			add_edge(y,x,c);
		}
		dfs(1,0,1);
		for(int i=0;i<m;i++){
			x = read();y = read();
			put(val[x]+val[y]-2*val[lca(x,y)]);
		}
	}
	return 0;
}
```


## POJ 3321 Apple Tree

题意：一棵树，操作一改变一个点的权值，操作二求以某个点为根的子树的权值和。

解法：如果求出了这棵树的dfs序，就可以将问题从树转化为数字序列上的问题。

- 操作1：单点修改
- 操作2：区间求和，范围是st[x],ed[x]

使用树状数组维护即可。

```c++
/*by kzl*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
const int maxx = 1e5+500;
const int INF = 0x3f3f3f3f;
typedef long long LL;

int st[maxx],ed[maxx],head[maxx],to[2*maxx],nxt[2*maxx],c[2*maxx];
int n,m,u,v,cnt,tot;

//读入优化
inline int read()
{
	char ch=getchar();
	int x=0,f=1;
	while((ch>'9'||ch<'0')&&ch!='-')
		ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
	if(x==0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int num=0;
	char c[25];
	while(x)
	{
		c[++num]=(x%10)+48;
		x/=10;
	}
	while(num)
		putchar(c[num--]);
	putchar('\n');
	return ;
}

//链式前向星
void add_edge(int a,int b){
	to[++tot] = b;
	nxt[tot] = head[a];
	head[a] = tot;
}

//dfs序
void dfs(int x,int fa){
	st[x] = ++cnt;
	for(int i = head[x];i;i = nxt[i]){
		if(to[i]==fa)continue;
		dfs(to[i],x);
	}
	ed[x] = cnt;
}

//树状数组
int lowbit(int x){
	return x&(-x);
}

void change(int x,int y){
	while(x<2*maxx){
		c[x] += y;
		x+=lowbit(x);
	}
}

int getsum(int x){
	int sum = 0;
	while(x>0){
		sum+=c[x];
		x-=lowbit(x);
	}
	return sum;
}
char s[2];
int main(){
	n = read();
	for(int i=0;i<n-1;i++){
		u = read();v = read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,-1);
	for(int i=1;i<=n;i++)change(st[i],1);
	m = read();
	while(m--){
		scanf("%s",s);u = read();
		if(s[0]=='C')change(st[u],getsum(st[u])-getsum(st[u]-1)?-1:1);
		else put(getsum(ed[u])-getsum(st[u]-1));
	}
	return 0;
}
```
