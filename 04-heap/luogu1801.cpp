/*
P1801 黑匣子  by 又白 
解法：
1.工具：一个大根堆qmax+一个小根堆qmin。
 大根堆存前i小的数，小根堆存剩下的数。
2.核心：每次get时，循环往qmax里add数，如果此时qmax超过了i个，那就pop出来扔到qmin里。
 这样循环操作之后，qmax的top一定是第i小的数。输出他！ 
3.为防止连续get，所以要在每次输出之后，再扔一个数进qmax，这样就可以应付连续get了 
*/
#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;
int a[200005];
int l=1,r,m,n;
priority_queue<int,vector<int>,greater<int> > qmin;
priority_queue<int> qmax;
int main()
{
	cin>>m>>n;
	for(int i=1;i<=m;i++)
	  scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
	  scanf("%d",&r);
	  for(int j=l;j<=r;j++){
	  	qmax.push(a[j]);
	  	if(qmax.size()>i){
		  qmin.push(qmax.top());  
		  qmax.pop();
		}
      }
	  l=r+1;
	  printf("%d\n",qmax.top());
      if(!qmin.empty()){
	   	qmax.push(qmin.top());
	    qmin.pop();
	  }
	}
	return 0;
}
