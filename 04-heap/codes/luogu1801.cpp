#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;
int a[200005];
int l = 1, r, m, n;
priority_queue<int, vector<int>, greater<int> > qmin;
priority_queue<int> qmax;
int main() {
  cin >> m >> n;
  for(int i = 1; i <= m; i++)
    scanf("%d", &a[i]);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &r);
    for(int j = l; j <= r; j++) {
      qmax.push(a[j]);
      if(qmax.size() > i) {
        qmin.push(qmax.top());
        qmax.pop();
      }
    }
    l = r + 1;
    printf("%d\n", qmax.top());
    if(!qmin.empty()) {
      qmax.push(qmin.top());
      qmin.pop();
    }
  }
  return 0;
}