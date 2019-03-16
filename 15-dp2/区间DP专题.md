# 区间dp专题

## 基本思想

区间dp一类的问题往往子问题具有很明显的区间性质,也就是说我们可以通过将子问题定义为整个区间的一个子区间.因为一个大区间可以切分成两段相邻的子区间.从这点出发,我们便可以找到递推关系.

## 1.纸牌游戏

蜘蛛牌游戏规则是这样的：只能将牌拖到比它大一的牌上面（$A$最小，$K$最大），如果拖动的牌上有按顺序排好的牌时，那么这些牌也跟着一起移动，游戏的目的是将所有的牌按同一花色从小到大排好。为了简单起见，我们的游戏只有同一花色的牌，但是这样XCX又觉得太简单了，于是他把牌数增加到了$n(1<=n<=100)$，牌随机的在一行上展开，编号从1到$n$，把第$i$号上的牌移到第j号牌上，移动距离为$abs(i-j)$，现在你要做的是求出完成游戏的最小移动距离。

### 题解

采用区间动态规划的方式，但是直接进行区间DP是没有任何意义的, 所以实际上我们需要另寻状态的定义方式.

我们需要对数列进行变化一下，我们进行dp的区间$[a,b]$定义为高度为$a$到高度为$b$的纸牌叠加到一起，所需要的最少距离和。

在一开始，我们定义数组$arr[x]$中存储的是高度为$x$的纸牌所在的位置。那么状态转移就可以写成：$dp[a][b] = dp[a][j] + dp[j+1][b] + abs(arr[b]-arr[j])$

