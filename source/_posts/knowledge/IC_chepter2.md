---
title: IC(answer.chepter2)
date: 2018-12-24
author: "zuhiul"
tags:
  - IC
---

作者自己辛苦原创,如有错误or转载or其他用途请联系qq:669415029,谢谢
<!-- more -->

1.$\emptyset$ : $4^5 = 1024$.$\lbrace a\rbrace$ : $5\times 4\times 4\times 4 = 320$.$\lbrace b\rbrace$ : $5\times 5\times 5\times 2 = 250$.$\lbrace a,b\rbrace$ : $4\times 4\times 4\times 2 = 128$

2.$(13!)^4 = 1503561738404723998944447273369600000000$.

3.
$$
\left(
	\begin{matrix}
		52\\\
		5
	\end{matrix}
\right)
=2598960
$$

4.(a) $5\times 3\times 7\times 2 = 210$
(b) $620 = 2^2+3^1+5^1+7^1$,$3\times 2\times 2\times 2 = 24$
(c) $10^{10} = 2^{10} 5^{10}$,$11\times 11 = 121$

5.因为$10 = 2\times 5$,所以我们只用统计$2,5$的数量就行了,然后我们可以发现,$2$的数量显然多于$5$的数量,所以我们只用统计$5$的个数就是答案.下面给出一个通用的代码

```cpp
int cal(int a){
	int ret = 0;
	while(a) ret+=a/=5;
	return ret;
}
```

6.小数据暴力,大数据模拟
