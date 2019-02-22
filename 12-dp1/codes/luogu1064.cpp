#include <bits/stdc++.h>

using namespace std;
const int maxc = 32000 + 10;
const int maxn = 100 + 10;
typedef pair<int,int> P;

int c,m,u,p,q,tot = 0;
map<int,int> mp;
vector<P> vs[maxn];
int dp[maxc];
int main()
{
  scanf("%d%d",&c,&m);
  for(int i = 1; i <= m; i++)
   {
     scanf("%d%d%d",&u,&p,&q);
     if(q == 0)
       {
         mp[i] = ++tot;
         vs[tot].push_back(P(u,u*p));
       }
    else vs[mp[q]].push_back(P(u,u*p));
   }
  for(int i = 1; i <= tot; i++)
    for(int j = c; j >= vs[i][0].first; j--)
      {
        dp[j] = max(dp[j],dp[j - vs[i][0].first] + vs[i][0].second);
        if(vs[i].size() >= 2 && j - vs[i][0].first - vs[i][1].first >= 0) dp[j] = max(dp[j],dp[j - vs[i][0].first - vs[i][1].first] + vs[i][0].second + vs[i][1].second);
        if(vs[i].size() >= 3 && j - vs[i][0].first - vs[i][2].first >= 0) dp[j] = max(dp[j],dp[j - vs[i][0].first - vs[i][2].first] + vs[i][0].second + vs[i][2].second);
        if(vs[i].size() >= 3 && j - vs[i][0].first - vs[i][1].first - vs[i][2].first >= 0) dp[j] = max(dp[j],dp[j - vs[i][0].first - vs[i][1].first - vs[i][2].first] + vs[i][0].second + vs[i][1].second + vs[i][2].second);
      }
   printf("%d\n",dp[c]);
   return 0;
}
