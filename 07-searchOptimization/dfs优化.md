# DFS优化 #



## 狗哥玩木棒

[洛谷 P2383](https://www.luogu.org/problemnew/show/P2383 "洛谷P2383 狗哥玩木棒")

## 题目大意：

&emsp;&emsp;给出n个木棒的长度，问这些木棒能否拼凑成为一个正方形

## 题目分析：

&emsp;&emsp;这个题目，首先是要拼成正方形，所以，我们可以确定每一条边的长度应该是总长度除以4。然后，我们就进行搜索，由于我们知道每一条边的长度，当某一条边上的值大于答案，那么这个答案就不需要考虑了。就可以对这种情况进行剪枝。     

## 代码
    #include <bits/stdc++.h>
    using namespace std;
    const int maxn=1e5+50;
    int n;
    int m,eva;
    int s[maxn];
    int flag;
    bool cmp(int a,int b){return a>b;}
    void dfs(int k,int a,int b,int c,int d)
    {
    	if(a>eva||b>eva||c>eva||d>eva)return;
    	if(a==eva&&b==eva&&c==eva&&d==eva) flag=1;
		if(flag==1)return;
		dfs(k+1,a+s[k],b,c,d);
		dfs(k+1,a,b+s[k],c,d);
		dfs(k+1,a,b,c+s[k],d);
		dfs(k+1,a,b,c,d+s[k]);
    }
    int main()
    {
	    scanf("%d",&n);
	    int all=0;
	    while(n--)
	    {
		    scanf("%d",&m);
		    all=0;
		    memset(s,0,sizeof(s));
		    for(int i=1;i<=m;i++) {scanf("%d",&s[i]);all+=s[i];}
		    if(all%4) {puts("no");continue;}
		    eva=all/4;
		    sort(s+1,s+1+m,cmp);
		    flag=0;
		    dfs(1,0,0,0,0);
		    if(flag)puts("yes");
		    else puts("no");
	    
	    }
	    return 0;
    }
    



## 小木棍［数据加强版］

[洛谷 P1120](https://www.luogu.org/problemnew/show/P1120)
## 题目大意

&emsp;&emsp;把一些长的木棍随意砍成若干段，已知被砍后每根小木棍的长度（被砍后长度小于50），试求原来木棍的最小可能长度

## 题目分析
&emsp;&emsp;首先要注意这道题要无视长度大于50的输入

&emsp;&emsp;对于这个问题，其实类似上面的问题，我们很自然的想到搜索，本题与上一题的区别在于，这道题目他没有告诉你原来有多少个木棍，而上一道题明确了原来有四个，那么这道题我们就可以枚举答案，如果我们知道最小的长度，那么我们已知总数，自然可以算出原来一共有多少个，这样以后，我们就将新的问题，转化成为已知的问题了。

&emsp;&emsp;当然，我们在枚举答案的时候，很显然，下限应该是已经有的木棍中的最小值

&emsp;&emsp;然后，这个问题的难点就在于如何剪枝。

&emsp;&emsp;首先，我们肯定是先放长的木棍，再放短的木棍，这样可以变得更加容易凑成

&emsp;&emsp;其次，我们当填充好一个位置的时候，就从后面查找缺口补上，如果补不上说明这条路径失败，就停止搜索
## 代码

    #include<cstdio>
    #include<cstdlib>
    const int N = 70 ;
    int n , cnt , tot , maxn , minn , tm[ N ] /* 2 */ ; 
    void dfs( int res , int sum , int target , int p ) {
	    if( res == 0 ) {
	    printf("%d", target  );
	    exit( 0 );
    }
	    if( sum == target ) {
	    dfs( res - 1 , 0 , target , maxn );
	    return;
    }
	    for( int i = p ; i >= minn ; i -- ) { // 2  3 
	    	if( tm[ i ] && i + sum <= target ) {
	    		tm[ i ] -- ;
	    	dfs( res , sum + i , target , i );
	   		tm[ i ] ++ ;
	    if ( sum == 0 || sum + i == target )  //4
	    	break;
    }
    }
    return;
    }
    int main() {
	    scanf("%d" , &n ) ;
	    minn = N ;
	    int temp;
	    while( n -- ) {
		    scanf("%d" , &temp );
		    if( temp <= 50 ) {
			    cnt ++;
			    tm[ temp ] ++;
			    tot += temp;
			    maxn = maxn > temp ? maxn : temp ;   //1
			    minn = minn < temp ? minn : temp ;
		    }
	    }
	    temp = tot >> 1;
	    for( int i = maxn ; i <= temp ; i ++ ) {
		    if( tot % i == 0 ) {
		    	dfs( tot / i , 0 , i , maxn );
		    }
	    }
	    printf("%d" , tot );
    return 0;
    }  


## 生日蛋糕

[ P1731 [NOI1999] ](https://www.luogu.org/problemnew/show/P1731)

## 题目大意：
&emsp;&emsp;一个蛋糕，每一层都是圆柱体，已知整个蛋糕的体积为Nπ，（n<=20000),并已知层数M，要求一种方案，使得表面积最小。

## 题目分析

&emsp;&emsp;首先确定范围，已知体积，那么半径和高度不会超过28

&emsp;&emsp;然后就可以进行搜索了。但是爆搜基本上就是会超时，所以我们需要进行剪枝

&emsp;&emsp;当搜索到的蛋糕已经超过体积，或者表面积已经超过最优值，就停止搜索即可。

&emsp;&emsp;如果当前的体积加上之后的体积 不到N的话，也直接 停止


## 代码

```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int r[30],h[30],minn=2147483647,n,m;
void dfs(int x,int y,int k,int z)
{  if(y<0) return;
    if(x>m+1) return;
     if(k>=minn) return;
    if(y==0&&x==m+1)
    {  k+=r[1]*r[1];
         if(k<minn) minn=k;
         return;
    }
    if(k+z+r[1]*r[1]>minn) return;
   if(y-(r[x-1])*(r[x-1])*(h[x-1])*z>0) return;
    for(int i=r[x-1]-1;i>=z;i--)
      for(int j=h[x-1]-1;j>=z;j--)
      {
            if(y-i*i*j>=0&&x+1<=m+1)
             {     r[x]=i;
                   h[x]=j;
                    dfs(x+1,y-i*i*j,k+(i*2*j),z-1);
                   h[x]=0;
                   r[x]=0;
             }
      }
}
int main()
{
    scanf("%d%d",&n,&m);
    r[0]=(int)sqrt(n);
    h[0]=(int)sqrt(n);
    dfs(1,n,0,m);
    if(minn==2147483647) printf("%d",0);
      else printf("%d",minn);
    return 0;
}
```




## 吃奶酪

[洛谷P1433](https://www.luogu.org/problemnew/show/P1433)

## 题目大意
&emsp;&emsp;给定n块奶酪的坐标，求从(0,0)点出发，问最少要走多少距离

## 题目分析
&emsp;&emsp;我们每次一定是从一块奶酪走到另一块奶酪，走直线的近距离是最短的，所以，我们暴力枚举每一块奶酪访问的顺序，然后将答案相加，这样的话复杂度应该是n!，n=15时就太大了。
&emsp;&emsp;于是我们还要进行剪枝，如果当前路径已经大于求得的答案就可以退出。

```
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int n,v[1001];
double x[100];
double y[20]; 
double dis[1001][1001];
double ans=1231234424.0; 
void dfs(int step,int now,double length)
    if(length>ans)     return;                                                                
    if(step==n)  
      {
          ans=min(ans,length);  
          return;
      }
    for(int i=1;i<=n;i++)  
      if(!v[i])   
        {
            v[i]=1; 
            dfs(step+1,i,length+dis[now][i]); 
            v[i]=0; 
        }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
      cin>>x[i]>>y[i];
    x[0]=0;y[0]=0;  
    for(int i=0;i<=n;i++)  
      for(int j=0;j<=n;j++)
        dis[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    dfs(0,0,0.0); 
    printf("%.2f",ans);
    return 0;
}```

## 滑雪
[P1434 [SHOI2002]
](https://www.luogu.org/problemnew/show/P1434)

## 题目大意

&emsp;&emsp;给定一个二维数组，从某一个点出发，可以向四周滑落，但要求高度是减小的，问最长的滑坡的长度

## 题目分析
&emsp;&emsp;这个题目是一个明显的记忆化，因为每个点只能从高处滑下来，我们枚举起点，然后从起点开始往下搜索，搜索这个点所能往上走的最高距离，并把这个值保存下来，然后在后面再次搜索到这个值的时候，我们就可以用之前储存过的结果，降低复杂度拉。

## 代码
```
#include<cstdio>
#define r(i,a,b) for (int i=a;i<=b;i++)
#define pk putchar(32)
#define ph putchar(10)
using namespace std;int t,n,m;
int h[101][101],ans,f[101][101]
int max(int x,int y){return x>y?x:y;}int min(int x,int y){return x<y?x:y;}
short dx[]={-1,0,1,0};
short dy[]={0,1,0,-1};
void read(int &a)
{
    a=0;int d=1;char c;
    while (c=getchar(),c<'0'||c>'9') if (c=='-') d=-1;a=a*10+c-48;
    while (c=getchar(),c>='0'&&c<='9') a=a*10+c-48;
    a*=d;
}
void write(int x)
{
    if (x<0) {x=-x;putchar(45);}
    if (x) 
     write(x/10);
    else return;
    putchar(x%10+48);
}
int dfs(int x,int y)
{
    if (f[x][y]) return f[x][y];
    int t=1;
    r(i,0,3)
    {
        int nx=x+dx[i];
        int ny=y+dy[i];
        if (nx>=1&&nx<=n&&ny>=1&&ny<=m&&h[x][y]<h[nx][ny])
            t=max(dfs(nx,ny)+1,t);
    }
    f[x][y]=t;
    return t;
}
int main()
{
    read(n);read(m);
    r(i,1,n)
     r(j,1,m)
      read(h[i][j]);
    r(i,1,n)
     r(j,1,m)
      {
          t=dfs(i,j);
          f[i][j]=t;
          ans=max(f[i][j],ans);
      }
    write(ans);
}
```


## 棋盘
[洛谷P3956](https://www.luogu.org/problemnew/show/P3956)
## 题目大意
&emsp;&emsp;在一个m*m的棋盘上，有三种格子，红色、黄色、无色的格子，要求从左上角走到右下角，只能走上下左右四个方向，然后，在同种颜色的格子上走，花费为0，在不同颜色的格子上走花费为1，不能走在无色的格子上，但是可以花费2，将无色变为其他颜色，离开之后颜色复原，并且不能连续两步变两个无色格子。
&emsp;&emsp;求最小的花费。


## 题目分析

&emsp;&emsp;这个题目我们可以用BFS去搜索，向四个方向搜索，并且存储当前结点的颜色，和是否变过色，以及到达该节点的最小花费，然后不断bfs，遇到变过色的情况，那么改变的颜色和过来的结点颜色一致就可以。

## 代码
```
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int map[105][105],val[105][105];
struct node{
    int x,y,c,v;
};
queue<node>q;
int main() {
    int m,n,di[4][2]={0,1,1,0,0,-1,-1,0},ans=0x7f7f7f7f;
    memset(map,-1,sizeof(map));
    memset(val,0x7f,sizeof(val));
    cin>>m>>n;
    for(int i=0;i<n;i++){
        int x,y,c;
        cin>>x>>y>>c;
        map[x][y]=c;
    }
    q.push((node){1,1,map[1][1],0});
    val[1][1]=0;
    while(!q.empty()){
        int x=q.front().x,y=q.front().y,c=q.front().c,v=q.front().v;
        if(v>ans){
            q.pop();
            continue;
        }
        if(x==m&&y==m){
            ans=min(ans,v);
            q.pop();
            continue;
        }
        for(int k=0;k<4;k++){
            int dx=x+di[k][0],dy=y+di[k][1];
            if(dx>0&&dy>0&&dx<=m&&dy<=m){
                int bc=map[x][y],dc=map[dx][dy],mv=val[dx][dy],dv;
                if(dc>=0&&bc>=0){
                    dv=v+(dc==bc?0:1);
                    if(mv>dv){
                        q.push((node){dx,dy,dc,dv});
                        val[dx][dy]=dv;
                    }
                }else if(dc<0&&bc>=0){
                    if(mv>v+2){
                        q.push((node){dx,dy,bc,v+2});
                        val[dx][dy]=v+2;
                    }
                }else if(dc>=0&&bc<0){
                    dv=v+(c==dc?0:1);
                    if(mv>dv){
                        q.push((node){dx,dy,dc,dv});
                        val[dx][dy]=dv;
                    }
                }
            }
        }
        q.pop();
    }
    if(ans==0x7f7f7f7f){
        cout<<"-1"<<endl;
    }else {
        cout<<ans<<endl;
    }
    return 0;
}
```
