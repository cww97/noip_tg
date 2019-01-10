#include <bits/stdc++.h>
using namespace std;
const int N = 33;

int n, vis[N], ind[N];
vector <int> G[N], ans;
bool loop[N];

void init(const int &n){
    for (int i = 0; i <= n; i++) G[i].clear();
    memset(ind, 0, sizeof ind);
    memset(loop, 0, sizeof loop);
}

void addEdge(const int &f, const int &t){
    G[f].push_back(t);
    ind[t]++;
}

int get_start(){
    for (int i = 1; i <= n; i++){
        if (!ind[i]) return i;
    }
    return -1;
}

bool dfs(int u){  // return 0 if there is a loop
    if (loop[u]) return 0;
    vis[u] = 1;
    loop[u] = 1;

    for (int i = 0; i < G[u].size(); i++){
        int v = G[u][i];
        if (vis[v]) continue;
        if (!dfs(v)) return 0;
    }
    ans.push_back(u);
    loop[u] = 0;
    return 1;
}

void print_top_seq(){
    for (int i = 0; i < n; i++){
        printf("%c", ans[i] + 64);
    }
    puts(".");
}

int main()
{
    freopen("in.txt", "r", stdin);
    int t1, t2, lz, m;
    char ch[90][30];
    while(scanf("%d:", &lz) == 1){
        printf("%d:\n", lz);
        scanf("%d %d",&n,&m);
        init(n);
        for(int i = 1; i <= m; i++) scanf("%s", ch[i]);

        for(int i = 1; i <= m+1; i++){
            if (i == m+1){
                printf("Sorted sequence cannot be determined.\n");
                break;
            }

            t1 = ch[i][0] - 'A' + 1;
            t2 = ch[i][2] - 'A' + 1;
            addEdge(t1, t2);
            
            int start = get_start();
            ans.clear();
            printf("start = %d\n", start);
            if (start == -1 || !dfs(start)){
                printf("Inconsistency found after %d relations.\n", i);
                break;
            } else if (ans.size() == n){
                printf("Sorted sequence determined after %d relations: ", i);
                print_top_seq();
                break;
            }
        }
    }

    return 0;
}