#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
int n;
int a[N], b[N];
priority_queue <int> Q;
void Print(int x) {
    int tmp = Q.top();
    Q.pop();
    if(x == n)  printf("%d ", tmp);
    else {
        Print(x + 1);
        printf("%d ", tmp);
    }
}
int main() {
    int flag;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)  scanf("%d", a + i);
    for(int i = 0; i < n; i++)  scanf("%d", b + i);
    for(int i = 0; i < n; i++)  Q.push(a[0] + b[i]);
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i] + b[j] < Q.top()) {
                Q.pop();
                Q.push(a[i] + b[j]);
            } else    break;
        }
    }
    Print(1);
    return 0;
}