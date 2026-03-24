安装 MODAL 模块 {#module_modal_installation}
==========================

[TOC]

Chrono::Modal 通过利用稀疏矩阵的迭代移位反演特征值求解器，实现了对大型 Chrono 系统的 **模态分析** 和 **模态简化**。

该模块的扩展描述可在 [Chrono::Modal](@ref manual_modal) 用户手册中找到。

## 依赖项

- 构建基于此模块的应用程序需要：
	- [Spectra](https://spectralib.org/) 库

- 运行基于此模块的应用程序没有额外的要求

## 构建说明

1. 从 GitHub 页面下载 [Spectra](https://spectralib.org/) 库。你可以选择下载源代码的 zip 文件，或者克隆 git 仓库。
   **注意** 我们需要 Spectra 库的开发版本，因为只有该版本包含 Krylov-Schur 求解器。因此，请使用此链接：[https://github.com/yixuan/spectra/tree/develop](https://github.com/yixuan/spectra/tree/develop)

2. 重复[完整安装](@ref tutorial_install_chrono)的说明。
  
3. 将 `CH_ENABLE_MODULE_MODAL` 设置为 'ON'。

4. 将 `SpectraINCLUDE_DIR` 设置为 Spectra 安装中包含目录的路径。例如，它可以是 `C:/Packages/spectra/include`。

5. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-info">
Spectra 的 `develop` 分支正在开发中。在构建过程中，你可能会收到一些警告。
</div>

<div class="ce-info">
在等待未来版本的 Spectra 在 Krylov-Schur 求解器中启用复特征值时，对于阻尼复模态分析的情况，将使用更传统的求解器。更传统的求解器不是稀疏的，因此预计会占用更多的 CPU 时间和内存。通常的模态分析已经使用 Krylov-Schur，因此可以支持大型问题。
</div>

## 使用方法

- 查看该模块的 [API 部分](group__modal__module.html) 以获取关于类和函数的文档。

- 查看 [demos](https://github.com/projectchrono/chrono/tree/main/src/demos/modal) 的 C++ 源代码，以了解如何使用此模块的功能。
