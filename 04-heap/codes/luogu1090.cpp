
#include<bits/stdc++.h>
using namespace std;
struct node {
    int m;
    bool operator<(const node &a) const { //优先队列，重量小的在前
        return a.m < m;
    }
};
int n, Sum;
node Num, temp, temp1;
priority_queue<node> a;
int main() {
    Sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &Num);
        a.push(Num);
    }
    for(int i = n; i > 1; i--) {
        temp.m = 0;
        temp = a.top(), a.pop();
        temp1 = a.top(), a.pop();

        temp.m = temp.m + temp1.m;
        Sum = Sum + temp.m;
        a.push(temp);
        //cout<<"???\n";
    }
    printf("%d", Sum);
    return 0;
}