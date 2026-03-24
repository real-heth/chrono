安装 IRRLICHT 模块 {#module_irrlicht_installation}
==========================

[TOC]

Chrono::Irrlicht 是一个用于交互式 3D 查看 Chrono 仿真的运行时可视化系统。

## 功能

**IRRLICHT 模块**用于在交互式 3D 视图中显示 Chrono 仿真。主要功能包括：

- 支持所有在 Chrono 物理对象（刚体、连接等）上指定为 _assets_ 的可视化形状
- 支持以下默认鼠标和键盘控制：
	- 鼠标左键用于相机旋转
	- 鼠标右键用于相机 x z 方向移动
	- 鼠标滚轮用于相机前后移动
	- 按 'i' 键查看设置面板
	- 按箭头键进行 x z 方向的相机移动，按 Page Up 和 Page Down 键进行 y 方向的垂直移动
	- 按 'Print Screen' 键开始将截图保存到磁盘
- 可以选择在 3D 视图中用向量绘制接触点
- 可以在 3D 视图中绘制连接坐标系

## 依赖项

- Chrono::Irrlicht 需要 Irrlicht SDK 

## 安装前提条件

1. **下载** [Irrlicht 引擎](http://irrlicht.sourceforge.net/downloads.html)；最新测试版本为 [1.8.5](http://downloads.sourceforge.net/irrlicht/irrlicht-1.8.5.zip)

2. **解压** 到你选择的目录。例如，这里假设你将其解压到 <tt>C:/Packages/irrlicht-1.8.5</tt>。

在 Linux 上，Irrlicht 也可以通过包管理器安装：`irrlicht`、`libirrlicht-dev`、`irrlicht-devel`。

在 Mac 上安装 Irrlicht 的最佳方式是：<tt>brew install irrlicht</tt>（版本 v.1.8.5）。在 MacOS 12（Monterey）上，你必须将 IRRLICHT_INSTALL_DIR 设置为 <tt>/opt/homebrew</tt>。<br>

## 构建说明

在 [Chrono 安装页面](@ref tutorial_install_chrono) 上已经报告了如何安装 Chrono::Irrlicht 库的说明。这里将更详细地重复这些说明。
   
1. 重复[完整安装](@ref tutorial_install_chrono)的说明。
   
2. 将 `CH_ENABLE_MODULE_IRRLICHT` 设置为 'on'。
 
3. 设置 `Irrlicht_ROOT` 目录：它必须包含你解压的 Irrlicht 目录的路径。在我们的示例中，`C:/Packages/irrlicht-1.8.5`
   	 
4. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

## 使用方法

- 查看该模块的 [API 部分](group__irrlicht__module.html) 以获取有关类和函数的文档。

- 查看 [演示](@ref tutorial_root) 的 C++ 源代码，以了解如何使用此模块的功能。
