安装 MATLAB 模块 {#module_matlab_installation}
==========================

[TOC]

Chrono::Matlab 是一个简单的模块，允许通过 Chrono 中的简单 C++ 函数调用在 Matlab 环境中交换矩阵和变量。

## 功能

**Matlab 模块**用于提供一种简单的方法，从基于 Chrono 的应用程序中调用 Matlab 函数。基本上，你可以

- 从 C++ 程序中调用 Matlab 命令，
- 向 Matlab 发送/从 Matlab 检索数据（Chrono C++ 矩阵会转换为 Matlab 矩阵，反之亦然）
- 使用 Matlab 强大的可视化工具，在 2D/3D 图中显示仿真数据


## 依赖项

- 要 **运行** 基于此模块的应用程序：
	- 你必须在系统上安装了 Matlab(TM) 的授权副本。
	  我们测试了从 2006 版本到最新版本。
	- 你的 PATH 环境变量必须包含 libeng.dll 的路径（见下文）
- 要 **构建** 基于此模块的应用程序：
	- 你必须在系统上安装了 Matlab(TM) 的授权副本。
	  我们测试了从 2006 版本到最新版本。

## 构建说明

1. 重复[完整安装](@ref tutorial_install_chrono)的说明。
  
2. 将 `CH_ENABLE_MODULE_MATLAB` 设置为 'on'。

3. 设置 `Matlab_ROOT_DIR` 目录：它必须包含你安装的 Matlab 根目录的路径。
   这取决于你安装 Matlab 的位置。例如，它可能是 `C:/Program Files/MATLAB/R2019a`

4. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
在大多数情况下，当你运行使用 Matlab 模块的可执行文件时，你会收到来自 Windows 的错误消息，提示找不到 libeng.dll 库。
这意味着你必须告诉 Windows 在哪里找到它；因此你需要修改 PATH 系统变量。操作如下：
<br><br>
1. 打开你的 Matlab 编辑器，输入 <br>
  <tt>[matlabroot "\bin\win64"]</tt><br>
  （在 32 位平台上为 <tt>[matlabroot "\bin\win32"]</tt>）。
  你将获得系统上 dll 的路径。
<br><br>
2. 在 Windows 系统中设置环境变量，选择  
  开始 > 设置 > 控制面板 > 系统。  
  系统属性对话框将显示。点击高级选项卡，然后点击环境变量按钮。在系统变量面板中向下滚动，直到找到 Path 变量。点击此变量以突出显示它，然后点击编辑按钮以打开编辑系统变量对话框。在路径字符串的末尾，输入分号，然后输入在 MATLAB 中评估上述表达式返回的路径字符串。点击编辑系统变量对话框中的确定按钮，以及所有剩余的对话框。
</div>

<div class="ce-info">
在某些情况下，在 Windows 中，Matlab 引擎无法启动，因为它在安装过程中未在 COM 中注册。 
在这种情况下，当启动 "demo_MTLB_matlab.exe" 时， 
你会收到类似 "Can't start MATLAB engine" 的消息。 
要解决此问题： <br><br>
1. 打开你的 Matlab 编辑器，  <br>
2. 输入 `!matlab -regserver`
</div>

## 使用方法

- 查看该模块的 [API 部分](group__matlab__module.html) 以获取有关类和函数的文档。

- 查看 [演示](@ref tutorial_table_of_content_chrono_matlab) 的 C++ 源代码，以了解如何使用此模块的功能。
