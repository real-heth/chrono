安装 PARSERS 模块 {#module_parsers_installation}
==========================

[TOC]

Chrono::Parsers 提供了各种导入工具。

## 特性

Chrono::Parsers 模块提供了从各种基于文件的规范导入 Chrono 模型的工具。提供了以下格式的解析器：

- URDF
- OpenSim
- Adams
- Python

请参阅 [用户手册](@ref manual_parsers) 以获取更多信息。

## 依赖项

- URDF 解析器依赖于 urdfdom、urdfdom_headers、console_bridge 和 tinyxml2 库。
- Python 解析器依赖于 Python 3 以及 PythonInterp 和 PythonLibs 库。

## 构建和安装前提条件

Python 解析器的依赖项可以通过安装 Python 3 来满足。

URDF 解析器依赖于 `urdfdom` 的一些功能，这些功能尚未在其官方仓库的主分支中提供。因此，我们目前依赖于 `urdfdom` 的一个分支，该分支实现了最终将被合并到上游仓库的功能。

构建和安装 Chrono URDF 解析器所需的所有依赖项的最简单方法是使用随 Chrono 分发提供的实用脚本。
这些脚本（`buildURDF.bat` 和 `buildURDF.sh`，分别用于 Windows 和 Linux）位于 [Chrono 仓库](https://github.com/projectchrono/chrono/tree/main/contrib/build-scripts/urdf) 的 `contrib/build-scripts/urdf` 目录中。

1. 复制适当的脚本并将其放置在任意临时目录中。
2. 编辑脚本副本以：
   - 强制下载 URDF 库代码。
   - 指定安装目录（设置变量 `URDF_INSTALL_DIR`）。
   - 决定是否还要构建调试库。
3. 从脚本副本所在位置运行脚本（`.\buildURDF.bat` 或 `sh buildURDF.sh`，视情况而定）。这将创建一个临时目录，其中将克隆所有源代码仓库，并创建一组目录，用于构建各个 URDF 依赖项。
4. 安装目录将在 `URDF_INSTALL_DIR/CMake`（在 Windows 上）和子目录 `URDF_INSTALL_DIR/***/cmake`（在 Linux 上）下包含所有配置 Chrono 并启用 Chrono::Parser 模块所需的 URDF CMake 项目配置脚本。

<div class="ce-warning">
Chrono YAML 解析器依赖于第三方库 `yaml-cpp`（随 Chrono 分发提供）。
由于 yaml-cpp 中的一个错误，该第三方库无法在使用 **早于 2022** 版本的 Visual Studio 的 Windows 上构建。
如果检测到 VS 2019 或更早版本，Chrono::Parsers 模块中的 YAML 支持将被禁用。
</div>

## 构建说明

安装必要的依赖项后，执行以下步骤以配置和构建 Chrono::Parsers 模块：

1. 重复[完整安装](@ref tutorial_install_chrono)的说明。

2. 在 CMake 配置过程中，将 `CH_ENABLE_MODULE_PARSERS` 设置为 'on'，然后按下 'Configure'。

3. 当提示时，提供各个 URDF 项目配置脚本的路径（`urdfdom_DIR`、`urdfdom_headers_DIR` 和 `console_bridge_DIR`）。假设依赖项已按上述说明安装，所有这些 CMake 变量在 Windows 上应设置为 `<URDF_INSATALL_DIR>/CMake`，而在 Linux 上应分别设置为 `<URDF_INSTALL_DIR>/lib/urdfdom/cmake`、`<URDF_INSTALL_DIR>/lib/urdfdom_headers/cmake` 和 `<URDF_INSTALL_DIR>/lib/console_bridge/cmake`。

4. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
使用第三方依赖项的共享库时，必须确保在运行时能够找到这些库。<br>
在 Windows 上，可以将依赖项的 DLL 复制到可执行文件所在的目录，或者将这些共享库的路径添加到 `PATH` 环境变量中。<br>
在 Linux 上，可能需要将路径追加到 `LD_LIBRARY_PATH` 环境变量中。
</div>

## 使用方法

- 请参阅该模块的 [API 部分](group__parsers__module.html) 以获取关于类和函数的文档。

- 请参阅 [演示程序](@ref tutorial_root) 的 C++ 源代码，以了解如何使用该模块的功能。
