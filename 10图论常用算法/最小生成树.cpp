#include <bits/stdc++.h>
using namespace std;
const int INF = 500010;
const int N = 5e5 + 7;

int n;
//---------------------并查集----------------------
int father[N];

int init(int n){
    for (int i = 1; i <= n; i++) father[i] = i;
}

int findFather(int x){
    if (father[x] == x) return x;
    return father[x] = findFather(father[x]);
}



//-----

int f[N];
int F(int x){
    return f[x]==x ? x : f[x] = F(f[x]);
}

void Merge(int x, int y){
    x = F(x);
    y = F(y);
    f[x] = y;  // f[y] = x;
}

//===================最小生成树=====================
// kruskal, (prim)

struct Graph{
    struct Edge{
        int x, y, w;

        Edge(int _x, int _y, int _z):x(_x), y(_y), w(_z){}

        bool operator < (const Edge &b) const{
            return w < b.w;
        }
    } edges[N]; // 边集数组
    int E, n, f[N];

    void init(const int &n){  // iniyt...., 初始化
        this->n = n;
        E = 0;
    }

    void addEdge(const int &x, const int &y, const int &z){
        edges[E++] = Edge(x, y, z);
    }

    int kruskal(){
        for (int i = 1; i <= n; i++) f[i] = i;
        sort(edges, edges + E);

        int sum = 0, cnt = 0;
        for (int i = 0; i < E; i++){
            Edge &e = edges[i];
            if (F(e.x) == F(e.y)) continue;
            sum += e.w;
            cnt++;
            f[F(e.x)] = F(e.y);
        }
        if (cnt != n-1) return -1;
        return sum;
    }

} g;

int n = 0;

int main(){
    int n, m;
    g.init(n);
    for (int x, y, z; m--;){
        cin >> x >> y >> z;
        g.addEdge(x, y, z);
    }


    n
    
    return 0;
}