# 字符串初阶


对于初阶字符串问题而言，我们最常用的莫过于KMP问题，因此本章会整理一些有关于KMP的题型，并且总结其中的规律与问题


## 洛谷 P3375 KMP字符串匹配
https://www.luogu.org/problemnew/show/P3375

题目大意：给定两个字符串s1 和 s2 ，其中 s2 为s1的子串，求出s2 在s1中所有出现的位置，并输出子串的前缀数组next

题目分析：这道题就是KMP的一个经典的模板题型，通过kmp算法先求出next数组，然后对模式串和目标串进行匹配。最后确定出现位置即可

代码
https://paste.ubuntu.com/p/DTg99Hk8Ry/

## 洛谷 P4391 无线传输
https://www.luogu.org/problemnew/show/P4391

题目大意：给定一个字符串，求该字符串的最小循环节

题目分析：这个题目就是next 数组的一个应用了。我们知道一个结论 n - next [ n ] = t，t 就是循环节了的长度了

代码：
https://paste.ubuntu.com/p/PnBtq6wjTQ/

## uva 1328  
https://www.luogu.org/problemnew/show/UVA1328

题目大意：给定一个字符串，求该字符串的最小循环节 

题目分析： 这个题和上面那个题是同一种题目，主要考点还是在next数组的应用上面

代码
https://paste.ubuntu.com/p/67qP8Njmv4/

## 洛谷P3435 [POI2006]OKR-Periods of Words

https://www.luogu.org/problemnew/show/P3435

题目大意：给定一个字符串，对于每一个前缀，求它的最长前缀，使其重复后能够覆盖原串

题目分析：这道题目也是基于next数组的一个分析的过程，我们要使某个前缀重复以后能够覆盖整个串，我们只要求出当前子串的前缀=后缀的最短的匹配长度，那么剩余长度就是我们要求的最长前缀。
那么怎么求最短的匹配长度呢？

next[i] 表示当前匹配的最长前缀和后缀相等
我们只需要继续求 next[next[i]]的话，也就是依然满足前缀=后缀的情况。只要一直求，求到0为止，就可以得出最短的匹配长度了

代码：https://paste.ubuntu.com/p/6VsRgDj2QQ/

## 洛谷 P2375 [NOI2014]动物园

https://www.luogu.org/problemnew/show/P2375

题目大意：这道题目要求前缀与后缀相等但不重叠的长度，记做num[i]，求 （num[i]+1)的乘积

题目分析：
这个题类似我们刚才求最短长度的做法，我们不断的求next[i]，只要满足2\*next[i]<n的话，这就是我们要求的长度了，然而这样做的话，复杂度会比较高 O(n\*L\*log(L)) 会TLE
所以，我们要直接写出递推解，这里考虑KMP的做法，我们在计算再跑一次next数组的求法，就可以解决这个问题了

代码：https://paste.ubuntu.com/p/bZqRSkwHtY/

## codeforces 126B password

http://codeforces.com/contest/126/problem/B

题目大意：给定一个字符串，找出其中一个最长的子串，使得这个子串既是前缀又是后缀又在中间出现

题目分析：我们看到前后缀很自然的可以想到Kmp中的next数组，那么如何处理是否在中间呢？我一开始构建了一个s除去头尾的子串，试图在其中用find函数去查找是否存在这样的串，很显然这样的复杂度是很高的，会T，我们可以发现，我们在求next的数组的时候，就是求最长前缀后多少个，因此，我们只要记录除了最后一个字符意外的前面的最长前缀的情况，也就是除去后缀之后，前缀和中间出现的又构成的一个前后缀，我们只要找到满足这样条件的子串即可。

代码
https://paste.ubuntu.com/p/RHJfnF8z4Q/