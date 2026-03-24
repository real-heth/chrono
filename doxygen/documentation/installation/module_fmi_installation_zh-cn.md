安装 FMI 模块 {#module_fmi_installation}
==========================

[TOC]

Chrono::FMI 提供对封装 Chrono 模型和/或仿真的 FMU 的创建（导出）和使用（导入）的支持。 

## 功能

功能建模接口（[FMI](https://fmi-standard.org/)）是一个免费的标准，它定义了一个容器（FMU - 功能建模单元）和一个接口，用于使用 XML 文件、二进制文件和 C 代码的组合交换动态仿真模型，这些文件以 ZIP 文件的形式分发。

`Chrono::FMI` 模块目前支持 FMI 2.0 标准，计划在未来扩展对 FMI 3.0 的支持。由于 FMI 标准在定义由 DAE 描述的模型方面的限制，Chrono 只能导出用于协同仿真的 FMU。

与其他 Chrono 模块不同，`Chrono::FMI` 不会生成新的 Chrono 库，而是提供对导出 Chrono 协同仿真 FMU 和导入 FMU 以与其他 Chrono 模型进行协同仿真的支持。

如果同时启用了 `Chrono::Vehicle` 模块，将生成几个封装车辆相关模型的 FMU 并可供使用。未来将添加新的 Chrono::Vehicle FMU。

## 要求

构建 Chrono FMI 支持没有明确的依赖项。`Chrono::FMI` 模块使用一个通用的 FMU 导出/导入工具（[fmu-forge](https://github.com/projectchrono/fmu-forge)），该工具也由 ProjectChrono 团队开发和维护，但该库作为 git 子模块使用，因此无需单独下载和安装。

<div class="ce-warning">
FMU 的自封装要求最容易通过链接静态库来满足。因此，`Chrono::FMI` 模块只能在 Chrono 配置为创建静态库时启用。此外，在 Windows 上构建带有 FMI 支持的 Chrono 时，请确保使用多线程静态链接的运行时库（Release 和 Debug 模式分别为 `/MT` 或 `/MTd`）编译 Chrono。这两个条件都可以在 CMake 配置期间设置，具体请参见下面的构建说明。
<br><br>
使用 Chrono 静态库的要求意味着并非所有 Chrono 模块都可以在启用 `Chrono::FMI` 的构建中使用。虽然这个问题将进一步研究，但目前建议不要启用任何基于 GPU 的 Chrono 模块。
<br><br>
`Chrono::FMI` 模块已在 Windows 和 Linux 上与以下其他 Chrono 可选模块一起测试：Chrono::Vehicle、Chrono::Irrlicht、Chrono::Postprocess 和 Chrono::PardisoMKL。其他模块也可能可以构建，但这需要一些实验。
<br><br>
`Chrono::FMI` 模块尚未在 MacOS 上进行测试。
</div>

## 构建说明

1. 在 CMake 配置期间，确保将 `BUILD_SHARED_LIBRARIES` 设置为 `OFF`。这将强制构建 Chrono 静态库。

2. 在 Windows 上，还要确保将 `CH_USE_MSVC_STATIC_RUNTIME` 设置为 `ON`。这将强制使用多线程静态链接的运行时库。

3. 将 `CH_ENABLE_MODULE_FMI` 设置为 `ON`。

4. 根据需要设置其他 CMake 变量，并按下/调用 `Configure`，直到满足所有 CMake 依赖项。然后按下/调用 `Generate` 以创建构建脚本。

5. 按照常规方式继续构建 Chrono。

## 使用方法

- 请参考 `fmu-forge` 的[文档](https://github.com/projectchrono/fmu-forge/blob/main/README.md)，了解导出和导入 FMU 的通用功能。

- 查看 Chrono 扩展的文档，以了解如何导出（`chrono::FmuChronoComponentBase`）和导入（`chrono::FmuChronoUnit`）封装 Chrono 模型的 FMU。

- 查看 [Chrono::FMI 示例](@ref tutorial_table_of_content_chrono_fmi) 的 C++ 源代码，以了解如何使用此模块的功能。
