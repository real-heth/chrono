
FEA 单元      {#manual_fea_elements}
=======================

\tableofcontents

不同类型的有限元可以在 [FEA 模块](@ref manual_fea) 中使用。在本页中，您可以找到它们属性的描述。

- 一个 **单元** 连接 N 个节点。
- 节点通过 std::shared_ptr 共享指针进行管理：您无需担心删除它们。
- 使用 ChMesh::AddElement() 将单元添加到网格中。
- 使用 SetNodes() 告诉单元连接了哪些节点来初始化单元。
- 使用 SetMaterial() 为单元设置材料属性。

# ChElementSpring    {#manual_ChElementSpring}

![](http://www.projectchrono.org/assets/manual/fea_ChElementSpring.png)

chrono::fea::ChElementSpring 是最简单的单元，可以作为学习如何实现有限元的起点。

此外，它对于桁架、悬挂等问题也很有用。这个基础实现假设线性行为，但有经验的程序员可以重写此类并实现更高级的非线性弹簧模型。

- 2 个 ChNodeFEAxyz 类型的节点
- 允许大位移
- 零质量单元
- 参数：
  - 静止长度 L
  - 刚度 k
  - 阻尼 r
- 刚度矩阵通过解析方法计算以提高性能（支持材料和几何刚度）。

# ChElementBar    {#manual_ChElementBar}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBar.png)

chrono::fea::ChElementBar 与 ChElementSpring 非常相似，但增加了质量的影响，并在构造时使用不同的参数。

- 2 个 ChNodeFEAxyz 类型的节点
- 与 ChElementSpring 非常相似，但具有质量
- 两端无扭矩（如两个球形关节）
- 允许大位移
- 参数：
  - 静止长度 L
  - 截面面积 A
  - 杨氏模量 E
  - 阻尼（如 Rayleight beta 参数）
- 刚度矩阵通过解析方法计算以提高性能（支持材料和几何刚度）。

# ChElementTetraCorot_4    {#manual_ChElementTetraCorot_4}

![](http://www.projectchrono.org/assets/manual/fea_ChElementTetra_4.png)

chrono::fea::ChElementTetraCorot_4 是用于模拟 3D 问题的最简单体单元。

- 4 个 ChNodeFEAxyz 类型的节点
- 线性插值，恒定应力
- 1 个积分点
- 大位移的共转公式
- 使用极分解进行共转框架
- 适用于固体
- 固体的最快单元
- 刚度矩阵通过解析方法计算以提高性能（注意，目前几何刚度项尚未添加）。

# ChElementTetraCorot_10    {#manual_ChElementTetraCorot_10}

![](http://www.projectchrono.org/assets/manual/fea_ChElementTetra_10.png)

chrono::fea::ChElementTetraCorot_10 是基于四面体的二次体单元，沿边缘有中间节点，如图所示。

- 10 个 ChNodeFEAxyz 类型的节点
- 二次插值，线性应力
- 4 个积分点
- 大位移的共转公式
- 使用极分解进行共转框架
- 注意：初始位置假设节点 n>4 精确位于边的中点
- 适用于固体
- 刚度矩阵通过解析方法计算以提高性能（注意，目前几何刚度项尚未添加）。

# ChElementHexaCorot_8    {#manual_ChElementHexaCorot_8}

![](http://www.projectchrono.org/assets/manual/fea_ChElementHexa_8.png)

chrono::fea::ChElementHexaCorot_8 是一种线性等参砖单元。

- 8 个 ChNodeFEAxyz 类型的节点
- 线性插值
- 8 个积分点
- 大位移的共转公式
- 适用于固体，适用于结构化网格
- 刚度矩阵通过解析方法计算以提高性能（注意，目前几何刚度项尚未添加）。

# ChElementHexaCorot_20   {#manual_ChElementHexaCorot_20}

![](http://www.projectchrono.org/assets/manual/fea_ChElementHexa_20.png)

chrono::fea::ChElementHexaCorot_20 是一种二次等参砖单元。

- 20 个 ChNodeFEAxyz 类型的节点
- 8 个在顶点，12 个在边的中点
- 二次插值
- 27 个积分点
- 大位移的共转公式
- 适用于固体，适用于结构化网格
- 刚度矩阵通过解析方法计算以提高性能（注意，目前几何刚度项尚未添加）。

# ChElementHexaANCF_3813    {#manual_CChElementHexaANCF_3813}

![](http://www.projectchrono.org/assets/manual/fea_ChElementHexa_8.png)

chrono::fea::ChElementHexaANCF_3813 是一种使用 ANCF 公式实现的砖单元。

- 8 个 ChNodeFEAxyz 类型的节点
- 线性插值
- 8 个积分点
- 使用 EAS 增强假设应变
- 大应变
- 可以使用 Mooney-Rivlin 模型用于超弹性材料
- 适用于固体，适用于结构化网格

# ChElementHexaANCF_3813_9    {#manual_ChElementHexaANCF_3813_9}

chrono::fea::ChElementHexaANCF_3813_9 是一种使用 ANCF 公式实现的砖单元。

- 9 个 ChNodeFEAxyz 类型的节点（8 个在角点，1 个在中心）
- 线性插值
- 8 个积分点
- 大应变的应变公式：
  - Green-Lagrange
  - Hencky
- 塑性：
  - J2（金属）
  - DruckerPrager（土壤，塑料）
  - DruckerPrager_Cap（土壤，塑料）
- 适用于固体，适用于结构化网格

# ChElementHexaANCF_3843    {#manual_ChElementHexaANCF_3843}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBrickANCF_3843.png)

chrono::fea::ChElementHexaANCF_3843 是一种基于 ANCF 方法的 8 节点砖单元，每个节点具有完整的位矢梯度坐标集。

- 8 个 ChNodeFEAxyzDDD 类型的节点
- 64 个积分点
- 大位移的 ANCF 公式
- 适用于固体，适用于结构化网格

# ChElementCableANCF   {#manual_ChElementCableANCF}

![](http://www.projectchrono.org/assets/manual/fea_ChElementCableANCF.png)

chrono::fea::ChElementCableANCF 是一种用于模拟细长梁（电缆、线、绳索）的快速单元，当不关心扭转、剪切等效应时非常有用。

- 2 个 ChNodeFEAxyzD 类型的节点
- 3 个积分点（刚度），4 个积分点（质量）
- 大位移的 ANCF 公式
- 细梁（无剪切）
- 不建模扭转刚度（适用于电缆、线）
- 截面属性：A, I, E, 密度, 阻尼，通过 chrono::fea::ChBeamSectionCable 对象定义。

# ChElementBeamANCF_3243   {#manual_ChElementBeamANCF_3243}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamANCF_3243.png)

chrono::fea::ChElementBeamANCF_3243 是一种厚梁单元，使用 ANCF 公式实现，每个节点具有完整的位矢梯度坐标集。作为替代方案，我们还提供了 chrono::fea::ChElementBeamIGA，在几何精确梁理论领域具有更高级的功能。

- 2 个 ChNodeFEAxyzDDD 类型的节点
- 大位移的 ANCF 公式
- 截面属性：矩形宽高、E、泊松比、剪切修正系数、密度

# ChElementBeamANCF_3333   {#manual_ChElementBeamANCF_3333}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamANCF.png)

chrono::fea::ChElementBeamANCF_3333 是一种厚梁单元，使用 ANCF 公式实现。
作为替代方案，我们还提供了 chrono::fea::ChElementBeamIGA，在几何精确梁理论领域具有更高级的功能。

- 3 个 ChNodeFEAxyzDD 类型的节点
- 大位移的 ANCF 公式
- 截面属性：矩形宽高、E、泊松比、剪切修正系数、密度

# ChElementBeamEuler   {#manual_ChElementBeamEuler}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamEuler.png)
![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamEuler_section.png)

chrono::fea::ChElementBeamEuler 是一种细长梁单元，采用三维共旋 Euler-Bernoulli 理论。对于低/中等程度的弯曲，且当剪切效应不重要（细长梁假设）时，该公式非常高效。

- 2 个 ChNodeFEAxyzrot 类型的节点
- 线性插值
- 1 个积分点（默认）
- 大位移的共旋公式
- 细梁（无剪切），基于 Euler-Bernoulli 细梁理论
- 截面属性包括以下设置：
  - A, A, Iyy, Izz,（或轴向和弯曲刚度），
  - G, J  (或扭转刚度)，
  - 密度, 阻尼
可选：
  - αe , ze , ye ,   用于偏移/旋转截面
  - zs , ys          用于偏移剪切中心
- 截面属性通过 chrono::fea::ChBeamSectionEuler 类定义，包括以下几种：
  - chrono::fea::ChBeamSectionEulerSimple , 用于均匀弹性，均匀密度 
  - chrono::fea::ChBeamSectionEulerAdvanced , 如上，增加偏移/旋转截面和剪切中心
  - chrono::fea::ChBeamSectionEulerAdvancedGeneric , 如果非均匀弹性或非均匀密度
  - chrono::fea::ChBeamSectionEulerEasyCircular , 易于使用的快捷方式
  - chrono::fea::ChBeamSectionEulerEasyRectangular , 易于使用的快捷方式
- 材料和几何刚度均已计算。

# ChElementBeamIGA   {#manual_ChElementBeamIGA}

![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamIGA.png)
![](http://www.projectchrono.org/assets/manual/fea_ChElementBeamIGA_b.png)

chrono::fea::ChElementBeamIGA 是一种基于等几何分析（IGA）的厚梁单元，因此具有 B 样条形状，并且基于几何精确梁理论。

- 等几何分析（IGA）形式的 Cosserat 杆，具有大位移
- 用户定义的阶数 n（例如：1=线性，2=二次，3=三次）
- 每个单元是 B 样条的一个跨度，因此每个单元使用 n+1 个控制点，即 chrono::fea::ChNodeFEAxyzrot 类型的节点
- 厚梁剪切效应是可能的，参见 Timoshenko 理论
- 使用简化积分以校正剪切锁定
- 支持初始弯曲配置
- 建议：使用 ChBuilderBeamIGA 便于创建完整的 B 样条，即给定完整的节点序列和点，如上图所示。
- 截面通过模块化方式定义，通过 chrono::fea::ChBeamSectionCosserat 组成：
  - 弹性模型来自 chrono::fea::ChElasticityCosserat，例如：
    - chrono::fea::ChElasticityCosseratGeneric
    - chrono::fea::ChElasticityCosseratSimple
	- chrono::fea::ChElasticityCosseratAdvanced
	- chrono::fea::ChElasticityCosseratAdvancedGeneric
    - chrono::fea::ChElasticityCosseratMesh
    - ...
  - 惯性模型来自 chrono::fea::ChInertiaCosserat，例如：
    - chrono::fea::ChInertiaCosseratSimple
    - chrono::fea::ChInertiaCosseratAdvanced
    - chrono::fea::ChInertiaCosseratMassref
    - ...
  - 阻尼模型来自 chrono::fea::ChDampingCosserat（可选），例如：
    - chrono::fea::ChDampingCosseratLinear
    - chrono::fea::ChDampingCosseratRayleigh
  - 塑性模型来自 chrono::fea::ChPlastcityCosserat（可选）
- 上述部分截面属性支持质心、剪切中心、轴向弹性力中心的偏移，以及截面轴的旋转，用于定义复杂的梁结构，如直升机叶片
- 材料和几何刚度均已考虑。

# ChElementShellReissner   {#manual_ChElementShellReissner}

![](http://www.projectchrono.org/assets/manual/fea_ChElementShellReissner.png)

chrono::fea::ChElementShellReissner 是一种四边形厚壳单元。

- 4 个 chrono::fea::ChNodeFEAxyzrot 类型的节点
- 双线性插值
- 4 个积分点（默认）
- 允许大位移，使用指数映射处理 SO3
- 允许厚壳
- 基于 Reissner 六场壳理论（带钻孔刚度）
- 可以有多层材料，使用 CLT 理论
- ANS，无剪切锁定
- 节点不需要与壳对齐（初始化时自动计算旋转偏移）
- 截面通过模块化方式定义，通过 N 层，每层由 chrono::fea::ChMaterialShellReissner 组成：
  - 弹性模型来自 chrono::fea::ChElasticityReissner，例如：
    - chrono::fea::ChElasticityReissnerIsothropic
    - chrono::fea::ChElasticityReissnerOrthotropic
    - chrono::fea::ChElasticityReissnerGeneric
	- ...
  - 阻尼模型来自 chrono::fea::ChDampingReissner（可选）
    - chrono::fea::ChDampingReissnerRayleigh
	- ...
  - 塑性模型来自 chrono::fea::ChPlasticityReissner（可选）

# ChElementShellANCF_3423   {#manual_ChElementShellANCF_3423}

![](http://www.projectchrono.org/assets/manual/fea_ChElementShellANCF.png)

chrono::fea::ChElementShellANCF_3423 是一种基于 ANCF 方法的四边形厚壳单元。

- 4 个 chrono::fea::ChNodeFEAxyzD 类型的节点
- 双线性插值
- 4 个积分点（默认）
- 允许大位移，使用 ANCF 公式
- 允许厚壳
- 可以有多层材料
- ANS-EAS，无剪切锁定
- 节点 D 必须在初始化时与壳法线对齐

# ChElementShellANCF_3443   {#manual_ChElementShellANCF_3443}

![](http://www.projectchrono.org/assets/manual/fea_ChElementShellANCF_3443.png)

chrono::fea::ChElementShellANCF_3443 是一种基于 ANCF 方法的四边形厚壳单元，具有每个节点的完整位置向量梯度坐标集。

- 4 个 chrono::fea::ChNodeFEAxyzDDD 类型的节点
- 允许大位移，使用 ANCF 公式
- 允许厚壳
- 可以有多层材料
- 锁定是该单元当前公式中的一个问题

# ChElementShellANCF_3833   {#manual_ChElementShellANCF_3833}

![](http://www.projectchrono.org/assets/manual/fea_ChElementShellANCF_8.png)

chrono::fea::ChElementShellANCF_3833 是一种基于 ANCF 方法的四边形厚壳单元。

- 8 个 chrono::fea::ChNodeFEAxyzDD 类型的节点
- 高阶插值
- 允许大位移，采用 ANCF 公式表述
- 允许厚壳
- 可以有多层材料
- 锁定是该单元当前公式中的一个问题

# ChElementShellBST   {#manual_ChElementShellBST}

![](http://www.projectchrono.org/assets/manual/fea_ChElementShellBST.png)

chrono::fea::ChElementShellBST 是一种三角形薄壳单元，具有非常高的计算效率。

- 三角形薄壳
- 6 个 chrono::fea::ChNodeFEAxyz 类型的节点
  - 1,2,3 来自三角形
  - 4,5,6 来自相邻的三角形（如果在边界上，任何一个都可以是可选的）
- 恒定应变，恒定曲率由弯曲的三角形邻居计算
- 允许大变形
- 可以有多层材料
- 基于 Kirchhoff-Love 理论（无剪切），适用于组织、帆布等
- 截面通过模块化方式定义，通过 N 层，每层由 chrono::fea::ChMaterialShellKirchhoff 组成：
  - 弹性模型来自 chrono::fea::ChElasticityKirchhoff，例如：
    - chrono::fea::ChElasticityKirchhoffIsothropic
    - chrono::fea::ChElasticityKirchhoffOrthotropic
    - chrono::fea::ChElasticityKirchhoffGeneric
	- ...
  - 阻尼模型来自 chrono::fea::ChDampingKirchhoff（可选）
  - 塑性模型来自 chrono::fea::ChPlasticityKirchhoff（可选）

# 理论

关于 Chrono 中有限元实现的更多信息，请参阅[白皮书页面](http://projectchrono.org/whitepapers/)。

# 示例

请参阅 [教程页面](http://projectchrono.org/tutorials/) 获取演示和示例。