这样的话,问题就迎刃而解了,所以说如何去定义问题是$dp$问题的一大难点和关键点.

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int a[105],n;
int dp[105][105];
 
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            a[x]=i;
        }
        for(int k=2;k<=n;k++)
        {
            for(int i=1;i<=n-k+1;i++)
            {
                int l=i,r=i+k-1;
                dp[l][r]=1e9+7;
                for(int j=l;j<=r-1;j++)
                    dp[l][r]=min(dp[l][r],dp[l][j]+dp[j+1][r]+abs(a[r]-a[j]));
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}
```

---

## 2.Multiplication Puzzle  POJ - 1651 
在一个序列中，拿走一个数字，那么得分就是这个数字以及它相邻的两个数字，这三个数字的乘积, 求最小得分。

### 题解
这道题乍一看感觉是区间DP，但是需要逆向思考的技巧。

记$dp[i][k]$表示以$i$开头的，长度$k$的区间。

我们考虑一个区间的时候，记录区间的两个端点分别为$l,r$。

这个区间两侧的端点是不能被拿走的，那么我们考虑最后一个被拿走的数字$k$，它的得分一定是区间端点的两个数和它的乘积($a[l]*a[k]*a[r]$)。

然后我们考虑区间$[l,k]$之间的情况，这个区间被拿的只剩下区间两个端点了，所以可以直接用子结构$dp[l][k-l+1]$。

同理区间$p[k,r]$也被拿的只剩下区间的两个端点了，直接用子结构$dp[k][r-l-k+1]$

这样的话递推式就非常的清晰了。

$dp[i][k] = min(dp[i][k],dp[i][j+1] + dp[i+j][k-j] + a[i]*a[i+j]*a[i+k-1])$

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 106;
int dp[MAX][MAX];
int a[MAX];
int n;
int main(){
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		cin>>a[i];
	}
	for(int k = 3;k <= n;k++){
		for(int i = 0 ;i + k <= n;i++){
			dp[i][k] = 1e9;
			for(int j = 1;j < k-1;j++){
				dp[i][k] = min(dp[i][k],dp[i][j+1] + dp[i+j][k-j] + a[i]*a[i+j]*a[i+k-1]);
			}
 
		}
	}
	cout<<dp[0][n]<<endl;
}
```

---

## 3.括号匹配问题 Brackets  POJ - 2955 
给定一个括号序列,求最长的合法括号表达式子序列.

### 题解
再明显不过的区间DP的题目了，要求求出给出符号式中最大匹配的括号数。
考虑区间$[l,r]$，如果$str[l]$与$str[r]$匹配了，那么转移方程为: 

$dp[l][r] = max(dp[l][r],dp[l+1][r-1]+ 2)$

还有一种情况就是考虑将区间分成2部分

$dp[l][r] = max(dp[l][r],dp[l][k]+dp[k+1][r])$

然后就成了，没错就这么简单

### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAX = 105;
char str[MAX];
int dp[MAX][MAX];
int mp[128];
int main(){
	mp['('] = ')';
	mp['['] = ']';
 
	while(gets(str)){
		memset(dp,0,sizeof(dp));
		if(str[0] == 'e'){
			break;
		}
		int n = strlen(str);
		for(int k = 2;k <= n;k++){
			for(int i = 0;i + k <= n;i++){//左闭右开 
				for(int j = i + 1;j < i + k;j++){
					dp[i][i+k] = max(dp[i][i + k],dp[i][j] + dp[j][i+k]);
					if(mp[str[i]] == str[i+k-1])
						dp[i][i+k] = max(dp[i][i+k],dp[i+1][i+k-1]+2);
				}
			} 
		}
		printf("%d\n",dp[0][n]);
	}
	return 0;
}
```

---

## 4.You Are the One  HDU - 4283 
题目大意就是说给定一个有序序列和一个栈，对于队伍前头的一个人，有两个操作，一个是直接迈向舞台，另一个操作就是迈入栈中。在一个时间下，迈向舞台的人可以是原始队伍里的人，也可以是栈里面的人。举例来说，假定队伍此时为 队首=>4 5<=队尾，栈此时为 栈顶=>3 2 1 <=栈底,那么下一个时刻可能是4进入栈中，或者4进入舞台，或者3从栈中去向舞台。

有$n$个人参加非诚勿扰，每个人都有$n_i$的屌丝值，如果前面有$k$个人比他早，他就会有$(k−1)*(n_i)$的不开心值，你可以让一些人进入一个小黑屋，来改变上场顺序，但是小黑屋是类似栈，先入后出。求最小不开心值.

### 题解

我们考虑如下事实：

考虑区间$[l,r]$，区间长度$k = r-l+1$。

如果区间的第一个元素可能是第$1$ 一直到第 $k$个进入舞台的，假设第一个元素是第$p$个进入舞台的$1<=p<=k$，那么我们知道第一个元素一定要先入栈，区间$[l+1,l+k-1]$中的元素一定会先第一个元素而进入舞台，这样的话，就转化到了子结构$dp[l+1][l+k-1]$中去了。

同时$[l+k,r]$中的元素一定后于第一个元素而进入舞台。他们共同要等待的耗费为$p*sum[l+k,r]$，另外还有一部分耗费为$dp[l+k][r]$

综上所述，得到转移方程

$dp[l][r] = min(dp[l][r],dp[l+1][l+k-1] + (k-1)*a[l+p-1] + p*sum[l+k,r] + dp[l+k][r])$

注意：代码中用的区间方式为左闭右开。

### 代码
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 106;
char strA[MAX];
char strB[MAX]; 
int dp[MAX][MAX];
int ans[MAX];
int n;
int main(){
	while(scanf("%s %s",strA,strB) != EOF){
		memset(dp,0,sizeof(dp));
		memset(ans,0,sizeof(ans));
		n = strlen(strA);
		for(int i = 0;i < n;i++) dp[i][i+1] = 1;
		for(int len = 2;len <= n;len++){
			for(int i = 0;i + len <= n;i++){
				dp[i][i+len] = dp[i+1][i+len] + (strB[i] == strB[i+len-1]?0:1);
				for(int j = i+1;j < i+len;j++){
					dp[i][i+len] = min(dp[i][i+len],dp[i][j]+dp[j][i+len]);
				} 
			}
		}
		ans[0] = strA[0] == strB[0] ? 0:1;
		for(int i = 1;i < n;i++){
			ans[i] = dp[0][i+1];
			if(strB[i] == strA[i])
				ans[i] = min(ans[i],ans[i-1]);
			for(int j = 0;j < i;j++){
				ans[i] = min(ans[i],ans[j] + dp[j+1][i+1]);
			}
		}
		cout<<ans[n-1]<<endl;
	}
	return 0;
}
```

---

## 5.Coloring Brackets CodeForces - 149D

题目大意：

给定合法的括号序列，让你给括弧上色，并且上色时一定要满足3个要求：
（1）每个括号要么被上红色，要么被上蓝色，要么不上色。
（2）一对匹配的左右括弧，有且只有其中的一个可以被上色。
（3）相邻的括弧不能被涂上相同的颜色。

### 题解

首先我们要进行预处理，求出每个括号的唯一配对的括号，即寻找他们一一对应的关系，这个预处理很简单，用栈操作一下就可以了

```cpp
	gets(str);
	stack<int> stk;
	int len = strlen(str);
	for(int i = 0;i < len;i++){
		if(str[i] == '('){
			stk.push(i);
		}
		else{
			int p = stk.top();
			stk.pop();
			mp[p] = i;
			mp[i] = p;
		}
	}
```

下面我们考虑的区间，全部都是配对合法的区间！

用一个四维数组dp[l][r][i][j]表示区间[l,r]且l处被涂上i色，r处被涂上j色。（规定无色为0，红色为1，蓝色为2）

那么我们可以得到下面的状态转移方程：

（1）当区间长度只有2时候（两个括弧一定是配对的，因为我们考虑的所有区间都是配对合法的区间），上色方案是非常好确定的。

$dp[l][r][0][1] = 1;$
$dp[l][r][0][2] = 1;$
$dp[l][r][1][0] = 1;$
$dp[l][r][2][0] = 1;$

（2）当区间的左右括弧是配对的时候（判断左右括弧是否匹配，用到了预处理得到的结果）。则有如下转移方法：
```cpp
if(j != 1)
dp[l][r][0][1] = (dp[l][r][0][1] + dp[l+1][r-1][i][j])%MOD;
if(j != 2)
dp[l][r][0][2] = (dp[l][r][0][2] + dp[l+1][r-1][i][j])%MOD;
if(i != 1)
dp[l][r][1][0] = (dp[l][r][1][0] + dp[l+1][r-1][i][j])%MOD; 
if(i != 2)
dp[l][r][2][0] = (dp[l][r][2][0] + dp[l+1][r-1][i][j])%MOD; 
```
（3）当区间非左右配对时，把区间划分为左右两个各自合法 的区间，转移方程是。

$dp[l][r][i][j] = (dp[l][r][i][j] + dp[l][k][i][p] * dp[k+1][r][q][j]\%MOD) \% MOD;$

这里注意$k$代表的是与l配对的括号，那么$k+1$就是与$r$配对的括号了。（这就是预处理的作用！）

而在动态规划的实现过程中，我们发现并非所有的区间都是合法的，只有少部分的区间是合法的，因此我们用自顶向下的记忆化dp的方法，这样可以简化代码的实现。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#define int long long 
using namespace std;
const int MAX = 705;
const int MOD = 1e9 + 7;
int used[MAX][MAX];
int mp[MAX];
char str[MAX];
int dp[MAX][MAX][3][3];
void dfs(int l,int r){
	if(used[l][r]) return ;
	used[l][r] = 1;
	if(l + 1 == r){
		dp[l][r][0][1] = 1;
		dp[l][r][0][2] = 1;
		dp[l][r][1][0] = 1;
		dp[l][r][2][0] = 1;
		return ;
	}
	if(mp[l] == r){//配对的情况 
		dfs(l+1,r-1);
		for(int i = 0;i < 3;i++){
			for(int j = 0;j < 3;j++){
				if(j != 1)
					dp[l][r][0][1] = (dp[l][r][0][1] + dp[l+1][r-1][i][j])%MOD;
				if(j != 2)
					dp[l][r][0][2] = (dp[l][r][0][2] + dp[l+1][r-1][i][j])%MOD;
				if(i != 1)
					dp[l][r][1][0] = (dp[l][r][1][0] + dp[l+1][r-1][i][j])%MOD;	
				if(i != 2)
					dp[l][r][2][0] = (dp[l][r][2][0] + dp[l+1][r-1][i][j])%MOD;	
			}
		}
	}
	else{
		int k = mp[l];
		dfs(l,k);
		dfs(k+1,r);
		for(int i = 0;i < 3;i++){
			for(int j = 0;j < 3;j++){
				for(int p = 0;p < 3;p++){
					for(int q = 0;q < 3;q++){
						if(p + q == 0 || p != q ){
							dp[l][r][i][j] = (dp[l][r][i][j] + dp[l][k][i][p] * dp[k+1][r][q][j]%MOD)%MOD;
						}
					}
				} 
			}
			
		} 
		 
	}
}
main(){
	gets(str);
	stack<int> stk;
	int len = strlen(str);
	for(int i = 0;i < len;i++){
		if(str[i] == '('){
			stk.push(i);
		}
		else{
			int p = stk.top();
			stk.pop();
			mp[p] = i;
			mp[i] = p;
		}
	}
	dfs(0,len-1);
	int ans = 0;
	for(int i = 0;i < 3;i++){
		for(int j = 0;j < 3;j++){
			ans = (ans + dp[0][len-1][i][j])%MOD;
		}
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 能量项链  

前置问题:石子合并, 矩阵链乘

### 问题描述
在Mars星球上，每个Mars人都随身佩带着一串能量项链。在项链上有N颗能量珠。能量珠是一颗有头标记与尾标记的珠子，这些标记对应着某个正整数。并且，对于相邻的两颗珠子，前一颗珠子的尾标记一定等于后一颗珠子的头标记。因为只有这样，通过吸盘（吸盘是Mars人吸收能量的一种器官）的作用，这两颗珠子才能聚合成一颗珠子，同时释放出可以被吸盘吸收的能量。如果前一颗能量珠的头标记为`m`，尾标记为`r`，后一颗能量珠的头标记为`r`，尾标记为`n`，则聚合后释放的能量为 `m*r*n` （Mars单位），新产生的珠子的头标记为`m`，尾标记为`n`。需要时，Mars人就用吸盘夹住相邻的两颗珠子，通过聚合得到能量，直到项链上只剩下一颗珠子为止。显然，不同的聚合顺序得到的总能量是不同的，请你设计一个聚合顺序，使一串项链释放出的总能量最大。例如：设`N=4`，`4`颗珠子的头标记与尾标记依次为`(2，3) (3，5) (5，10) (10，2)`。我们用记号?表示两颗珠子的聚合操作，`(j?k)`表示第`j, k`两颗珠子聚合后所释放的能量。则第`4, 1`两颗珠子聚合后释放的能量为：`(4?1)=10*2*3=60`。这一串项链可以得到最优值的一个聚合顺序所释放的总能量为`((4?1)?2)?3）=10*2*3+10*3*5+10*5*10=710`。 



### 输入格式

输入文件的第一行是一个正整数`N（4≤N≤100）`，表示项链上珠子的个数。第二行是`N`个用空格隔开的正整数，所有的数均不超过`1000`。第`i`个数为第`i`颗珠子的头标记`(1≤i≤N)`，当`1≤i＜N`时，第i颗珠子的尾标记应该等于第 `i+1` 颗珠子的头标记。第 `N` 颗珠子的尾标记应该等于第 `1` 颗珠子的头标记。至于珠子的顺序，你可以这样确定：将项链放到桌面上，不要出现交叉，随意指定第一颗珠子，然后按顺时针方向确定其他珠子的顺序。

### 输出格式

输出文件只有一行，是一个正整数`E(E≤2.1*10^9)`, 为一个最优聚合顺序所释放的总能量。


### 分析

`f[left][right]`表示从`left` 到 `right` 颗珠子合并所释放的最大值， 由此得方程 `f[left][right] = max{f[left,middle] + f[middle+1,right]+a[left+1]*a[middle+1]*a[right]}`。循环写起来费劲可以用记忆化搜索来写，具体见代码。

对于环的处理: 从某个点断开, 枚举断电 `i`, `ans = max(f[i][i+n-1]) for i:1 to n`.


### 源程序

```c++
#include<bits/stdc++.h>
using namespace std;
int f[310][310], a[310], n, ans;

int dp(int l,int r){
    if(f[l][r]) return f[l][r];
    if(l == r-1) return f[l][r] = a[l]*a[r]*a[r+1];
    for(int i = l; i < r; i++)
        f[l][r]=max(f[l][r], a[l] * a[i+1] * a[r+1] + dp(l, i) + dp(i+1, r));
    return f[l][r];
}

int main(){
    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        scanf("%d",&a[i]);
        a[n+i] = a[i];
    }
    a[2*n+1] = a[1];
    for(int i = 1; i <= n; i++)
        ans = max(ans,dp(i, i+n-1));
    printf("%d\n",ans);
    return 0;
}
```