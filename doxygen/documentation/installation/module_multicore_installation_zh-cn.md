安装 MULTICORE 模块 {#module_multicore_installation}
==========================

[TOC]

Chrono 的多核求解器模块。

## 特性

**MULTICORE 模块** 提供了在 Chrono 中使用共享内存并行计算进行多体仿真的功能

- 引入了自定义的 ChSystemMulticore 类
- 实现了高性能的多核碰撞检测算法
- 使用高效的并行计算 API（OpenMP、Thrust 等）

## 依赖项

- 构建基于此模块的应用程序需要：
    - [Blaze](https://bitbucket.org/blaze-lib/blaze) 库，版本 3.8。
    - [Thrust](https://github.com/thrust/thrust)（也包含在 CUDA SDK 中）。

<div class="ce-warning">
获取 Thrust 库的最简单方法是安装 CUDA SDK。
或者，你可以从其 [GitHub 仓库](https://github.com/thrust/thrust) 下载或克隆 Thrust。在这种情况下，你需要手动指定 Thrust CMake 配置脚本的路径（设置变量 `Thrust_DIR`）。
</div>

## 构建说明
  
1. 下载以下库（根据平台，过程可能有所不同）
    - [Blaze](https://bitbucket.org/blaze-lib/blaze) 库，版本 3.8
    - [Thrust](https://github.com/thrust/thrust)（也包含在 CUDA SDK 中）

    对于使用 Chrono::Multicore 模块，上述仅包含头文件的库不需要安装。然而，如果需要，它们可以安装在适当的系统目录中（在支持的平台上）。

2. 重复[完整安装](@ref tutorial_install_chrono)的说明。

3. 将 `CH_ENABLE_MODULE_MULTICORE` 设置为 'ON'。

4. 如果提示，请设置 `Blaze_ROOT_DIR` 的路径。

5. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
并非标准 _serial_ 版本的 Chrono 的所有功能都受支持。
</div>

## 使用方法

- 查看该模块的 [API 部分](group__multicore__module.html) 以获取关于类和函数的文档。

- 查看 [demos](@ref tutorial_table_of_content_chrono_multicore) 的 C++ 源代码，以了解如何使用此模块的功能。
