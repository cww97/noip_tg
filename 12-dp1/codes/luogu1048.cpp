#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 10;
const int maxc = 1000 + 10;

int dp[maxc] = {0};
int v[maxn],w[maxn];
int main()
{
    int T,M;
  scanf("%d%d",&T,&M);
    for(int i = 1; i <= M; i++)
     scanf("%d%d",&v[i],&w[i]);
    for(int i = 1; i <= M; i++)
      for(int j = T; j >= v[i]; j--)
           dp[j] = max(dp[j],dp[j-v[i]] + w[i]);
    printf("%d\n",dp[T]);
    return 0;
}
