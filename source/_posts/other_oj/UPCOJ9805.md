---
title: UPCOJ 9805 Network Reliability
date:	2018-12-03
author:	"zuhiul"
tags:
  - 状压DP
---
### 题目描述
An undirected graph is given. Each edge of the graph disappears with a constant probability. Calculate the probability with which the remained graph is connected.
<!-- more -->

### 输入
The first line contains three integers N (1≤N≤14), M (0≤M≤100) and P (0≤P≤100), separated by a single space. N is the number of the vertices and M is the number of the edges. P is the probability represented by a percentage.

The following M lines describe the edges. Each line contains two integers  $ v_i $  and $ u_i $ (1≤$ u_i $ ,$ v_i $≤N). ($ u_i $ ,$ v_i $) indicates the edge that connects the two vertices $ u_i $  and$  v_i $.

### 输出
Output a line containing the probability with which the remained graph is connected. Your program may output an arbitrary number of digits after the decimal point. However, the absolute error should be  $10^{−9}$  or less.

### 样例输入
3 3 50

1 2

2 3

3 1

### 样例输出
0.500000000000

## 题意
zuhiul 和不超过14 个妹子存在着不清不楚的关系，但是他发现，有些妹子们相互之间是闺蜜，所以这些是闺蜜的妹子们有 $P$ 的概率会发现对面和zuhiul有关系从而导致关系破裂，现在问你多大的概率下，大家相安无事(妹子们还是一个联通图)．

## 分析
数据量这么小，显然状压呀．

所以我们定义

$DP[i] 表示 state==i 时，i 包含的点相互联通的概率$

那么比较容易得到答案就是	$ DP[(1<<n)-1] $

现在我们考虑转移：

​	因为要保证state内任意两点可达，所以我们不妨枚举出所有不可达的情况，容斥一下就行了．

​	所以每次对于一个state，我们可以枚举他的每个点的子集，然后对于其他点到这个集合都割掉就行了

​	你问我为什么不会重复和遗漏？

​	这就要用到神奇的构造了．

​	首先我们保证每个正确的点的子集里面都包含某一个点，那么对于包含这个点的所有正确子集来说肯定各不相同，这个保证了不会重复

​	然后怎么证明没有遗漏呢？

​	因为对于任何一个点来说，他都属于某一个联通块，我们实际上是在枚举每一个联通块，所以不会遗漏呀．

​	恩，大概就是这样，详情请看代码．

​	最后说一下复杂度．

​	应该是 $O(\sum_{i = 1}^{n} C_n^i * 2^i) = O(3^n)$


## 代码

给大佬递上我奇丑无比的代码　(*/ω＼*)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double p;
double pow_p[100];
int pow_2[100];
int mat[100][100];
void init(){
    scanf("%d%d%lf",&n,&m,&p);
    p/=100;
    pow_2[0] = 1;
    pow_p[0] = 1;
    for(int i = 1;i<100;i++) pow_p[i] = pow_p[i-1]*p,pow_2[i] = pow_2[i-1]<<1;
    for(int i = 1,from,to;i<=m;i++) {
        scanf("%d%d",&from,&to);
        mat[--from][--to]++;
        mat[to][from]++;
    }
}
const int maxm = 1<<15;
double dp[maxm];
int has[100];
int sub[100];
void get(int state){
    dp[state] = 1;
    has[0] = 0;
    for(int i = 0;i<n;i++) if(state&(1<<i)) has[++has[0]] = i;
    if(has[0]==1) return ;
    for(int now = state&(state-1);now;now = (now-1)&state){
        if((now&(1<<has[1]))==0) continue;
        sub[0] = 0;
        for(int i = 1;i<=has[0];i++) if(now&(1<<has[i])) sub[++sub[0]] = has[i];
        int cnt = 0;
        for(int i = 1;i<=has[0];i++)
            for(int j = 1;j<=sub[0];j++){
                if(now&(1<<has[i])) continue;
                cnt+=mat[has[i]][sub[j]];
            }
        dp[state]-=dp[now]*pow_p[cnt];
    }
}
int main(){
    init();
    const int nouse = pow_2[n];
    for(int i = 1;i<nouse;i++){
        get(i);
    }
    printf("%.10f\n",dp[nouse-1]);
    return 0;
}
```
