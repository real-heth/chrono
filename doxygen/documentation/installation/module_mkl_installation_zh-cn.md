安装 Pardiso MKL 模块 {#module_mkl_installation}
==========================

[TOC]

Chrono::PardisoMKL 是一个可选模块，它暴露了来自 Intel MKL 库的直接稀疏线性求解器 Pardiso。Pardiso 的接口由 [Eigen](https://eigen.tuxfamily.org/dox/classEigen_1_1PardisoLU.html) 提供。

## 功能

实现了两个 Chrono 特定的功能：
- **稀疏模式 _锁定_**<br>
	在许多情况下，内部数据结构在时间步之间的变化很小。当发生这种情况时，通知求解器关于一致的稀疏模式可以显著加快矩阵组装。
- **稀疏模式 _学习器_**<br>
    稀疏模式学习功能提前获取稀疏模式，以加快矩阵组装。默认情况下启用，稀疏矩阵学习器识别确切的矩阵稀疏模式（而不实际设置任何非零元素）。
查看该模块的 [API 部分](group__mkl__module.html) 以获取更多详细信息。

## 依赖项

该模块需要 [Intel MKL 库](https://software.intel.com/en-us/mkl)。
请注意，Intel MKL 可以单独安装，也可以作为 Intel oneAPI [Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit.html) 的一部分安装。

- 在 Linux 上，可以使用发行版的包管理器安装 MKL 库，具体请参阅 Intel 的 [安装说明](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html?operatingsystem=linux&distributions=aptpackagemanager)。
- 在 Windows 上，请按照 Intel MKL 库的 [安装说明](https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-mkl-for-dpcpp/top.html) 进行操作。

<div class="ce-warning">
<span style="color:red; font-weight:bold">注意!</span><br>
Eigen3 尚未更新以支持 oneAPI 和 MKL 2025。<br>
已知 Intel MKL 2023 在 Linux 和 Windows 上与 Eigen（因此也与 Chrono）兼容。
</div>

## 构建说明

1. 重复[完整安装](@ref tutorial_install_chrono)的说明，但在运行 CMake 时确保选项 `CH_ENABLE_MODULE_PARDISO_MKL` 设置为 `ON`。

2. 如果提示，请将 MKL_DIR 设置为包含 MKL CMake 配置文件的目录。根据操作系统，这可能是：
    - `C:/Program Files (x86)/Intel/oneAPI/mkl/2023.0.0/lib/cmake/mkl` (Windows)
	- `/opt/intel/oneapi/mkl/latest/lib/cmake/mkl` (Linux)

3. 再次按下 'Configure'，然后按下 'Generate'

4. 构建此模块将生成一个额外的共享库，称为 **Chrono_pardisomkl**，可以将其链接到你的应用程序。

## 使用方法

### 设置环境

在创建可以实际利用 Intel MKL 库的可执行文件之前，你必须确保 Intel _运行时_ 库对可执行文件可用。这可以通过以适当的方式设置 PATH 环境变量来实现。为此，有两种方法可供选择：
+ [Intel 官方方法](https://software.intel.com/content/www/us/en/develop/documentation/onemkl-windows-developer-guide/top/getting-started/setting-environment-variables.html)；此方法仅在当前命令提示符会话中 _临时_ 设置 PATH 变量；这意味着，如果你从 Visual Studio 或新的命令提示符运行它，此方法对你来说可能困难/麻烦；
+ 非官方方法，即手动设置 PATH 变量，但 _一次性_ 设置；描述如下...

以下非官方方法需要你设置系统的环境变量。

1. 将以下 MKL 目录添加到系统 `PATH`（Windows）或 `LD_LIBRARY_PATH`（Linux 或 MacOS）环境变量中，根据你的操作系统和架构进行调整：<br>
	**对于 Windows:**<br>
	`<install_folder>/Intel/oneAPI/mkl/latest/redist/intel64`<br>
	`<install_folder>/Intel/oneAPI/compiler/latest/windows/redist/intel64_win/compiler`<br>
	或者，对于较旧的安装版本：<br>
	`<install_folder>/IntelSWTools/compilers_and_libraries/windows/redist/intel64_win/mkl`<br>
	`<install_folder>/IntelSWTools/compilers_and_libraries/windows/redist/intel64_win/compiler`.<br>
	**对于 Linux:**<br>
	`/opt/intel/oneapi/mkl/latest/lib/intel64`<br>
	`/opt/intel/oneapi/compiler/2024.0/lib/`
	
1. 添加这些系统环境变量（适用于 Windows 和 Linux）<br>
	`MKL_INTERFACE_LAYER` = `LP64`<br>
	`MKL_THREADING_LAYER` = `INTEL`<br>
	或者，更一般地，你可以根据你的架构和所需的线程层选择 [不同的选项](https://software.intel.com/en-us/mkl-linux-developer-guide-dynamically-selecting-the-interface-and-threading-layer)。

2. 重启你的 IDE，关闭任何打开的 CMake

通过这样做，你将能够直接从你的 IDE 启动基于 MKL 的演示和程序，或者只需双击它们。

### 设置代码

- 只需在运行主模拟循环之前，将此代码片段添加到您的代码中的任意位置。<br>
这将通知 Chrono 使用 Intel MKL Pardiso 求解器的 Eigen 接口。
~~~{.cpp}
auto mkl_solver = chrono_types::make_shared<ChSolverPardisoMKL>();
my_system.SetSolver(mkl_solver);
~~~


- (可选) 启用稀疏模式锁定（请参阅 @ref chrono::ChSolverPardisoMKL 和 @ref chrono::ChDirectSolverLS 以获取更多详细信息）

~~~{.cpp}
auto mkl_solver = chrono_types::make_shared<ChSolverPardisoMKL>();
mkl_solver->SetSparsityPatternLock(true);
my_system.SetSolver(mkl_solver);
~~~

- 默认情况下，此求解器使用稀疏模式学习器（请参阅 @ref chrono::ChDirectSolverLS）在实际加载非零元素之前推断稀疏模式。要禁用稀疏模式学习器，请调用

~~~{.cpp}
mkl_solver->UseSparsityPatternLearner(false);
~~~

- 查看该模块的 [API 部分](group__mkl__module.html) 以获取关于类和函数的文档。

## MacOS 支持

此模块无法在配备 Apple Silicon 硬件的 Mac 上构建，配备 Intel 硬件的 Mac 可以使用它，详见 [这里](https://www.intel.com/content/www/us/en/docs/onemkl/developer-guide-macos/2024-0/overview.html)。
