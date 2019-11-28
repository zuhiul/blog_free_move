---
title: mac下监听全局键盘输入
date: 2019-08-04
author: "zuhiul"
tags:
  - 体验优化
---

因为这段时间终于狠下心来买了把键盘。然后这两天脑子里面全是如何统计键盘敲击次数，在我踩了几个坑之后，终于搞定了，这里总结一下。

首先就是mac下不支持pyhook，貌似，所以只能用pynput来瞎搞。安装各种依赖就不说了。

首先一个坑点就是，mac为了安全考虑，拒绝一般的程序监听键盘和鼠标等外设的输入。

然后我就想办法给python权限，“系统偏好设置->安全性与隐私->完全磁盘访问权限”，给权限整上了，但是我发现一个比较尴尬的事是：依然是跑不起来。然后就各种寻求帮助。

后来发现是要在sudo下运行，我试了一下，还是不行。

最后才发现，需要的权限名字不叫“完全磁盘访问权限”，而是“辅助功能”，服了。我的理解是：你丫都有完全的磁盘访问权限了，还没有辅助功能？开玩笑呢？

啊，我死了。

这里贴上我抄的代码

```python
from pynput import keyboard


def on_press(key):
    with open('out', 'a+') as f:
        try:
            f.write(str(key.char) + '\n')
        except AttributeError:
            f.write(str(key) + '\n')
        f.close()


def on_release(key):
    pass


# Collect events until released
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
```
