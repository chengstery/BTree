# 数据结构课程设计：文献管理系统

## Graphviz 文件夹

Graphviz 文件夹下放的工具用于生成可视化的B树图片

tree.dot 用于解析的 .dot 文件，解析后可得到树的可视化图片 tree.png

使用例子
```c
system("./Graphviz/bin/dot -Tpng ./tree.dot -o ./tree.png");
```
## BTree_GUI 文件夹

BTree_GUI文件夹下放有可直接运行的BTree_GUI.exe，BTree_GUI.exe 是经过了CLion编译后的图形化界面版可执行程序, BTree_GUI.exe的运行还依赖于 
```
libgcc_s_seh-1.dll  libstdc++-6.dll  libwinpthread-1.dll
```
这三个文件已在BTree_GUI.exe所在目录放置

## SourceCode 文件夹

SourceCode 文件夹下放了所有功能实现的源文件和头文件，这些代码都是在CLion的MinGW编译器实现的，因此不能保证在其他编译器能正常运行(在其他编译器需要经过小修改可能才能编译)。

## data.dat 和 log.txt

data.dat是用于保存和加载文献信息的二进制文件

log.txt是用于记录每次操作情况的日志文件

