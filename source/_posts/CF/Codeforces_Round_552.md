---
title: 	Codeforces Round 552
date:		2019-04-17
author:	"zuhiul" 
tags:
  - CF
---

## F. Shovels Shop

[开启传送门](http://codeforces.com/contest/1154/problem/F)

<!-- more -->

### 题目描述

There are $n$ shovels in the nearby shop. The $i$-th shovel costs $a_i$ bourles.

Misha has to buy **exactly $k$** shovels. Each shovel can be bought **no more than once**.

Misha can buy shovels by several purchases. During one purchase he can choose any subset of remaining (non-bought) shovels and buy this subset.

There are also $m$ special offers in the shop. The $j$-th of them is given as a pair $(x_j,y_j)$, and it means that if Misha buys **exactly** $x_j$ shovels **during one purchase** then $y_j$ **most cheapest** of them are for free (i.e. he will not pay for $y_j$ most cheapest shovels during the current purchase).

Misha can use any offer any (possibly, zero) number of times, but he cannot use **more than one** offer during **one purchase** (but he can buy shovels without using any offers).

Your task is to calculate the minimum cost of buying $k$ shovels, if Misha buys them optimally.
### Input

The first line of the input contains three integers $n,m$ and $k$ ($1\leq n,m\leq 2\cdot 10^5,1\leq k\leq min(n,2000)$) - the number of shovels in the shop, the number of special offers and the number of shovels Misha has to buy, correspondingly.

The second line of the input contains $n$ integers $a_1,a_2,\dots,a_n$ ($1\leq a_1\leq 2\cdot 10^5$), where $a_i$ is the cost of the $i$-th shovel.

The next $m$ lines contain special offers. The $j$-th of them is given as a pair of integers ($x_i,y_i$) ($1\leq y_i\leq x_i\leq n$) and means that if Misha buys exactly $x_i$ shovels during some purchase, then he can take $y_i$ most cheapest of them for free.

### Output

Print one integer $-$ the minimum cost of buying $k$ shovels if Misha buys them optimally.

### Examples

#### inpus1

7 4 5

2 5 4 2 6 3 1

2 1

6 5

2 1

3 1

#### output1

7

#### input2

9 4 8

6 8 5 1 8 1 1 2 1

9 2

8 4

5 3

9 7

#### output2

17

#### input3

5 1 4

2 5 7 4 6

5 4

#### output3

17

### Note

In the first example Misha can buy shovels on positions 1 and 4 (both with costs 2) during the first purchase and get one of them for free using the first or the third special offer. And then he can buy shovels on positions 3 and 6 (with costs 4 and 3) during the second purchase and get the second one for free using the first or the third special offer. Then he can buy the shovel on a position 7 with cost 1. So the total cost is 4+2+1=7.

In the second example Misha can buy shovels on positions 1, 2, 3, 4 and 8 (costs are 6, 8, 5, 1 and 2) and get three cheapest (with costs 5, 1 and 2) for free. And then he can buy shovels on positions 6, 7 and 9 (all with costs 1) without using any special offers. So the total cost is 6+8+1+1+1=17.

In the third example Misha can buy four cheapest shovels without using any special offers and get the total cost 17.

### 题意

zuhiul 都20了，还没有对象，然后家里人给安排了n个菇凉和他相亲，他需要挑出k个来相亲。相亲当然是男方请客，和每个妹子相亲的成本是不一样的，每个妹子都有一个固定成本，为了促进zuhiul相亲，家里人说，如果一次邀约了$x_i$个菇凉，家里就给报销这次相亲的所有菇凉中，成本最低的$y_i$个菇凉的花费，现在zuhiul想花最少的钱相完所有的亲，他最少要花多少钱呢？

### 分析

首先可以确定的是，我们一定找n个中最便宜的k个来相亲，因为如果不是这k个，我们一定可以合理的交换，得到一个不劣的解。

然后排序，干掉贵的那一部分。

那么如果不考虑报销的话，成本是固定的，所以剩下的问题就是怎么得到尽可能多的报销。

然后，显然是一个$n^2$的dp了。

我们可以预处理出，如果一次约j个女孩的话，可以省掉多少个女孩的费用，设为sub[j]

假设每个女孩的费用为values[i]

考虑转移，设dp[i]表示邀约前n个妹子的最小花费，那么可以得到$$dp[i] = \min_{j=1}^{i} (dp[i-j] + \sum_{k=i-j+sub[j]+1}^{i} values[k])$$

然后对于后面的求和，可以搞一个前缀和来维护，复杂度$O(n^2)$

### 代码

给大佬递上我奇丑无比的代码　(*/ω＼*)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxk = 2005;
const int maxm = 2e5+10;
int sub[maxk];
int n,m,k;
int values[maxm];
long long sum[maxm];
int ans[maxk];
long long cost[maxk];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<=n;i++) scanf("%d",values+i);
	sort(values+1,values+n+1);
	for(int i = 1;i<=n;i++) sum[i] = sum[i-1]+values[i];
	while(m--) {/*{{{*/
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>k) continue;
		sub[a] = max(sub[a],b);
	}/*}}}*/
	for(int i = 1;i<=k;i++) sub[i] = max(sub[i],sub[i-1]);
	memset(cost,0x3f,sizeof(cost));
	cost[0] = 0;
	for(int i = 1;i<=k;i++){
		cost[i] = sum[i];
		for(int j = 1;j<=i;j++){
			cost[i] = min(cost[i],cost[i-j]+sum[i]-sum[i-j+sub[j]]);
		}
	}
	printf("%lld\n",cost[k]);
	return 0;
}
```


## G. Minimum Possible LCM

[开启传送门](http://codeforces.com/contest/1154/problem/G)

### 题目描述

You are given an array $a$ consisting of $n$ integers $a_1,a_2,\dots,a_n$.

Your problem is to find such pair of indices $i,j (1\leq i<j\leq n)$ that $lcm(a_i,a_j)$ is minimum possible.

$lcm(x,y)$ is the least common multiple of $x$ and $y$ (minimum positive number such that both $x$ and $y$ are divisors of this number).

###Input

The first line of the input contains one integer $n$ ($2\leq n\leq10^6$) — the number of elements in $a$.

The second line of the input contains $n$ integers $a_1,a_2,\dots,a_n$ ($1\leq a_i\leq 10^7$), where $a_i$ is the $i$-th element of $a$.

### Output

Print two integers $i$ and $j$ ($1\leq i<j\leq n$) such that the value of $lcm(a_i,a_j)$ is minimum among all valid pairs $i,j$. If there are multiple answers, you can print any.

### Examples

#### inpus1

5

2 4 8 3 6

#### output1

1 2

#### input2

5

5 2 11 3 7

#### output2

2 4

#### input3

6

2 5 10 1 10 2 

#### output3

1 4

### 题意

zuhiul有很多妹子，今天他想找两个妹子出去吃饭，每个妹子都有一个权值，他今天要花的钱等于这两个妹子权值的lcm，他想花尽可能少的钱，他该约哪两个妹子呢？

### 分析

我们考虑一下那种情况可以构成解。

首先对于重复的数据，我们可以干掉，因为相同值的lcm等于本身，所以我们可以把相同的权值干掉，然后剩下的数据都是不同的。

然后我们考虑权值都不相同的时候怎么构成解。

首先，这两个数肯定有一个gcd，哪怕gcd = 1，然后我们考虑一下，这$n*(n-1)>>1$这么多对数中，哪些对可以构成解，一个显而易见的想法就是，我们可以枚举gcd。

然后我们枚举这个gcd的所有倍数，这样能不重不漏的枚举出所有对数，然后我们考虑怎么减少枚举量。假设当前的$gcd=x$,因为前一步保证了没有相同的数据，所以我们只要找到最小的$i,j$使得$i\%x==0\&\&j\%x==0$，然后就用这两个数更新一下答案就行了。

### 代码

给大佬递上我奇丑无比的代码　(*/ω＼*)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm = 1e7+10;
int n;
int app[maxm];
struct p{
	long long ans;
	int ind1,ind2;
	bool operator<(const p a) const {
		return ans<a.ans;
	}
};
int main(){
	scanf("%d",&n);
	p ans = {1000000000000000000ll,-1,-1};
	for(int i = 1,buf;i<=n;i++){
		scanf("%d",&buf);
		if(app[buf]) ans = min(ans,{buf,app[buf],i});
		app[buf] = i;
	}
	for(int i = 1;i<maxm;i++){
		int buf[3] = {0};
		for(int j = i;j<maxm;j+=i){
			if(app[j]){
				buf[++buf[0]] = j;
				if(buf[0]==2){
					ans = min(ans,{1ll*buf[1]*buf[2]/i,app[buf[1]],app[buf[2]]});
					break;
				}
			}
		}
	}
	if(ans.ind1>ans.ind2) swap(ans.ind1,ans.ind2);
	printf("%d %d\n",ans.ind1,ans.ind2);
	return 0;
}
```
