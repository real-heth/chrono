安装 DEM 模块   {#module_dem_installation}
===============================

[TOC]

Chrono::Dem 是一个可选模块，它启用了一个专门用于模拟大规模颗粒材料系统的 GPU 求解器，采用基于惩罚的离散元方法。

## 功能

**DEM 模块**允许用户构建由球形元素组成的动态系统

主要功能包括：
* 各种摩擦模型
    * 无摩擦（优化）
    * 单步伪历史
    * 多步历史跟踪
* 各种显式时间积分器
    * 前向欧拉
    * 扩展泰勒
    * 中心差分
    * [Chung](https://onlinelibrary.wiley.com/doi/abs/10.1002/nme.1620372303)
* 单 GPU 可扩展至 7 亿个无摩擦元素或 2 亿个全历史摩擦元素
* 三角网格（`obj` 格式），以便与功能更全面的求解器（如 ChSystem）进行协同仿真

## 要求

- 要 **构建** 基于此模块的应用程序，必须安装 CUDA
- 要 **运行** 基于此模块的应用程序，您需要
    - NVIDIA GPU
    - Linux 或 Windows
- 此模块已在 Windows 11 和 Linux（Ubuntu 22.04、Fedora 40 和 Arch Linux）上使用 CUDA 12.3 和 12.8 构建/测试。

## 构建说明

1. 重复 [完整安装](@ref tutorial_install_chrono) 的说明，但当您看到 CMake 窗口时，必须添加以下步骤：

2. 将 `CH_ENABLE_MODULE_DEM` 设置为 'on'，然后按 'Configure'（刷新变量列表） 

3. 再次按下 'Configure'，然后按 'Generate'，并按照安装说明继续操作。

## 使用方法

- 查看此模块的 [API 部分](group__dem__module.html) 以获取有关类和函数的文档。

- 查看 [示例](@ref tutorial_table_of_content_chrono_dem) 的 C++ 源代码，以了解如何使用此模块的函数。

## MacOS 支持

此模块无法在 MacOS 上构建，因为 Nvidia GPU 硬件和 CUDA 不受支持。
