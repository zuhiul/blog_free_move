---
title: 	Codeforces Round 553
date: 		2019-04-19
author: 	"zuhiul"
tags:
  - CF
---

## F. Sonya and Informatics

[开启传送门](https://codeforces.com/contest/1151/problem/F)

<!-- more -->

### 题目描述

A girl named Sonya is studying in the scientific lyceum of the Kingdom of Kremland. The teacher of computer science (Sonya's favorite subject!) invented a task for her.

Given an array $a$ of length $n$, **consisting only of the numbers** $0$ **and** $1$, and the number $k$. Exactly $k$ times the following happens:

 - Two numbers $i$ and $j$ are chosen equiprobable such that ($1\leq i<j\leq n$).
 - The numbers in the $i$ and $j$ positions are swapped.

Sonya's task is to find the probability that after all the operations are completed, the $a$ array will be **sorted in non-decreasing order**. She turned to you for help. Help Sonya solve this problem.

It can be shown that the desired probability is either $0$ or it can be represented as $\frac{P}{Q}$, where $P$ and $Q$ are coprime integers and $Q\not\equiv0(mod\ 10^9+7)\textscA$.

### Input

The first line contains two integers $n$ and $k$ ($2\leq n\leq 100,1\leq k\leq 10^9$) — the length of the array $a$ and the number of operations.

The second line contains $n$ integers $a_1,a_2,\dots,a_n$ ($0\leq a_i\leq 1$) — the description of the array $a$.

### Output

If the desired probability is $0$, print $0$, otherwise print the value $P\cdot Q^{-1}$ ($mod\ 10^9+7$), where $P$ and $Q$ are defined above.

### Examples

#### inpus1

3 2

0 1 0

#### output1

333333336

#### input2

5 1

1 1 1 0 0

#### output2

0

#### input3

6 4

1 0 0 1 1 0

#### output3

968493834

### Note

In the first example, all possible variants of the final array $a$, after applying exactly two operations: $(0,1,0)$, $(0,0,1)$, $(1,0,0)$, $(1,0,0)$, $(0,1,0)$, $(0,0,1)$, $(0,0,1)$, $(1,0,0)$, $(0,1,0)$. Therefore, the answer is $\frac{3}{9}=\frac{1}{3}$.

In the second example, the array will not be sorted in non-decreasing order after one operation, therefore the answer is 0.

### 题意

给你一个长度为n的01序列，每次随机从中选择两个出来，交换一下，一共这样操作k次，问你经过k次交换之后，序列变成不降($00\dots 0011\dots 11$)的概率是？

### 分析

首先序列里面的$0$和$1$的数量是固定的，不妨设分别有$len_a$和$len_b$个。

也就是说在交换$k$次之后要保证前$len_a$个为$0$，后$len_b$个为$1$,如下
$$\underbrace{00\dots 00}_{len_a} \underbrace{11\dots 11}_{len_b}$$

然后我们分别统计前半段后半段$0$和$1$的数量，分别定义为$a_0,a_1,b_0,b_1$。例如
$$\underbrace{\underbrace{\overbrace{01010000101110100}^{a_1=7}}_{a_0=10}}_{len_a=17}\underbrace{\underbrace{\overbrace{000101111101010}^{b_1=8}}_{b_0=7}}_{len_b=15}\tag{3}$$

然后考虑一次交换产生的效果：

- $b_1$增加：$a_1$和$b_0$交换，使得后半段多了一个1，例如
$$\underbrace{\underbrace{\overbrace{01010000101110000}^{a_1=6}}_{a_0=11}}_{len_a=17}\underbrace{\underbrace{\overbrace{010101111101010}^{b_1=9}}_{b_0=6}}_{len_b=15}\tag{2}$$

- $b_1$减少：$a_0$和$b_1$交换，使得后半段少了一个1，例如
$$\underbrace{\underbrace{\overbrace{01010000101110101}^{a_1=8}}_{a_0=9}}_{len_a=17}\underbrace{\underbrace{\overbrace{000101111101000}^{b_1=7}}_{b_0=8}}_{len_b=15}\tag{1}$$

- 其他情况不影响$0$和$1$的数量。

然后多次操作和一次操作怎么联系起来呢？

看到这个数据量$n = 100$，一次变多次，一个自然的想法就是快速幂啊啊啊啊啊啊啊啊啊啊。

然后就用上面的式子构造转移矩阵，然后快速幂，就能得到有解的方案数，然后除掉总方案数就行了。

### 代码

给大佬递上我奇丑无比的代码　(*/ω＼*)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
long long add(long long a,long long b){return (a+b)%mod;}
long long mul(long long a,long long b){return a*b%mod;}
long long qpow(long long a,long long b = mod-2){/*{{{*/
	long long ret = 1;
	while(b){
		if(b&1) ret = mul(ret,a);
		a = mul(a,a);
		b>>=1;
	}
	return ret;
}/*}}}*/
const int maxm = 105,inv_2 = qpow(2);
long long C(long long a){
	return mul(inv_2,mul(a,add(a,mod-1)));
}
int n,k,len_a,len_b;
int num[maxm];
struct matrix{
	long long num[maxm][maxm];
};
matrix mul(matrix a,matrix b){/*{{{*/
	matrix c;
	memset(c.num,0,sizeof(c.num));
	for(int i = 0;i<=len_b;i++) for(int j = 0;j<=len_b;j++)
			if(a.num[i][j])
				for(int k = 0;k<=len_b;k++) c.num[i][k] = add(c.num[i][k],mul(a.num[i][j],b.num[j][k]));
	return c;
}/*}}}*/
matrix qpow(matrix a,long long b){
	matrix e;
	for(int i = 0;i<=len_b;i++) for(int j = 0;j<=len_b;j++) e.num[i][j]=(i==j);
	while(b){
		if(b&1) e = mul(e,a);
		a = mul(a,a);
		b>>=1;
	}
	return e;
}
int main(){
	scanf("%d%d",&n,&k);
	int all = C(n);
	for(int i = 0;i<n;i++){/*{{{*/
		scanf("%d",num+i);
		if(num[i]) len_b++;
		else len_a++;
	}/*}}}*/
	matrix base;
	for(int i = 0;i<=len_b;i++){
		for(int j = max(0,i-1);j<=min(len_b,i+1);j++){
			int b1 = j,b0 = len_b - j,a0 = len_a - b0,a1 = len_a - a0;
			if(i==j-1) base.num[i][j] = a0*b1;
			else if(i==j+1) base.num[i][j] = a1*b0;
			else base.num[i][j] = add(all,add(mod - a0*b1,mod - a1*b0));
		}
	}

	int cnt = 0;
	for(int i = len_a;i<n;i++) if(num[i]) cnt++;
	matrix ano;
	memset(ano.num,0,sizeof(ano.num));
	ano.num[cnt][0] = 1;

	base = mul(qpow(base,k),ano);

	long long ans = base.num[len_b][0];
	ans = mul(ans,qpow(qpow(C(n),k)));
	printf("%lld\n",ans);
	return 0;
}
```


