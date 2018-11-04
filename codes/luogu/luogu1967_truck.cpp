/*
作者:CWW970329
题目:p3287 货车运输
*/
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
const int N = 1e5 + 5;
int n,m;

struct gragh{
    struct Edge{
        int from,to,w;
        Edge(){}
        Edge(int x,int y,int z):from(x),to(y),w(z){}
        bool operator < (const Edge& a)const{
            return w < a.w;
        }
    }edges[N],be[N];
    int E,f[N],fa[N][20],di[N][20],dep[N];
    bool vis[N];
    vector<int >G[N];
    int F(int x){//并查集
        return f[x]==x?x:(f[x]=F(f[x]));
    }

    inline void link(int x,int y,int z){
        edges[++E]=Edge(x,y,z);
        G[x].push_back(E);
    }

    void build(){
        E=0;
        for (int i=1;i<=n;i++)G[i].clear();
        int x,y,z;
        for (int i=1;i<=n;i++)f[i]=i;
        for (int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&z);
            be[i]=Edge(x,y,z);
            f[F(x)]=F(y);
        }
    }

    void kruskal(){
        int treenum = 0;//forests
        memset(vis,0,sizeof(vis));
        for (int i=1;i<=n;i++)if (!vis[F(i)]){
            treenum++;vis[F(i)]=1;
        }
        for (int i=1;i<=n;i++)f[i]=i;
        sort(be+1,be+m+1);
        int cnt = 0;
        for (int i=m;i>=1;i--){
            int x = be[i].from;
            int y = be[i].to  ;
            if (F(x)==F(y))continue;
            f[F(x)]=F(y);
            cnt++;
            link(x,y,be[i].w);
            link(y,x,be[i].w);
            if (cnt==n-treenum)break;
        }
    }

    void dfs(int x){
        vis[x] = 1;
        for (int i=1;i<=17;i++){
            if(dep[x]<(1<<i))break;
            fa[x][i]=fa[fa[x][i-1]][i-1];
            di[x][i]=min(di[x][i-1],di[fa[x][i-1]][i-1]);
        }
        for (int i=0;i<G[x].size();i++){
            Edge e = edges[G[x][i]];
            if (vis[e.to])continue;
            fa[e.to][0] = x;
            di[e.to][0] = e.w;
            dep[e.to] = dep[x]+1;
            dfs(e.to);
        }
    }

    int lca(int x,int y){
        if (dep[x]<dep[y])swap(x,y);
        int t = dep[x] - dep[y];
        for (int i=0;i<=17;i++)
            if ((1<<i)&t) x = fa[x][i];
        for (int i=17;i>=0;i--)
            if (fa[x][i]!=fa[y][i]){
            x=fa[x][i];y=fa[y][i];
        }
        if (x==y)return x;
        return fa[x][0];
    }

    int ask(int x,int f){//f:father
        int ans = INF;
        int t = dep[x]-dep[f];
        for (int i=0;i<=17;i++)if(t&(1<<i)){
            ans=min(ans,di[x][i]);
            x = fa[x][i];
        }
        return ans;
    }

    void work(){
        build();
        kruskal();
        memset(vis,0,sizeof(vis));
        for (int i=1;i<=n;i++)if(!vis[i])dfs(i);
        int q,x,y;
        scanf("%d",&q);
        while (q--){
            scanf("%d%d",&x,&y);
            if (F(x)!=F(y))puts("-1");
            else {
                int t = lca(x,y);
                x = ask(x,t);
                y = ask(y,t);
                printf("%d\n",min(x,y));
            }
        }
    }
}g;

int main(){
    for (;~scanf("%d%d",&n,&m);)g.work();
    return 0;
}