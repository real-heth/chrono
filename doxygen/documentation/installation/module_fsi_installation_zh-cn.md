安装 FSI 模块 {#module_fsi_installation}
==========================

[TOC]

Chrono::FSI 是一个用于流体-固体相互作用问题建模和仿真的模块。

## 功能

**FSI 模块**允许用户：

- 使用该模块作为流体力学问题的 CFD 求解器，通过以下拉格朗日方法：
   - 隐式不可压缩 SPH (ISPH)
   - 显式弱可压缩 SPH (WCSPH)
- 使用该模块作为颗粒材料动力学的求解器，通过以下拉格朗日方法：
   - 显式弱可压缩 SPH (WCSPH)
- 使用该模块解决具有以下特征的流体-固体相互作用问题：
   - 刚体
   - 通过 ANCF 电缆和 ANCF 壳单元分别模拟的一维和二维柔性体
- 使用该模块解决刚性多体动力学及其与可变形地形的相互作用
   - 在颗粒材料地形上的漫游车/车辆机动仿真
- 使用基于 GPU 的稀疏线性求解器，如 BICGSTAB
- 使用 JSON 输入文件以便轻松指定仿真参数

## 要求

- 要 **运行** 基于该模块的应用程序，需要 NVIDIA GPU 显卡。
- 要 **构建** 该模块及其基于它的应用程序，需要安装 CUDA 并使用适当的编译器。
- 该模块已在以下环境中构建/测试：
   - Windows, MS Visual Studio 2022, CUDA 12.8.93 (Ampere GPU 架构)
   - Ubuntu 22.04 Linux, GCC 11.4, CUDA 12.8.93 (Turing GPU 架构)
   - Ubuntu 22.04 Linux, GCC 11.3, CUDA 12.3.0 (Hopper GPU 架构)
   - Ubuntu 24.04 Linux, GCC 13.3, CUDA 13.0.0 (Blackwell GPU 架构)

## 构建说明

1. 重复[完整安装](@ref tutorial_install_chrono)的说明。

2. 将 `CH_ENABLE_MODULE_FSI` 设置为 'on'。

3. 可选地，将 `CH_USE_FSI_DOUBLE` 设置为 'on'，否则将构建单精度 FSI 求解器。单精度 FSI 求解器已被测试，其精度与双精度求解器相当，但性能提高了近 2 倍。

4. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

## 使用方法

- 查看该模块的 [API 部分](group__fsi.html) 以获取有关类和函数的文档。

- 查看 [演示](@ref tutorial_table_of_content_chrono_fsi) 的 C++ 源代码，以了解如何使用此模块的功能。

## MacOS 支持

该模块无法在 MacOS 上构建，不支持 Nvidia GPU 硬件和 CUDA。
