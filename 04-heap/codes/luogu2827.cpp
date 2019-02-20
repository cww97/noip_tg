#include <cstdio>
#include <queue>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 10;
const int MAXM = 7 * 1e6 + 10;
int n, m, q, v, t, a[MAXN], den, size, ans[MAXN + MAXM], u;
double p;
bool cmp(int a, int b) {
    return a > b;
}
queue <int> e[3];
int getMax() {
    int res = -1;
    for(int i = 0; i < 3; i++) {
        if((!e[i].empty()) && (res == -1 || e[i].front() > e[res].front()))
            res = i;
    }
    return res;
}
int main() {
    scanf("%d %d %d %d %d %d", &n, &m, &q, &u, &v, &t);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++)
        e[0].push(a[i]);
    for(int i = 1; i <= m; i++) {
        int f1 = 0, f2 = 0, f3 = 0;
        int id = getMax();
        int sope = (i - 1) * q;
        int fx = e[id].front();
        e[id].pop();
        fx += sope;
        if(!(i % t))
            printf("%d ", fx);
        int fir = (long long)fx * u / v;;
        int sec = fx - fir;
        fir -= (sope + q);
        sec -= (sope + q);
        e[1].push(fir);
        e[2].push(sec);
    }
    printf("\n");
    int sope = q * m;
    for(int i = 1; i <= n + m; i++) {
        int id = getMax();
        int fx = e[id].front();
        e[id].pop();
        if(!(i % t))
            printf("%d ", fx + sope);
    }
    return 0;
}