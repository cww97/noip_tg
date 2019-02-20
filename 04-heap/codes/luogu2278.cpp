#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct node {
    int id, rea, nee, lev;
    bool operator <(const node &rhs) const {
        return lev == rhs.lev ? rea > rhs.rea : lev < rhs.lev;
    }
};
node pre;
int a, b, c, d, tnow = 0;
priority_queue<node>q;
int main() {
    while(scanf("%d %d %d %d", &a, &b, &c, &d) != EOF) {
        pre.id = a; pre.rea = b;
        pre.nee = c; pre.lev = d;
        while(!q.empty() && tnow + q.top().nee <= pre.rea) {
            node fr = q.top();
            q.pop();
            printf("%d %d\n", fr.id, fr.nee + tnow);
            tnow += fr.nee;
        }
        if(!q.empty()) {
            node fr = q.top();
            q.pop();
            fr.nee = fr.nee - pre.rea + tnow;
            q.push(fr);
        }
        q.push(pre);
        tnow = pre.rea;
    }
    while(!q.empty()) {
        node fr = q.top();
        q.pop();
        tnow += fr.nee;
        printf("%d %d\n", fr.id, tnow);
    }
    return 0;
}