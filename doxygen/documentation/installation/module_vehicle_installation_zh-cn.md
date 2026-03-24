安装 VEHICLE 模块   {#module_vehicle_installation}
===============================

[TOC]

Chrono::Vehicle 是一个模块，允许在 Chrono 中进行基于模板的地面车辆建模和仿真。

## 功能

**VEHICLE 模块**允许用户建模和仿真车辆。

有关更多详细信息，请参阅参考手册中的 [Chrono::Vehicle](@ref manual_vehicle) 部分。

## 依赖项

- 此模块没有额外的依赖项
- 使用 [CRGTerrain](@ref vehicle_terrain_crg) 功能需要 [OpenCRG](https://www.asam.net/standards/detail/opencrg/) 库。

对于运行时可视化，建议启用并安装 [Chrono::VSG](@ref module_vsg_installation) 模块和/或 [Chrono::Irrlicht](@ref module_irrlicht_installation) 模块。

## 构建和安装前提条件

Chrono::Vehicle 包含使用 OpenCRG 规范指定地形的选项。支持此可选功能需要 OpenCRG 库。

构建和安装 OpenCRG 库的最简单方法是使用 Chrono 分发版提供的实用程序脚本。
这些脚本（`buildOpenCRG.bat` 和 `buildOpenCRG.sh`，分别用于 Windows 和 Linux）位于 [Chrono 仓库](https://github.com/projectchrono/chrono/tree/main/contrib/build-scripts/opencrg) 的 `contrib/build-scripts/opencrg` 目录中。

1. 复制相应的脚本并将其放置在任意临时目录中。
2. 按照脚本顶部注释中的说明编辑脚本。
3. 从脚本副本所在的位置运行脚本（`.\buildOpenCRG.bat` 或 `sh buildOpenCRG.sh`，视情况而定）。这将创建一个临时目录，其中将克隆所有源代码仓库，并创建一组目录，用于构建各个 URDF 依赖项。
4. 安装目录将包含配置 Chrono::Vehicle 以支持 OpenCRG 所需的头文件和库文件。

## 构建说明

1. 重复[完整安装](@ref tutorial_install_chrono)的说明。

2. 将 `CH_ENABLE_MODULE_VEHICLE` 设置为 'on'。

3. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

如果启用 OpenCRG 支持（`CH_ENABLE_OPENCRG`），系统将提示您提供本地 OpenCRG 安装的位置，包括头文件、库文件的位置，以及（仅限 Windows）OpenCRG DLL 的位置。

## 使用

- 请参阅参考手册中的 [Chrono::Vehicle](@ref manual_vehicle) 部分。

- 查看此模块的 [API 部分](@ref vehicle) 以获取有关类和函数的文档。

- 查看 [演示](@ref tutorial_table_of_content_chrono_vehicle) 的 C++ 源代码，以了解如何使用此模块的功能。
