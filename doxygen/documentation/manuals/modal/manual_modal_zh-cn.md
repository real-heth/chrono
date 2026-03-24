Chrono::Modal 参考手册 {#manual_modal}
=================================

为了启用此模块，用户应完成安装过程：[安装和构建 Chrono::Modal](@ref module_modal_installation)

**模态模块**提供两种主要功能：*模态分析*和*模态简化*。

## 模态分析

通过模态*分析*，用户能够提取结构和机构的振型及其对应的频率（和阻尼比）。该分析不仅可包含有限元，还能包含刚体和约束，同时也支持刚体模态。

目前提供两组主要的类来求解特征值问题：

+ *特征值求解器*，用于直接处理_纯矩阵_，它们不了解 Chrono 的 @ref chrono::ChSystem "ChSystem" 或 @ref chrono::ChAssembly "ChAssembly"，因此*不适合由普通用户直接使用*。
  所有特征值求解器:
  - 仅接受实矩阵
  - 实现移位-反演迭代方法
  - 可以处理稀疏矩阵
  - 获取最低特征值（根据移位）
  根据矩阵类型提供两种主要的求解器:
  - @ref chrono::modal::ChSymGenEigenvalueSolver "ChSymGenEigenvalueSolver" 针对对称矩阵
  - @ref chrono::modal::ChUnsymGenEigenvalueSolver "ChUnsymGenEigenvalueSolver" 针对一般矩阵
+ *模态求解器*，用于处理 Chrono @ref chrono::ChSystem "ChSystem" 或 @ref chrono::ChAssembly "ChAssembly"；它们作为接口类，通过在给定的 @ref chrono::ChAssembly "ChAssembly" 上运行 *特征值求解器* 来工作。它们可以包含阻尼。*它们是普通用户的首选*。
  模态求解器分为以下几类：
  - *undamped*: 如果 Chrono 系统生成对称矩阵，则无阻尼问题可能是对称的；根据情况，需要对称或非对称特征值求解器
  - *damped*: 包含阻尼矩阵；特征值问题始终是非对称的，因此需要适当的非对称特征值求解器

作为通用知识，Chrono 的 @ref chrono::ChSystem "ChSystem" 包含一个顶层的 @ref chrono::ChAssembly "ChAssembly"。该装配体可能包含其他装配体，从而允许仅分析（和降阶）系统中部分对象：在这种情况下，需要先将对象添加到装配体中，然后再将该装配体添加到系统中。

为了可视化模态形状，必须启用 [Irrlicht 模块](@ref irrlicht_visualization)。在这种情况下，CMake 结构将自动启用模态特定的可视化类 @ref chrono::modal::ChModalVisualSystemIrrlicht "ChModalVisualSystemIrrlicht"。由于该类是仅头文件，因此不包含在共享库中。

要运行模态分析，需要几个步骤：

- 创建一个特征值求解器，通过共享指针，例如：

  ~~~cpp
  auto eig_solver = chrono_types::make_shared<ChUnsymGenEigenvalueSolverKrylovSchur>();
  ~~~

  它必须与即将使用的模态求解器兼容

- 创建一个兼容的模态求解器
  
  ~~~cpp
  ChModalSolverDamped modal_solver(num_modes, tolerance, true, false, eig_solver);
  ~~~

- 实例化用于存储特征值和特征向量的矩阵和向量
- 调用模态求解器的求解函数
  
  ~~~cpp
  modal_solver.Solve(sys.GetAssembly(), eigvects, eigvals, freq, damping_ratios);
  ~~~

- [用于可视化] 创建一个可视化接口以可视化模态形状。模板选项应为 `double` 或 `std::complex<double>`，具体取决于特征值求解器

  ~~~cpp
  ChModalVisualSystemIrrlicht<std::complex<double>> vis;
  ~~~

- [用于可视化] **仅在** 调用 Solve 之后，从可视化接口获取结果
  
  ~~~cpp
  vis.AttachAssembly(sys.GetAssembly(), eigvects, freq);
  ~~~

- 在循环中调用常规的渲染命令：
  
  ~~~cpp
	vis.BeginScene();
	vis.Render();
	vis.EndScene();
  ~~~

  无需调用其他函数。

[demo_MOD_analysis](https://github.com/projectchrono/chrono/blob/main/src/demos/modal/demo_MOD_analysis.cpp) 展示了一种稍微复杂的用法，其中 Chrono 系统在运行过程中被动态修改。

## 模态降阶

模态降阶方法允许通过用简化版本替换给定的 Chrono 模型来减少计算量，同时保持原始系统在给定频率范围内的行为。为了利用此功能，用户必须将所有要降阶的刚体、有限元节点和约束添加到特定的 @ref chrono::modal::ChModalAssembly "ChModalAssembly" 中，而不是直接添加到系统中，方法如下：

- @ref chrono::modal::ChModalAssembly::Add() "ChModalAssembly::Add()" 用于那些被视为“边界”的对象，即位于内部（降阶）节点与外部世界之间的边界上的对象
- @ref chrono::modal::ChModalAssembly::AddInternal() "ChModalAssembly::AddInternal()" 用于那些被视为“内部”的对象，即将被降阶的对象
然后，应将 @ref chrono::modal::ChModalAssembly "ChModalAssembly" 添加到通常的 @ref chrono::ChSystem "ChSystem" 中。

通过调用 @ref chrono::modal::ChModalAssembly::DoModalReduction() "ChModalAssembly::DoModalReduction()"，Chrono 将应用转换。调用后，可以看到 ChModalAssembly 的状态数量减少，从而在模拟过程中显著提高性能。同时，ChModalAssembly 的图形外观仍将与完整模型相同：完整的内部状态确实是从降阶状态中恢复的，以便进行可视化。

*注意：目前仅支持子装配体的线性动力学，这意味着子装配体无法承受大旋转，例如直升机叶片。未来的发展将解决这个问题*

为了对装配体调用模态降阶，用户应首先构建一个模态求解器（如前一节所述），然后将其作为参数传递给 @ref chrono::modal::ChModalAssembly::DoModalReduction() "ChModalAssembly::DoModalReduction()" 方法，如 [demo_MOD_reduction](https://github.com/projectchrono/chrono/blob/main/src/demos/modal/demo_MOD_reduction.cpp) 所示。
