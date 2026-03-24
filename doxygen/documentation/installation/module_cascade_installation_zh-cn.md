安装 CASCADE 模块 {#module_cascade_installation}
==========================

[TOC]

Chrono::Cascade 是一个可选模块，利用 [OpenCASCADE](http://www.opencascade.org) 库为 Chrono 增加了对 3D CAD 文件（STEP 格式）的支持。

## 功能

**CASCADE 模块** 使用 [OpenCASCADE](http://www.opencascade.org) 开源库的功能，以便加载以 STEP 文件格式保存的 CAD 模型。

主要功能如下：

- 加载以 STEP 文件格式保存的对象形状
- 计算形状的质心、质量和惯性
- 将形状转换为用于可视化的三角网格

## 需求

- 要 **运行** 基于此模块的应用程序：
	- 必须安装 [OpenCASCADE](http://www.opencascade.org) 库。
- 要 **构建** 此模块：
	- 必须安装 [OpenCASCADE](http://www.opencascade.org) 库。

目前，Chrono API 与 OpenCASCADE **OCCT v.7.9.2** 兼容。其他版本的 OpenCASCADE *不兼容*。

## 构建说明

1. 重复 [完整安装](@ref tutorial_install_chrono) 的说明。
  
2. 将 `CH_ENABLE_MODULE_CASCADE` 设置为 'on'。

3. 如果提示，请将 `OpenCASCADE_DIR` 设置为 OpenCASCADE 项目配置脚本 (`OpenCASCADEConfig.cmake`) 所在的路径。

4. 再次点击 'Configure'，然后点击 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
在 **Windows** 上，为了使 OpenCASCADE 的 DLL 对 Chrono::Cascade 示例可见：
- 在启动示例之前，在 OpenCascade 目录中执行 `env.bat` 脚本（但仅在同一个 DOS shell 中，通过命令行），或者
- 设置路径和环境变量，使这些 DLL 在任何地方都可见。

在 **Linux** 上，您可能需要将 OpenCascade 共享库的路径添加到 `LD_LIBRARY_PATH` 环境变量中。例如：

````
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
````

在 **MacOS** 上，您必须自己构建 OpenCascade 文件夹。Homebrew 有一个 cascade 模块，但它与 chrono_cascade 不兼容。
因此，如果之前安装过，请将其删除。
在使用 CMake 配置时，请确保为 <tt>INSTALL_NAME_DIR:PATH=/opt/OCCT/lib</tt> 应用正确的值，以将 dylib 搜索路径设置为固定值。
在此示例中，OpenCascade 已安装到安装前缀 <tt>/opt/OCCT</tt>。如果您想将其安装到其他位置，请调整设置。
使用固定的 dylib 路径时，不需要在 DYLD_LIBRARY_PATH 中设置与 cascade 相关的条目。
</div>

## 如何使用

- 查看此模块的 [API 部分](group__cascade__module.html) 以获取有关类和函数的文档。

- 查看 [示例](@ref tutorial_root) 的 C++ 源代码，以了解如何使用此模块的功能。


## 故障排除

- 如果可执行文件在加载后立即挂起、冻结或崩溃，可能是因为您使用的是较旧版本的 OpenCASCADE。请卸载它，并升级到 Chrono 支持的版本（见上文），重新构建 Chrono，并在环境变量中设置正确的路径。

- 一些用户报告，即使使用正确版本的 OpenCASCADE，启动可执行文件时仍会出现类似 "missing symbol in dll" 的错误。
这很可能是因为您在某个地方已经安装了较旧版本的 OpenCASCADE，即使您不知道它的存在，这些较旧 DLL 的路径在您的 PATH 环境变量中优先。解决方案：将 OpenCASCADE DLL 的路径移动到系统 PATH 变量中所有其他路径之前。这可能是由于您安装了以下软件包：
	- 一些 Matlab 软件包，在后台使用 OpenCASCADE
	- 一些 Anaconda 软件包，在后台使用 OpenCASCADE
