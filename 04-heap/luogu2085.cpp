#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 7;
int n, m, cnt, cnt1;
int vis[N][N];
struct F {
    int a, b, c;
} F[N];
struct node {
    int x, y, fn;
    bool operator < (const node &b)const {
        return b.y < y;
    }
} P[N];
int Calu(int t1, int t2, int t3, int _x) {
    return (_x * _x * t1 + _x * t2 + t3);
}
priority_queue <node> Q;
int main() {
    node temp;
    scanf("%d %d", &n, &m);
    for(int t1, t2, t3, i = 0; i < n; i++) {
        scanf("%d %d %d", &t1, &t2, &t3);
        F[i].a = t1;
        F[i].b = t2;
        F[i].c = t3;
    }
    for(int i = 0; i < n; i++) {
        P[cnt].fn = i;
        P[cnt].x = 1;
        P[cnt].y = Calu(F[i].a, F[i].b, F[i].c, P[cnt].x);
        cnt++;
    }
    for(int i = 0 ; i < cnt; i++) {
        Q.push(P[i]);
    }
    while(cnt1 < m) {
        temp = Q.top();
        printf("%d ", temp.y);
        cnt1++;
        Q.pop();
        temp.x++;
        temp.y = Calu(F[temp.fn].a, F[temp.fn].b, F[temp.fn].c, temp.x);
        Q.push(temp);
    }
    return 0;
}