地形模型 {#vehicle_terrain}
=================================

\tableofcontents

在 Chrono::Vehicle 中，地形对象必须提供以下方法：

- 返回指定位置正下方点的地形高度
- 返回指定位置正下方点的地形法线
- 返回指定位置正下方点的地形摩擦系数
其中给定的位置假定以当前世界坐标系表示。

参见基类 [ChTerrain](@ref chrono::vehicle::ChTerrain) 的定义。

注意，这些量仅与所谓的[半经验轮胎模型](@ref vehicle_tire_empirical)的交互相关。因此，它们不适用于可变形地形（SCM、颗粒或基于FEA的地形），这些地形只能与[刚性](@ref wheeled_tire_rigid)或[FEA](@ref wheeled_tire_fea)轮胎模型以及履带车辆一起使用（因为它们依赖于底层的Chrono碰撞和接触系统）。

此外，摩擦系数值可能被某些轮胎模型用来修改轮胎特性，但它不会影响地形与其他物体的交互（包括不显式使用它的轮胎模型）。

ChTerrain基类还定义了一个函数对象[ChTerrain::FrictionFunctor](@ref chrono::vehicle::ChTerrain::FrictionFunctor)，它提供了一个接口，用于指定位置依赖的摩擦系数。用户必须实现一个从该基类派生的自定义类，并实现虚方法`operator()`，以返回给定\f$(x,y,z)\f$位置正下方点的摩擦系数（假定以当前世界坐标系表示）。

## 平坦地形 {#vehicle_terrain_flat}

[FlatTerrain](@ref chrono::vehicle::FlatTerrain) 是一个水平平面的模型，具有无限的延伸，位于用户指定的高度。方法 [FlatTerrain::GetCoefficientFriction](@ref chrono::vehicle::FlatTerrain::GetCoefficientFriction) 返回在构造时指定的常数摩擦系数，或者如果注册了 `FrictionFunctor` 对象，则返回其值。

由于平坦地形模型不携带任何碰撞和接触信息，因此它只能与[半经验轮胎模型](@ref vehicle_tire_empirical)一起使用。

## 刚性地形 {#vehicle_terrain_rigid}

[RigidTerrain](@ref chrono::vehicle::RigidTerrain) 是一个具有任意几何形状的刚性地形模型。刚性地形由一组补丁组成，每个补丁可以是以下之一：

- 一个矩形盒子，可能旋转；“驾驶”表面是盒子的顶部面（在世界的垂直方向上）
- 从用户指定的 Wavefront OBJ 文件读取的三角网格
- 从用户指定的灰度 BMP 图像程序生成的三角网格

刚性地形模型可以与任何 Chrono::Vehicle 轮胎模型以及履带车辆一起使用。

一个盒子补丁由顶部（驾驶）表面的中心、顶部表面的法线和补丁的尺寸（长度、宽度和可选的厚度）指定。可选地，盒子补丁可以由多个相邻的瓦片组成，每个瓦片都是一个 Chrono 盒子接触形状；对于具有大水平范围的盒子补丁，建议使用这种方式，因为单个碰撞形状可能导致碰撞检测算法中的错误。

一个网格刚性地形补丁的示例如下图所示。假设网格是相对于 ISO 参考系提供的，并且没有“悬垂”（换句话说，垂直射线最多与网格相交一次）。可选地，用户可以为地形网格指定一个“厚度”，作为扫描球的半径。为该半径指定一个小的正值可以显著提高碰撞检测算法的鲁棒性。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/Rigid_mesh.png" width="600" />

高度图补丁是通过灰度 BMP 图像（如下面所示）、补丁的水平范围（长度和宽度）以及高度范围（最小和最大高度）来指定的。程序生成一个三角网格，为输入 BMP 图像中的每个像素创建一个网格顶点，在水平平面上拉伸网格以匹配给定的范围，在垂直方向上拉伸网格，使最小高度对应于完全黑色的像素颜色，最大高度对应于完全白色的像素。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/Rigid_heightmap_mag.png" width="400" />

**高度和法线计算**。 [RigidTerrain::GetHeight](@ref chrono::vehicle::RigidTerrain::GetHeight) 和 [RigidTerrain::GetNormal](@ref chrono::vehicle::RigidTerrain::GetNormal) 的实现依赖于相对昂贵的射线投射操作：从上方向所有组成补丁投射一条垂直射线，并报告交点处的高度和法线。对于盒子补丁，射线投射使用自定义的解析实现，找到射线与盒子顶部面的交点；对于基于网格的补丁，射线投射由底层碰撞系统处理。如果没有补丁被交叉，这些函数分别返回 \f$0\f$ 和世界的垂直方向。

**基于位置的摩擦系数**。 刚性地形模型支持定义一个 `FrictionFunctor` 对象。如果没有提供这样的函数对象，[RigidTerrain::GetCoefficientFriction](@ref chrono::vehicle::RigidTerrain::GetCoefficientFriction) 使用射线投射方法来识别正确的补丁，并返回该补丁的（常数）摩擦系数。如果提供了函数对象，RigidTerrain::GetCoefficientFriction 仅返回其值。然而，与地形的接触处理（例如，当使用刚性轮胎或履带车辆时）相对昂贵：在每次调用碰撞检测算法时（即每个仿真步一次），遍历 Chrono 系统中的所有接触列表，以拦截所有涉及刚性地形补丁碰撞模型的接触；对于这些接触，复合材料属性会被修改，以考虑接触点处的地形摩擦系数。

刚性地形可以通过编程方式构建，一次定义一个补丁，或者通过 JSON 文件指定，如下所示：
\include "data/vehicle/terrain/RigidPatches.json"

## CRG 地形 {#vehicle_terrain_crg}

[CRGTerrain](@ref chrono::vehicle::CRGTerrain) 是一个基于 [OpenCRG](http://opencrg.org) 道路规范构建的程序化地形模型。要使用此地形模型，用户必须安装 OpenCRG SDK 并在 CMake 配置期间启用其使用（参见 Chrono::Vehicle [安装说明](@ref module_vehicle_installation))。

CRG 地形从规范文件（如下所示）创建道路剖面（一个具有相关宽度的 3D 路径），并实现函数 [CRGTerrain::GetHeight](@ref chrono::vehicle::CRGTerrain::GetHeight) 和 [CRGTerrain::GetNormal](@ref chrono::vehicle::CRGTerrain::GetNormal) 来使用该规范。请注意，`crg` 规范文件可以是 ASCII 或二进制格式。
\include "data/vehicle/terrain/crg_roads/handmade_curved_minimalist.crg"

CRG 地形可以可视化为三角网格（表示道路“带”）或一组 3D 贝塞尔曲线（表示中心线和道路边界）。CRGTerrain 的其他特性包括：

- 能够导出道路网格（作为三角网格）
- 能够导出中心线（作为贝塞尔曲线）
- 报告道路长度和宽度的方法

下面的图像展示了使用三角网格或道路边界曲线的 CRG 道路的运行时可视化。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/Barber_mesh.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/Barber_curves.png" width="600" />

由于 CRG 地形模型目前不携带任何碰撞和接触信息，因此它只能与 [半经验轮胎模型](@ref vehicle_tire_empirical) 一起使用。

## 可变形 SCM（土壤接触模型） {#vehicle_terrain_scm}

在 [SCMTerrain](@ref chrono::vehicle::SCMTerrain) 中，地形由一个隐式的规则笛卡尔网格表示，其变形是通过节点的垂直偏转实现的。该土壤模型利用了 Chrono 的通用碰撞引擎，其轻量级的实现允许在接近实时的情况下计算车辆-地形接触力。
为了解决内存和计算效率问题，网格从未被显式创建。相反，只维护已变形的节点在哈希映射中。此外，碰撞系统中的射线投射（SCM 计算中最耗时的操作）是多线程的。为了实现变形地形的高效可视化，Chrono SCM 子系统提供了增量更新可视化网格的方法，并在使用外部可视化系统时，报告上一个时间步中变形的节点子集。

下面的图像展示了轮胎在可变形土壤中形成车辙，说明了 Chrono 版本 SCM 的网格结构。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/SCM_mesh_refinement.png" width="600" />

SCM 基于一个具有少量参数的半经验模型，这使得它易于根据实验结果进行校准。
它可以被视为 Bekker-Wong 模型在具有任意三维形状的车轮（或履带鞋）情况下的推广。
在可变形土壤上移动的车轮的 Bekker 公式提供了压力与土壤垂直变形之间的关系：
\f[
\sigma = \left( \frac{k_c}{b} + k_{\phi} \right) y^n
\f]
其中 \f$\sigma\f$ 是接触面压力，\f$y\f$ 是车轮下沉量，\f$k_c\f$ 是表示土壤内聚效应的经验系数，\f$k_{\phi}\f$ 是表示土壤刚度的经验系数，\f$n\f$ 是表示硬化效应的指数，该效应随着土壤压实的非线性增加而增加。最后，\f$b\f$ 是矩形接触面较短边的长度（因为原始 Bekker 理论假设圆柱形轮胎在平坦地形上滚动）。

对于通用接触面，长度 \f$b\f$ 不能像在原始 Bekker 模型中那样解释；相反，我们通过首先获取所有连接的接触面（使用洪泛算法），然后使用近似公式来估计该长度
\f[
b \approx \frac{2 A}{L}
\f]
其中 \f$A\f$ 是该接触面的面积，\f$L\f$ 是其周长。

Chrono SCM 实现的其他特性包括：

- 初始未变形网格可以创建为
  - 规则平铺网格（填充平坦矩形）
  - 从高度图创建（提供为灰度 BMP 图像）
  - 编程方式创建
- 支持地形参考平面的任意方向；默认情况下，地形定义为 \f$(x,y)\f$ 平面，\f$z\f$ 向上 [ISO 坐标系](@ref vehicle_ISO_frame)
- 支持移动补丁方法，其中射线投射（最耗时的操作）被限制在指定的区域内——可以是相对于车辆移动的矩形补丁，也可以是边界框的投影
- 支持指定位置依赖的土壤参数；这可以通过提供一个自定义回调类来实现，该类实现一个方法，该方法返回地形参考平面上给定 \f$(x,y)\f$ 点的所有土壤参数。参见 [SCMTerrain::SoilParametersCallback](@ref chrono::vehicle::SCMTerrain::SoilParametersCallback)

由于与该地形类型的交互是通过底层的 Chrono 接触系统完成的，因此它可以与 [刚性](@ref wheeled_tire_rigid) 或 [有限元](@ref wheeled_tire_fea) 轮胎模型以及履带车辆一起使用。

## 颗粒地形 {#vehicle_terrain_granular}

[GranularTerrain](@ref chrono::vehicle::GranularTerrain) 实现了一个矩形颗粒材料补丁，并利用了 Chrono 对所谓离散元方法（DEM）模拟的广泛支持。目前，该地形模型仅限于单分散球形颗粒材料。

由于大规模颗粒动力学模拟可能非常耗费计算资源，Chrono::Vehicle 中的 GranularTerrain 对象提供了对“移动补丁”方法的支持，其中模拟可以限制在一个颗粒材料箱中，该箱根据指定物体（通常是车辆底盘）的位置不断重新定位。目前，移动补丁只能在 \f$x\f$（前进）方向上重新定位。

下面的图像展示了使用移动补丁功能在 GranularTerrain 上进行车辆加速测试的情况。该模拟使用了超过 700,000 个颗粒，并使用 [Chrono::Multicore](@ref multicore_module) 模块进行多核并行模拟。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/Granular_moving_patch.png" width="600" />

颗粒地形的其他特性包括：

- 分层生成初始颗粒位置，水平平面上的颗粒位置均匀分布，并保证不小于颗粒半径的两倍
- 包含固定在边界箱上的颗粒（以抑制颗粒材料床整体滑动）；由于当前的限制，该特性不应与移动补丁选项一起使用
- 边界箱的解析定义和自定义碰撞检测机制
- 报告地形高度（定义为所有颗粒位置中最大的 \f$z\f$ 值）

由于与该地形类型的交互是通过底层的 Chrono 接触系统完成的，因此它可以与 [刚性](@ref wheeled_tire_rigid) 或 [有限元](@ref wheeled_tire_fea) 轮胎模型以及履带车辆一起使用。

## 可变形 FEA（ANCF 实体单元） {#vehicle_terrain_fea}

[FEATerrain](@ref chrono::vehicle::FEATerrain) 提供了一种基于专用 FEA 砖单元的可变形地形模型，单元类型为 [ChElementHexaANCF_3813_9](@ref chrono::fea::ChElementHexaANCF_3813_9)。  

该地形模型允许：

- 将盒状域离散化为用户指定数量的单元
- 分配材料属性（密度、弹性模量、泊松比、屈服应力、硬化斜率、膨胀角和摩擦角）
- 添加 Chrono FEA 网格可视化资产

由于与该地形类型的交互是通过底层的 Chrono 接触系统完成的，因此它可以与 [刚性](@ref wheeled_tire_rigid) 或 [有限元](@ref wheeled_tire_fea) 轮胎模型以及履带车辆一起使用。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/FEA_terrain.png" width="600" />
