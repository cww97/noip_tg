/**
 * sample input
6
0 0 1 0 0 0
0 0 0 0 0 1
0 1 0 0 0 1
0 0 0 0 1 0
0 0 0 0 0 0
0 0 0 1 0 0
1 5

sample output:
1 3 2 6 4 5
*/


#include <bits/stdc++.h>
using namespace std;
const int N = 333;

bool ok, vis[N];
int n, a[N][N], s, t, top, b[N];

void dfs(int u, int dep){
    if (ok) return;
    vis[u] = true;
    b[dep] = u;
    if (u==t){
        ok = true;
        top = dep;
        return;
    }

    for (int i = 1; i <= n; i++){
        if (a[u][i] && (!vis[i])){
            dfs(i, dep+1);
        }
    }
}

void printAns(){
    for (int i = 1; i <= top; i++){
        printf("%d%c", b[i], i==n ? '\n' : ' ');
    }
}

int main(){
    ///freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            scanf("%d", &a[i][j]);
        }
    }

    scanf("%d%d", &s, &t);
    ok = false;
    memset(vis, false, sizeof vis);
    dfs(s, 1);
    if (ok) printAns();
    else puts("-1");
    return 0;
}