# python_can

# Overview

当前项目用于记录python下使用socketcan。

python下的can可以参考文档：[Installation - python-can 4.2.2 documentation](https://python-can.readthedocs.io/en/stable/installation.html)

当前目录下：

```bash
.
├── canfd_recv.py  # 接受canfd报文
├── canfd_send.py  # 发送canfd报文
├── can_recv.py    # 接受can报文
├── can_send.py    # 发送can报文
├── asc2blf.py     # asc格式的日志文件转换成blf格式
├── blf2asc.py	   # blf格式的日志文件转换成asc格式
├── blf2log.py     # blf格式的日志文件转换成log格式
├── log2blf.py     # log格式的日志文件转换成asc格式
├── can_dbc_example # 使用dbc进行发送和解析can报文
```

**注意**:上述不同日志之间的转换代码都测试可以用，但是可能存在某些未知的问题：

1.代码转换得到的blf文件会比通过vector canoe得到的blf文件小几倍，可能略去了很多vector中自己的内容
