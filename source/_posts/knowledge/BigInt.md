---
title: C++ 大数
date: 2019-06-03
author: "zuhiul"
tags:
  - 模板
---

闲来无事写了一发玩玩。。。

不保证正确性。。。

<!-- more -->

```cpp
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
const int mod = 10000;
char for_cin[mod<<8];
struct bigInt {/*{{{*/
    bool neg;
    vector<int> num;
    bigInt() {
        neg = false;
    }
    bigInt(int len) {
        neg = false;
        num.resize(len);
        for(int i = 0;i<len;i++) num[i] = 0;
    }
};/*}}}*/
void relen(bigInt&a) {/*{{{*/
	int len = a.num.size();
    for(int i = len-1;i>0;i--) {
        if(a.num[i] && a.num[i-1]<0) {
            a.num[i]--;
            a.num[i-1] += mod;
        }
    }
    while(a.num.size()>=1&&a.num[a.num.size()-1]==0) a.num.resize(a.num.size()-1);
    if(a.num.size()==0) a.num.push_back(0);
}/*}}}*/
void show(bigInt a,char b = '\n'){/*{{{*/
    if(a.neg) putchar('-');
    int len = a.num.size();
    printf("%d",a.num[len-1]);
    for(int i = len-2;i>=0;i--){
        printf("%04d",a.num[i]);
    }
    cout<<b;
}/*}}}*/
bool input(bigInt & ret){/*{{{*/
    if(scanf("%s",for_cin)==EOF) return false;
    ret.num.resize(0);
    int startInd = 0;
    int len = strlen(for_cin);
    if(for_cin[0]=='-') {
        startInd = 1;
        ret.neg = true;
    }
    int i;
    for(i = len-4;i>=startInd;i-=4){
        ret.num.push_back(atoi(for_cin+i));
        for_cin[i] = '\0';
    }
    if(i!=startInd) ret.num.push_back(atoi(for_cin+startInd));
    relen(ret);
    return true;
}/*}}}*/
bigInt trans(int a){/*{{{*/
    bigInt ret(0);
    if(a<0) ret.neg = true,a = -a;
    while(a){
        ret.num.resize(ret.num.size()+1);
        ret.num[ret.num.size()-1] = a%mod;
        a/=mod;
    }
    relen(ret);
    return ret;
}/*}}}*/
bigInt trans(long long a){/*{{{*/
    bigInt ret(0);
    if(a<0) ret.neg = true,a = -a;
    while(a){
        ret.num.resize(ret.num.size()+1);
        ret.num[ret.num.size()-1] = a%mod;
        a/=mod;
    }
    relen(ret);
    return ret;
}/*}}}*/
bool equal(bigInt a,bigInt b){/*{{{*/
    if(a.neg!=b.neg) return false;
    if(a.num.size()!=b.num.size()) return false;
    int len = a.num.size();
    for(int i = 0;i<len;i++) if(a.num[i]!=b.num[i]) return false;
    return true;
}/*}}}*/
bool bigger(bigInt a,bigInt b) {/*{{{*/
    if(a.neg&&!b.neg) return false;
    if(!a.neg&&b.neg) return true;
    if(a.neg&&b.neg) {
        a.neg = b.neg = false;
        bool ret = bigger(b,a);
        a.neg = b.neg = true;
        return ret;
    }
    if(a.num.size()>b.num.size()) return true;
    if(a.num.size()<b.num.size()) return false;
    int len = a.num.size();
    for(int i = len-1;i>=0;i--){
        if(a.num[i]!=b.num[i]) return a.num[i]>b.num[i];
    }
    return false;
}/*}}}*/
bigInt add(bigInt a,bigInt b) {/*{{{*/
    bigInt ret(max(a.num.size(),b.num.size())+1);
    if(a.neg&&b.neg){
        a.neg = b.neg = false;
        ret = add(a,b);
        ret.neg = true;
        return ret;
    }
    if(a.neg){/*{{{*/
        a.neg = false;
        if(bigger(a,b)) {
            for(int i = b.num.size()-1;i>=0;i--){
                a.num[i]-=b.num[i];
                if(a.num[i]<0) {
                    a.num[i]+=mod;
                    a.num[i+1]--;
                }
            }
            relen(a);
            a.neg = true;
            return a;
        }else{
            for(int i = a.num.size()-1;i>=0;i--){
                b.num[i]-=a.num[i];
                if(b.num[i]<0){
                    b.num[i]+=mod;
                    b.num[i+1]--;
                }
            }
            relen(b);
            return b;
        }
    }/*}}}*/
    if(b.neg) return add(b,a);
    int maxlen = max(a.num.size(),b.num.size());
    a.num.resize(maxlen+1);
    int minlen = min(a.num.size(),b.num.size());
    for(int i = 0;i<minlen;i++){
        a.num[i]+=b.num[i];
        if(a.num[i]>=mod) {
            a.num[i]-=mod;
            a.num[i+1]++;
        }
        b.num[i] = 0;
    }
    relen(a);
    return a;
}/*}}}*/
bigInt sub(bigInt a,bigInt b){/*{{{*/
    b.neg = ~b.neg;
    return add(a,b);
}/*}}}*/
bigInt mul(bigInt a,bigInt b){/*{{{*/
    int lena = a.num.size();
    int lenb = b.num.size();
    int len = lena+lenb;
    bigInt ret(len);
    long long add = 0;
    for(int i = 0;i<len;i++){
        long long buf = add;
        for(int j = max(0,i-lenb+1);j<=i&&j<lena;j++) buf = buf+a.num[j]*b.num[i-j];
        add = buf/mod;
        ret.num[i] = buf%mod;
    }
    ret.neg = (a.neg!=b.neg);
    relen(ret);
    return ret;
}/*}}}*/
bigInt exec(bigInt a,int b){/*{{{*/
    bool neg = (b<0);
    bigInt ret(a.num.size());
    ret.neg = (a.neg!=neg);
    a.neg = false;
    int buf = 0;
    for(int i = a.num.size()-1;i>=0;i--){
        buf = buf*mod+a.num[i];
        ret.num[i] = buf/b;
        buf%=b;
    }
    relen(ret);
    return ret;
}/*}}}*/
bigInt exec(bigInt a,bigInt b){/*{{{*/
    bigInt base = trans(1);
    bigInt big10 = trans(10);
    bigInt big0 = trans(0);
    bigInt ans = trans(0);
    bool neg = (a.neg!=b.neg);
    a.neg = b.neg = false;
    while(bigger(a,mul(b,big10))) {
        base = mul(base,big10);
        b = mul(b,big10);
    }
    while(!equal(base,big0)) {
        while(bigger(a,b)) {
            ans = add(ans,base);
            a = sub(a,b);
        }
        b = exec(b,10);
        base = exec(base,10);
    }
    ans.neg = neg;
    return ans;
}/*}}}*/
int Mod(bigInt a,int b){
    int ret = 0;
    for(int i = a.num.size()-1;i>=0;i--){
        ret = ret*mod+a.num[i];
        ret%=b;
    }
    return ret;
}
bigInt table[mod];
int main(){
    return 0;
}
```
