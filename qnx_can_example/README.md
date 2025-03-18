# qnx_can_example

该文件用于测试简单的qnx上的can操作

目录结构如下：

```bash
├── can_app.cpp  模仿域控上的can_app，主要用于对can接口进行操作
├── can_dcmd.h 操作can接口需要用到的头文件，正常使用的是qnx系统提供的<sys/can_dcmd.h>
├── canfd_dcmd.h 操作canfd接口需要用到的头文件
├── canfd_read.cpp 读取canfd数据
├── canfd_write.cpp 写canfd数据
├── can_read.cpp 读取can数据
├── can_write.cpp 写can数据
├── CMakeLists.txt
├── conanfile.py
├── qnx.toolchain.cmake 交叉编译的toolchain文件
└── README.md
```
