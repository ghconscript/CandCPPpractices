# C 语言企业软件开发实践

## 在 windows 平台使用 MinGW 环境编译运行

### 安装 mingw 环境

参考《1-C 语言编程实践环境搭建说明书.docx》

### 确保 gcc 可用

在 windows 命令行下输入 where gcc 命令，可以查看 gcc 的安装路径:
如果有多个 gcc 版本，请修改系统环境变量 PATH，使得 PATH 中指向的 gcc 路径是你期望的版本。

### 编译方法

```shell
# windows
script\build_and_run.bat
```

也可以分步骤编译运行：

```shell
cd /d D:\c-training-adas
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make -j
```

> 如果嫌每次这样输入麻烦，可以通过环境变量的方式修改默认 generator，修改方法：cmake 3.15 及以后版本，在系统变量中，新建 CMAKE_GENERATOR ，值为 MinGW Makefiles。
> 设置后，可以这样查询：
> D:\>set CMAKE_GENERATOR
> CMAKE_GENERATOR=MinGW Makefiles

## 在 linux 环境下编译运行

```shell
# linux/macos
chmod +x script/build_and_run.sh
bash script/build_and_run.sh
```
