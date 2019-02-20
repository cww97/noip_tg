#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define reg register
using namespace std;
const int Maxn = 5e5 + 5;
typedef long long ll;
struct dug {
    int g, val;
    bool operator <(const dug &rhs) const {
        return val < rhs.val;
    }
};
ll ans = 0, val[Maxn];
int n, k, fin = 0;
bool sbp[Maxn];
priority_queue<dug> q;
int l[Maxn], r[Maxn];
int main() {
    memset(sbp, 0, sizeof(sbp));
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        l[i] = i - 1;
        r[i] = i + 1;
        scanf("%lld", &val[i]);
        q.push((dug) {
            i, val[i]
        });
    }
    r[0] = 1; l[n + 1] = n;
    while(k--) {
        while(sbp[q.top().g])q.pop();
        dug fr = q.top();
        if(q.top().val < 0) break;
        q.pop();
        ans += fr.val;
        int id = fr.g;
        sbp[r[id]] = sbp[l[id]] = 1;
        val[id] = val[l[id]] + val[r[id]] - val[id];
        q.push((dug) {
            fr.g, val[id]
        });
        l[id] = l[l[id]]; r[l[id]] = id;
        r[id] = r[r[id]]; l[r[id]] = id;
    }
    printf("%lld", ans);
    return 0;
}