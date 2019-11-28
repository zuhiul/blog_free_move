---
title: 程序对拍器
date: 2019-05-29
author: "zuhiul"
tags:
  - 模板
---

### 对拍器

```bash
g++ -std=c++11 my.cpp -o my
g++ -std=c++11 data.cpp -o data
g++ -std=c++11 ac.cpp -o ac
while true; do
	./data > in
	./my < in > my.out
	./ac < in > ac.out
	if diff my.out ac.out; then
		((var++))
		echo $var
    else
        printf "WA\n"
        exit 0
    fi
done
```
