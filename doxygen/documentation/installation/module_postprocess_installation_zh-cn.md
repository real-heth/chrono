安装 POSTPROCESS 模块 {#module_postprocess_installation}
==========================

[TOC]

Chrono::Postprocess 是一个可选单元，可用于导出用于后处理仿真数据的脚本。
例如，它可以生成可以在 Blender 中加载以进行高质量逼真渲染的文件，或者在 POVray 渲染工具中使用。
它还用于输出 GNUplot 的文件。

## 特性

Chrono::Postprocess 模块用于导出数据以进行批量渲染动画等。

主要特性如下：

- Blender:
	- 导出可以在 [Blender](http://www.blender.org) 中加载的文件
	  使用 chrono_import.py 插件
	- 将 ChVisualization 资源转换为 Blender 对象
	- 使用 Blender GUI，可以添加更多对象，或通过附加纹理等修改导入的对象
	- 相机可以附加到移动对象
	- 高级功能用于导出附加到 ChTriangleMeshConnected 或有限元的标量或向量场
	  并通过伪彩色图进行渲染
	- 渲染对象参考框架、接触点、关节参考
	- 等等

- POVray:
	- 将附加到刚体的 ChVisualization 资源转换为 POVray 的渲染原语
	- 使用相同的 ChVisualization 资源，可用于 Irrlicht 接口的实时可视化
	- 允许引入自定义的 POV 特定语句
	- 相机可以附加到移动对象
	- 接触点可以在 POVray 中以彩色向量和点的形式渲染
	- 等等

- GNUplot:
	- 使用 [GNUPLOT](http://www.gnuplot.info) 创建图表
	- 从 C++ 自动启动 gnuplot
	- 从 C++ 自动创建 .gpl 脚本，使用简单的函数
	- 将图表保存到磁盘，格式为 .EPS、.PNG 或其他格式

未来我们计划支持其他类型的渲染软件，因为该系统的架构不限于 POVray。

## 依赖项

- 要 **运行** 基于此单元的应用程序，没有任何要求。
  但是请注意，您可能需要
  	- 安装 [Blender](http://www.blender.org) 以加载和渲染输出文件，如果您对 POVray 输出感兴趣，
	- 安装 [POVray](http://www.POVray.org) 以加载和渲染输出文件，如果您对 POVray 输出感兴趣，
	- 安装 [GNUPLOT](http://www.gnuplot.info) 以显示图表，如果您对 GNUPLOT 输出感兴趣。

- 要 **构建** 基于此单元的应用程序，没有任何要求。

## 构建说明

该单元对应于一个额外的共享库，称为 Chrono_postprocess，如果您想使用它，可以将其链接到您的应用程序中。
文件扩展名在 Windows 上为 .dll，在 Linux 上为 .so。

1. 重复[完整安装](@ref tutorial_install_chrono)的说明，但当您看到 CMake 窗口时，必须添加以下步骤：

2. 将 `CH_ENABLE_MODULE_POSTPROCESS` 设置为 'on'，然后按下 'Configure'（以刷新变量列表）

3. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

当您重新构建项目时，您可以在二进制目录中找到 demo_POST_xxxx，以及其他默认演示程序。 

## 使用方法

请注意，为了使用 Blender、POVray 或 GNUPLOT，必须安装它们并正确设置环境变量。

- 查看此模块的 [API 部分](group__postprocess__module.html) 以获取有关类和函数的文档。

- 查看 [演示程序](@ref tutorial_root) 的 C++ 源代码，以了解如何使用此模块的函数。
