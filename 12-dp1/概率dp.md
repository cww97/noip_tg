# 概率dp

## HDU1203 I NEED A OFFER!

测试网站[HDU1203](http://acm.hdu.edu.cn/showproblem.php?pid=1203)

### 题目描述

Speakless很早就想出国，现在他已经考完了所有需要的考试，准备了所有要准备的材料，于是，便需要去申请学校了。

要申请国外的任何大学，你都要交纳一定的申请费用，这可是很惊人的。Speakless没有多少钱，总共只攒了n万美元。

他将在m个学校中选择若干的（当然要在他的经济承受范围内）。

每个学校都有不同的申请费用a（万美元），并且Speakless估计了他得到这个学校offer的可能性b。

不同学校之间是否得到offer不会互相影响。“I NEED A OFFER”，他大叫一声。

帮帮这个可怜的人吧，帮助他计算一下，他可以收到至少一份offer的最大概率。

（如果Speakless选择了多个学校，得到任意一个学校的offer都可以）。

### 题目分析

概率dp问题 ,由于概率很小，直接相乘会导致浮点数误差。所以 取对数，化乘法为加法。

### 代码示例

```c++
#include <bits/stdc++.h>
 
using namespace std;
typedef pair<int,int> P;
typedef long long LL;
const int maxn = 11000;
const int INF = 0x3f3f3f3f;
int n,v;
int vol[maxn];
double val0[maxn],val[maxn],dp[maxn];
int main()
{
    while(scanf("%d%d",&v,&n) && (v || n))
    {
    for(int i = 0; i <= v; i++) dp[i] = 0; 初始化dp 数组
    for(int i = 0; i < n; i++) scanf("%d%lf",&vol[i],&val0[i]);
    for(int i = 0; i < n; i++)  val[i] = log2(1-val0[i]);  取对数
    for(int i = 0; i < n; i++)
      for(int j = v; j-vol[i] >= 0; j--)
         dp[j] = min(dp[j],dp[j-vol[i]]+val[i]);  概率dp状态转移
    double ans = 1-pow(2,dp[v]);
    printf("%.1lf",ans*100);
    printf("%%\n");
  }
  return 0;
}
```


