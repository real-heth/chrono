轮胎模型 {#wheeled_tire}
===========================

\tableofcontents

Chrono::Vehicle 目前支持三种不同类型的轮胎模型：刚性轮胎、操控轮胎和有限元轮胎。

## 刚性轮胎模型 {#wheeled_tire_rigid}

刚性轮胎是三种轮胎模型中最简单的一种。这些模型假设轮胎是完全刚性的，并且通过与 Chrono 中其他刚体相同的摩擦和接触算法与地面和其他刚体进行交互。这些轮胎的接触几何形状可以简单如圆柱体，也可以复杂如三维三角网格。这些模型不仅适用于调试整体车辆模型，还可以在运行时间重要、地形远比轮胎软且不需要高度详细的轮胎模型的情况下使用。实际上，半经验轮胎模型不适用于越野车辆仿真，即在使用可变形地形（SCM、颗粒或基于 FEA 的地形；参见可用的[地形模型](@ref vehicle_terrain)描述）时。对于这种情况，刚性或基于 FEA 的轮胎模型是目前 Chrono::Vehicle 中唯一可用的两种选择。

参见 [ChRigidTire](@ref chrono::vehicle::ChRigidTire) 和 [RigidTire](@ref chrono::vehicle::RigidTire)。

以下是一个通过 Wavefront OBJ 文件提供网格几何的刚性轮胎示例：
\include "data/vehicle/hmmwv/tire/HMMWV_RigidMeshTire.json"

## 操控（半经验）轮胎模型 {#vehicle_tire_empirical}

第二类轮胎模型是常用于车辆操控的半经验模型。Chrono::Vehicle 目前实现了 Pacejka（89 和 2002）、TMeasy 和 Fiala 轮胎模型。操控轮胎模型设计用于平坦路面，通常使用单点接触或四点接触（TMeasy）。对于在起伏路面上的行驶测试或障碍物跨越，已经实现了一种称为“包络”的特殊接触算法。它基于 Sui & Hershey 的论文，并且可以与 Chrono 中包含的所有操控轮胎模型一起使用。使用技术演示器进行的验证测试显示，与实际车辆测试数据相比，数值计算量低且结果良好。如果需要更高的精度，用户应考虑在非操控测试中使用基于 FEA 的轮胎模型。

一些用户可能希望根据轮胎测试数据构建自己的操控轮胎参数集。请确保熟悉每种轮胎模型中的不同滑移定义和不同坐标系！

### Pacejka 89 (Pac89) 轮胎模型 {#wheeled_tire_pac89}

参见 [ChPac89Tire](@ref chrono::vehicle::ChPac89Tire) 和 [Pac89Tire](@ref chrono::vehicle::Pac89Tire)。

### Pacejka 2002 (Pac02) 轮胎模型  {#wheeled_tire_pac02}

该模型是 Pacejka 早期魔术公式轮胎模型的扩展，增加了额外的方程和系数。由于大量车辆动力学操作不在稳态滑移条件下发生，因此包括接触补丁滑移状态方程以在瞬态条件下提供更准确的结果。由于缺乏参考数据集，实际上未实现充气压力依赖项和大倾角项。

该 Chrono 轮胎模型也可以使用与 Adams/Car 兼容的 TIR 文件进行指定。

参见 [ChPac02Tire](@ref chrono::vehicle::ChPac02Tire) 和 [Pac02Tire](@ref chrono::vehicle::Pac02Tire)。

### TMeasy 轮胎模型（基础版本） {#wheeled_tire_tmeasy}

TMeasy (Tire Model Made Easy) 由 Georg Rill 教授开发，并作为商业代码提供（更多信息请[参见](http://www.tmeasy.de/)）。该模型的目的是允许轻松参数化。其复杂性大致与基于魔术公式的模型相当。此外，基于已知的卡车和乘用车参数集，可以从少量输入数据估算完整的参数集。TMeasy 考虑非线性效应，并包括接触补丁滑移状态方程。Chrono 中使用的实现相比最新的商业 TMeasy 版本缺少一些功能。例如，没有带动态和动态驻车扭矩计算。Chrono TMeasy 轮胎实现包含已在书籍 [Road Vehicle Dynamics - Fundamentals and Modeling with MATLAB](https://www.routledge.com/Road-Vehicle-Dynamics-Fundamentals-and-Modeling-with-MATLAB/Rill-Castro/p/book/9780367199739), Georg Rill 和 Abel Arrieta Castro, CRC Press, 2020 中发布的算法。

参见 [ChTMeasyTire](@ref chrono::vehicle::ChTMeasyTire) 和 [TMeasyTire](@ref chrono::vehicle::TMeasyTire)。

下面提供了一个包含 TMeasy 轮胎规格的 JSON 文件示例：
\include "data/vehicle/hmmwv/tire/HMMWV_TMeasyTire.json"

### Fiala 轮胎模型  {#wheeled_tire_fiala}

Fiala 轮胎模型在 Chrono::Vehicle 中的实现主要基于 MSC ADAMS/tire 帮助文档中介绍的瞬态 Fiala 轮胎模型，该模型使用轮胎滑移状态方程来改善模型在低速到零前进速度下的表现。Fiala 轮胎模型基于刷模型假设，仅需要少量系数。该轮胎模型假设轮胎相对于道路处于零倾角，并且没有生成翻转力矩的机制。然而，它在力和力矩计算中耦合了轮胎的横向和纵向滑移状态，从而提供了更真实的组合滑移描述。由于未考虑影响结果的重要因素，Fiala 轮胎模型不应用于严肃的车辆操控仿真。

参见 [ChFialaTire](@ref chrono::vehicle::ChFialaTire) 和 [FialaTire](@ref chrono::vehicle::FialaTire)。

下面提供了一个包含 Fiala 轮胎规格的 JSON 文件示例：
\include "data/vehicle/hmmwv/tire/HMMWV_FialaTire.json"

上面 JSON 文件中嵌入的垂直载荷曲线如下所示：

<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/FialaTire_vertical_load.png" width="500" />

##  操纵轮胎模型的验证 {#handling_tire_validation}

下面展示了针对 FED-alpha 车辆的 3 种 Chrono::Vehicle 操纵轮胎模型的验证研究，实验数据由密歇根州 Keweenah 研究中心 (KRC) 提供。

在这个名为 `Steady State Cornering` (SSC) 的测试中，车辆沿着一个圆圈行驶，起始速度为所谓的 "Ackermann-Speed"。该值约为 3 m/s，因此滑移值相当小，车辆沿圆圈运动。实际测试通过逐步增加车辆速度并保持恒定来继续。这些连续的速度增加步骤重复进行，直到达到最大可能的横向加速度，或发动机功率耗尽。KRC 测试在左转和右转中进行，以突出车辆的任何不对称性（如果存在）。

SSC 测试的目标是推断车辆是否对普通驾驶员安全。车辆应表现为转向不足，这意味着随着横向加速度的增加，驾驶员必须提供越来越大的转向角度以保持车辆在圆圈上并维持车辆稳定性。表现为转向过度的车辆倾向于向圆心转动并变得不稳定，因为后轮的横向滑移储备不足。对于普通驾驶员使用的公共交通标准车辆，应避免这种转向过度的行为，尽管专业拉力赛驾驶员更喜欢转向过度的车辆。

对于 FED-alpha，SSC 测试被定义为准稳态运行，其中速度连续但非常缓慢地变化，因此没有明显的动态效应。因此，仿真结果显示为连续曲线。数据的符号选择方式显示右转在右侧，左转在左侧。实验 KRC 数据用点表示。下图显示了 Chrono Pac02、TMsimple 和 TMeasy 轮胎模型的 SSC 仿真结果叠加在 KRC 实验数据上。

<img src="http://www.projectchrono.org/assets/manual/vehicle/tire/Pac02_SSC.png" width="650" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/tire/TMsimple_SSC.png" width="650" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/tire/TMeasy_SSC.png" width="650" />

## 基于有限元的轮胎模型  {#wheeled_tire_fea}

最后，提供的第三类轮胎模型是轮胎的完整有限元表示。虽然这些模型由于其详细的物理模型而有可能是最准确的，但它们也是目前 Chrono::Vehicle 中可用的轮胎模型中计算成本最高的。与刚性或半经验轮胎模型不同，基于有限元的轮胎模型能够同时考虑轮胎和地面的柔性，这是许多类型的越野机动性和车辆动力学研究的重要特性。这些有限元轮胎模型利用了 Chrono 中的非线性有限元能力。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/FEA_tire_sections.png" width="600" />

### ANCF 壳体可变形轮胎 {#vehicle_tire_ancf}

参见 [ChANCFTire](@ref chrono::vehicle::ChANCFTire) 和 [ANCFTire](@ref chrono::vehicle::ANCFTire)。

下面的 JSON 文件包含 ANCFTire 的规格：
\include "data/vehicle/hmmwv/tire/HMMWV_ANCF4Tire.json"

### Reissner 壳体可变形轮胎 {#vehicle_tire_reissner}

参见 [ChReissnerTire](@ref chrono::vehicle::ChReissnerTire) 和 [ReissnerTire](@ref chrono::vehicle::ReissnerTire)。
