# Overview

需要额外安装一些东西：

`pip install canmatrix`，canmatrix用于加载和解析DBC文件。

其中文件的作用：

```bash
├── dbc                              # 实际工程中使用的dbc文件
│   ├── GeelyYHAheadRadar.dbc
│   └── MCS1FMR.dbc
├── read.py                          # 基于dbc文件读取并解析相关报文
└── write.py                         # 基于dbc文件生成并发送相关报文
```
