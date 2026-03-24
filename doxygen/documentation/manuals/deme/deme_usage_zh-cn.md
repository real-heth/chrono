DEM-Engine 使用指南 {#deme_usage}
=================================

### 描述

DEM-Engine，昵称为 _DEME_，用于离散元方法（Discrete Element Method）模拟：

- 同时使用多达两张显卡（在消费级和数据中心级显卡上均能出色运行）。
- 粒子具有由聚合球体表示的复杂形状。
- 支持可自定义的接触力模型（想添加非标准的粘附力或静电排斥力？可以实现）。
- 强调计算效率。
- 支持与其他 C/C++ 软件包的协同仿真，例如 [Chrono](https://github.com/projectchrono/chrono)。

<p>
  <img width="380" src="https://i.imgur.com/mLMjuTc.jpg">
  <img width="380" src="https://i.imgur.com/PRbd0nJ.jpg">
</p>

目前，_DEME_ 是一个 C++ 软件包，其 API 设计与 Chrono 类似，对于现有的 Chrono 用户而言应该很容易上手。我们正在为 _DEME_ 开发 Python 接口封装。

### 示例

安装 _DEME_ 之后，你可以, 你可以开始尝试这些演示示例了。

- 一个全能的初学者示例，展示了带有刀片的搅拌器与复杂形状的颗粒的相互作用：`./src/demo/DEMdemo_Mixer`。
- 一个学习如何在此软件包中使用规定运动的地方，可以使用分析边界或颗粒表示的边界：`./src/demo/DEMdemo_Centrifuge` 和 `./src/demo/DEMdemo_Sieve`。
- 一个有趣的生命游戏模拟器，展示了如何使用此工具的灵活性：`./src/demo/DEMdemo_GameOfLife`。
- 一些在 DEM 仿真中重现的代表性工程实验，可能作为你自己的 DEM 脚本的起点：`/src/demo/DEMdemo_BallDrop`，`./src/demo/DEMdemo_ConePenetration`，`/src/demo/DEMdemo_Sieve`，`./src/demo/DEMdemo_Repose`。
- `./src/demo/DEMdemo_WheelDP` 展示了如何加载检查点配置文件以立即生成稳定的颗粒地形，然后在其上运行牵引测试。因此，此演示需要你首先完成两个 GRCPrep 演示以获取地形检查点文件。这些演示中的颗粒地形具有各种尺寸和形状的 DEM 颗粒。
- 更高级的示例展示了如何使用自定义附加属性（称为 _wildcards_），你可以将它们与仿真实体关联，并在力模型中使用它们和/或在仿真中更改它们，然后将它们存储到输出文件中：`./src/demo/DEMdemo_Indentation`。
- 建议阅读演示文件顶部的注释行，以了解每个演示的功能。

一些关于运行演示的额外故障排除提示：

- 如果在运行演示时遇到类似 `CUDA_ERROR_UNSUPPORTED_PTX_VERSION` 的错误，或者（很少）仿真在未检测到任何接触的情况下继续进行，请确保 CUDA 安装版本与代码编译时的版本相同。

### 限制

_DEME_ 旨在模拟聚合体表示的颗粒之间的相互作用、颗粒与网格表示的物体之间的相互作用，以及颗粒与分析边界之间的相互作用。

- 它能够处理具有相对简单物理的网格表示物体，例如以规定速度移动的网格犁通过颗粒材料，或几个网格投射物飞行并撞击颗粒地面。
- 然而，如果物体的物理是复杂的多体问题，例如它是一个具有关节连接部件和特定驱动策略的电机的车辆，或者网格物体之间存在需要模拟的碰撞，那么仅使用 _DEME_ 并没有处理这些问题的基础设施。但你可以将 _DEME_ 安装为库，并与其他工具（如 [Chrono](https://github.com/projectchrono/chrono)）进行耦合仿真，其中 _DEME_ 专门负责处理颗粒材料及其对外界的影响（当然是高效的）。请参见以下部分。
