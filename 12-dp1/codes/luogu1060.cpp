#include <bits/stdc++.h>

using namespace std;

const int maxm = 30;
const int maxn = 30000 + 10;

int v[maxm],w[maxm];
int dp[maxn];

int main()
{
  int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d",&v[i],&w[i]);
        w[i] *= v[i];
    }
    for(int i = 1; i <= m; i++)
      for(int j = n; j-v[i] >= 0; j--)
                dp[j] = max(dp[j],dp[j-v[i]] + w[i]);
    printf("%d\n",dp[n]);
    return 0;
}
