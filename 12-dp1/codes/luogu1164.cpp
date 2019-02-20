#include <bits/stdc++.h>

using namespace std;

const int maxm = 10000 + 10;
const int maxn = 100 + 10;

int a[maxn];
int dp[maxm] = {0};

int main()
{
  int n,m;
    dp[0] = 1;
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d",&a[i]);
      for(int j = m; j >= a[i]; j--)
         dp[j] += dp[j-a[i]];
     }
    printf("%d\n",dp[m]);
     return 0;
}
