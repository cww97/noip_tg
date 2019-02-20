#include <bits/stdc++.h>

using namespace std;
const int maxc = 20000 + 10;
const int maxn = 30 + 10;

int v[maxn];
int dp[maxc] = {0};

int main()
{
  int V,n;
  scanf("%d%d",&V,&n);
  for(int i = 1; i <= n; i++) scanf("%d",&v[i]);
  for(int i = 1; i <= n; i++)
    for(int j = V; j >= v[i]; j--)
      dp[j] = max(dp[j],dp[j-v[i]] + v[i]);
  printf("%d\n",V-dp[V]);
  return 0;
}
