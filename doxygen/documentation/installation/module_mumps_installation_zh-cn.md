安装 MUMPS 模块 {#module_mumps_installation}
==========================

[TOC]

Chrono::Mumps 是一个可选模块，使 Chrono 能够使用 MUMPS 线性求解器。

Chrono 通常依赖其 [内置求解器](@ref solvers)，其良好的性能通过利用内部数据结构得到保证。
实际上，对于广泛的应用，这些求解器已经足够。<br>
然而，对于更高精度的结果，仍然可能需要直接求解器。

该模块提供了一个与第三方 MUMPS 求解器的接口。

## 特性

Chrono::Mumps 模块允许将 MUMPS 求解器集成到 Chrono 中，并提供两种接口：

- 一个面向 Chrono 的接口，即 @ref chrono::ChSolverMumps<>，**不**打算直接由用户使用。<br>
这是用户应当在 Chrono 环境中使用的接口。
- 一个面向最终用户的接口，即 @ref chrono::ChMumpsEngine，允许直接使用 Chrono 数据类操作 MUMPS（如果用户有此需求）。<br>
demo_MUMPS_MumpsEngine.cpp 展示了其用法，但普通用户通常不需要关注它。

查看该模块的 [API 部分](group__mumps__module.html) 以获取更深入的讨论。

## 构建和安装前提条件

Chrono::Mumps 模块需要 [MUMPS](http://mumps.enseeiht.fr) 库。
Mumps 不提供基于 CMake 的安装系统。为了解决这个问题，我们提供了一组实用脚本（随 Chrono 源代码一起提供），这些脚本可以下载 Mumps 源代码，构建所有必要的库，并将它们安装到用户指定的位置。

这些脚本（`buildMUMPS.bat`、`buildMUMPS.sh` 和 `buildMUMPS_Mac.sh`，分别用于 Windows、Linux 和 MacOS）位于 [Chrono 仓库](https://github.com/projectchrono/chrono/tree/main/contrib/build-scripts/mumps) 的 `contrib/build-scripts/mumps` 目录中。

1. 复制适当的脚本并将其放置在任意临时目录中。
2. 编辑脚本副本以：
   - 强制下载源代码。
   - 指定安装目录（设置变量 `MUMPS_INSTALL_DIR`）。
   - 决定是构建共享库还是静态库，以及是否还要构建调试库。
3. 从脚本副本所在位置运行脚本（`.\buildMUMPS.bat` 或 `sh buildMUMPS.sh`，视情况而定）。这将创建一个临时目录，其中将克隆所有源代码仓库，并创建一组目录，用于构建各个 VSG 依赖项。
4. 安装目录将在 `MUMPS_INSTALL_DIR/cmake/` 下包含所有配置 Chrono 并启用 Chrono::Mumps 模块所需的 CMake 项目配置脚本。

## 构建说明

1. 安装 MUMPS 库（见上文）

2. 重复[完整安装](@ref tutorial_install_chrono)的说明。

3. 将 `CH_ENABLE_MODULE_MUMPS` 设置为 'ON'。

4. 设置 CMake 变量 `MUMPS_DIR` 指向包含 MUMPS CMake 项目配置脚本的目录
   (例如，`C:/Packages/mumps/cmake`)。

5. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
如果使用 Intel oneAPI Fortran 编译器，`ifort` 在最新版本的 oneAPI 中已被 `ifx` 取代。 
<br>
为了确保 CMake 使用正确的 Fortran 编译器，请在调用 CMake 时显式指定它，传递 `-T fortran=ifx`（当然，这假设您已正确配置 Intel oneAPI 并且 `ifx` 在搜索路径中）。
</div>

## 使用方法

- 只需在代码中的任意位置添加此代码片段，在运行主仿真循环之前。<br>
这将通知 Chrono 使用 MUMPS 求解器的接口。

~~~{.cpp}
auto mumps_solver = chrono_types::make_shared<ChSolverMumps>();
my_system.SetSolver(mumps_solver);
~~~

- （可选）启用稀疏模式锁（参见 @ref chrono::ChSolverMumps 和 @ref chrono::ChDirectSolverLS 以获取更多详细信息）

~~~{.cpp}
auto mumps_solver = chrono_types::make_shared<ChSolverMumps>();
mumps_solver->SetSparsityPatternLock(true);
my_system.SetSolver(mumps_solver);
~~~

- 默认情况下，该求解器使用稀疏模式学习器（参见 @ref chrono::ChDirectSolverLS）在实际加载非零元素之前推断稀疏模式。要禁用稀疏模式学习器的使用，请调用

~~~{.cpp}
mumps_solver->UseSparsityPatternLearner(false);
~~~

- 查看该模块的 [API 部分](group__mumps__module.html) 以获取关于类和函数的文档。
