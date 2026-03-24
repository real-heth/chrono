
仿真系统   {#simulation_system}
=================

Chrono 系统包含了所有正在被仿真的其他对象，例如 [刚体](@ref rigid_bodies)、[连接件](@ref links) 等等。该系统是 Chrono 仿真的核心基础。

\tableofcontents

# ChSystem  {#manual_ChSystem}

Chrono 仿真系统是 ChSystem 类的一个对象。
参见 @ref chrono::ChSystem "ChSystem" 获取 API 详细信息。

请注意，ChSystem 是一个抽象类：您必须实例化其特化类之一。具体来说，您可以使用以下子类：

- @ref chrono::ChSystemNSC "ChSystemNSC" 用于 **非光滑接触** (NSC)：在接触情况下，互补性求解器将使用非光滑动力学处理它们；即使在大时间步长下，这也非常高效。
- @ref chrono::ChSystemSMC "ChSystemSMC" 用于 **光滑接触** (SMC)：接触通过罚方法处理，即接触是可变形的；

如果您的系统中不存在接触或碰撞情况，使用 ChSystemNSC 或 ChSystemSMC 并无差别。

- 一个 @ref chrono::ChSystem "ChSystem" 包含了所有参与仿真的对象：刚体、约束、数值积分器类型、积分容差等。
- 使用 ```Add()```、```Remove()``` 函数将元素添加到系统对象中。

推荐的系统对象处理方式：

- 创建一个 @ref chrono::ChSystemNSC "ChSystemNSC" 或 @ref chrono::ChSystemSMC "ChSystemSMC"
- 将 [刚体](@ref rigid_bodies) 对象添加到系统中，参见 @ref chrono::ChBody "ChBody"
- 将 [连接件](@ref links) 对象添加到系统中，参见 @ref chrono::ChLink "ChLink"
- 调整时间积分和求解器的参数
- 运行动态仿真

参见 [demo_MBS_crank](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_crank.cpp) 获取基本示例。

在大多数情况下，有三个参数需要调整：

- **时间步进器**：时间积分算法及其步长（调用 @ref chrono::ChSystem::DoStepDynamics() "DoStepDynamics()" 时）
- **求解器**：在每个时间步计算加速度和反作用力的算法；对于迭代求解器，设置适当的最大迭代次数至关重要
  例如 `my_system.GetSolver()->AsIterative()->SetMaxIterations(400);`

- **碰撞参数**

下面提供了调整这些参数的入门指南。

# 时间步进器 {#time_steppers}

时间步进器，也称为 _时间积分器_，用于推进仿真。它们执行数值积分，并推进系统状态随时间变化。
技术和理论细节可以在多个 PDF 文档中找到，这些文档可在 [白皮书页面](http://projectchrono.org/whitepapers/) 获取。例如，
[积分器白皮书](http://projectchrono.org/assets/white_papers/integrator.pdf) 解释了 Chrono 中隐式积分器的实现方式。

时间步进器可以通过两种方式更改：

- 使用 ```my_system.SetTimestepper(...)``` 函数，插入自定义时间步进器，这是用户定义的 **[推荐]**
- 使用 ```my_system.SetTimestepperType(...)``` 函数，选择一个现成的、预打包的时间步进器

示例：将时间步进器更改为隐式数值积分器

~~~{.cpp}
my_system.SetTimestepperType(ChTimestepper::Type::EULER_IMPLICIT)
~~~

时间步进器总结：

- ```EULER_IMPLICIT_LINEARIZED```
	- Chrono 中的默认时间步进器
	- 快速，无需子迭代
	- 一阶精度
	- 适用于 DVI 接触（硬接触）
	- 对 FEA 提供一阶精度
	- 使用稳定化保持约束闭合
- ```HHT```
	- 隐式积分器，基于 Hilber-Hughes-Taylor 公式
	- 通常比 INT_EULER_IMPLICIT_LINEARIZED 慢
	- 需要子迭代
	- 二阶精度，可调数值阻尼
	- 目前不能用于处理 DVI 接触的系统；即硬接触
	- 对 FEA 提供二阶精度
	- 由于内部迭代，约束被 _精确地_ 保持在闭合状态。
- ```NEWMARK```
    - 在 FEA 社区中很流行，具有与 INT_HHT 类似的属性
	- 除了某些特定参数选择（此时它变为梯形积分规则）外，它提供一阶精度

	在上文中，“一阶”或“二阶”精度的含义是全局积分误差随着时间步长的变化而趋于零（对于二阶方法，误差随时间步长的平方趋于零）。

根据所使用的时间步进器类型，可能需要调整不同的参数。
示例：

~~~{.cpp}
if (auto mystepper = std::dynamic_pointer_cast<ChTimestepperHHT>(my_system.GetTimestepper())) {
    mystepper->SetAlpha(-0.2);
    ...
}
~~~

详情请参阅 @ref chrono::ChTimestepper "ChTimestepper" API。

# 求解器 {#solvers}

求解器由时间步进器调用，用于计算每个时间步中未知的加速度和未知的反作用力。它们通常是整个仿真中最大的计算瓶颈。
求解器可以通过两种方式更改：

- 使用 ```my_system.SetSolver(...)``` 函数，插入自定义求解器，这是用户定义的 **[推荐]**
- 使用 ```my_system.SetSolverType(...)``` 函数，选择一个现成的、预打包的选项

示例：

~~~{.cpp}
my_system.SetSolverType(ChSolver::Type::PSOR);
~~~

我们推荐使用以下迭代求解器之一：

- ```PSOR```
	- 低精度：收敛可能会停滞，尤其是在奇异质量比的情况下
	- 支持 DVI（硬接触，互补性）
	- 最常用于小问题，解的精度不是特别重要

- ```APGD```
	- 非常好的收敛性，最常用于需要高精度的仿真
	- 支持 DVI（硬接触，互补性）

- ```BARZILAIBORWEIN```
    - 良好的收敛性
	- 支持 DVI（硬接触，互补性）
    - 类似于 ```APGD```，在使用大质量比时可能更稳健

- ```MINRES```
    - 良好的收敛性
    - 支持 FEA 问题
    - 目前不支持 DVI（硬接触，互补性）

- ```ADMM + PardisoMKL```
    - 支持 FEA 问题和 DVI 问题
    - 需要一个内部线性求解器；最佳选择是 ```PardisoMKL```（需要 PARDISO_MKL 模块），否则将使用 \ref chrono::ChSolverSparseQR "ChSolverSparseQR"。

在使用迭代求解器时，尤其是在系统中存在连接件/约束的情况下，**强烈建议**增加迭代次数，直到连接件不再被违反为止。可以通过以下方式实现：

~~~{.cpp}
// 更改迭代求解器的最大迭代次数
my_system.GetSolver()->AsIterative()->SetMaxIterations(400);
~~~

根据所使用的求解器类型，可能需要调整不同的参数。
高级设置无法直接从 @ref chrono::ChSystem "ChSystem" 访问，
例如：

~~~{.cpp}
if (auto msolver = std::dynamic_pointer_cast<ChSolverMINRES>(my_system.GetSolver())) {
	msolver->SetDiagonalPreconditioning(true);
}
~~~

请参阅 @ref chrono::ChSolver "ChSolver" API 以获取更多详细信息。

# 其他参数  {#other_simulation_parameters}

有许多积分器/求解器设置可能会影响仿真的结果。例如，请参阅 [碰撞容差](@ref collision_tolerances) 以更好地理解碰撞检测的精度与仿真稳健性之间的相互作用。下面我们重点介绍两个与处理仿真中物体相互碰撞和/或与地面碰撞相关的重要设置。

### 最大恢复速度 

接触中的物体由于各种原因（例如，小的数值积分误差、不一致的初始条件等）发生穿透时，其“逃离”该接触违规的速度不会超过此阈值。恢复速度通常依赖于具体问题，并由用户控制，如下所示。

~~~{.cpp}
my_system.SetMaxPenetrationRecoverySpeed(0.2);
~~~

- 较大的值允许更积极地纠正穿透，但这可能导致接触中的物体快速弹出，或者在堆叠问题中堆叠变得抖动、噪声较大
- 较小的阈值增加了当积分器精度较低时物体相互“下沉”的风险，例如，当求解器的最大迭代次数较少时

### 最小反弹速度 

当物体碰撞时，如果其入射速度低于此阈值，则假定恢复系数为零。这有助于实现堆叠物体的更稳定仿真。

~~~{.cpp}
my_system.SetMinBounceSpeed(0.1);
~~~

- 较高的值可以实现更稳定的仿真，但碰撞的物理真实性较低

- 较低的值可以实现更真实的时间演化，但需要较小的积分时间步长，否则物体可能会持续不规则地弹跳

# 理论

有关 Chrono 中实现的时间积分策略的更多信息，请参阅 [白皮书页面](http://projectchrono.org/whitepapers/)。
