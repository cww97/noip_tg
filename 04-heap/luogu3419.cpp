#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 100010, MAXM = 500010;
queue<int> q[MAXN];
int NEXT[MAXM];
int a[MAXM];
int n, k, m;
struct cmp {
    inline bool operator()(const int &x, const int &y) {
        return NEXT[x] < NEXT[y];
    }
};
priority_queue<int, vector<int>, cmp> pq;
int inq[MAXN], ans;
int main() {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        q[a[i]].push(i);
    }
    for(int i = 1; i <= m; i++) {
        q[a[i]].pop();
        if(q[a[i]].empty())NEXT[i] = m + 1;
        else NEXT[i] = q[a[i]].front();
    }
    for(int i = 1; i <= m; i++) {
        if(!inq[a[i]]) {
            if(pq.size() == k) {
                inq[a[pq.top()]] = 0;
                pq.pop();
            }
            pq.push(i);
            ++ans;
            inq[a[i]] = 1;
        } else {
            ++k;
            pq.push(i);
        }
    }
    printf("%d\n", ans);
    return 0;
}